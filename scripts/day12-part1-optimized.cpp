#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <chrono>
#include <iomanip>

using namespace std;

struct Shape {
    vector<pair<int, int>> coords;
};

vector<Shape> getAllOrientations(const Shape& shape) {
    set<string> seen;
    vector<Shape> result;
    
    for (int flip = 0; flip < 2; flip++) {
        for (int rot = 0; rot < 4; rot++) {
            vector<pair<int, int>> coords = shape.coords;
            
            if (flip) {
                for (auto& [r, c] : coords) c = -c;
            }
            
            for (int i = 0; i < rot; i++) {
                vector<pair<int, int>> temp;
                for (auto [r, c] : coords) temp.push_back({c, -r});
                coords = temp;
            }
            
            int minR = INT_MAX, minC = INT_MAX;
            for (auto [r, c] : coords) {
                minR = min(minR, r);
                minC = min(minC, c);
            }
            for (auto& [r, c] : coords) {
                r -= minR;
                c -= minC;
            }
            
            vector<string> parts;
            for (auto [r, c] : coords) {
                parts.push_back(to_string(r) + "," + to_string(c));
            }
            sort(parts.begin(), parts.end());
            string key;
            for (auto& p : parts) key += p + "|";
            
            if (seen.find(key) == seen.end()) {
                seen.insert(key);
                result.push_back({coords});
            }
        }
    }
    
    return result;
}

bool tryPlace(int idx, const vector<int>& presents, 
              vector<vector<int>>& grid, int width, int height,
              map<int, vector<Shape>>& orientations) {
    if (idx >= (int)presents.size()) return true;
    
    int shapeIdx = presents[idx];
    
    for (const Shape& shape : orientations[shapeIdx]) {
        for (int r = 0; r < height; r++) {
            for (int c = 0; c < width; c++) {
                bool canPlace = true;
                for (auto [dr, dc] : shape.coords) {
                    int nr = r + dr, nc = c + dc;
                    if (nr >= height || nc >= width || grid[nr][nc] != -1) {
                        canPlace = false;
                        break;
                    }
                }
                
                if (canPlace) {
                    for (auto [dr, dc] : shape.coords) {
                        grid[r + dr][c + dc] = idx;
                    }
                    
                    if (tryPlace(idx + 1, presents, grid, width, height, orientations)) {
                        return true;
                    }
                    
                    for (auto [dr, dc] : shape.coords) {
                        grid[r + dr][c + dc] = -1;
                    }
                }
            }
        }
    }
    
    return false;
}

int solve(const vector<string>& lines, map<int, Shape>& shapes) {
    // Parse shapes
    shapes.clear();
    for (size_t i = 0; i < lines.size(); i++) {
        if (lines[i].empty()) continue;
        
        if (isdigit(lines[i][0]) && lines[i].find(':') != string::npos && 
            lines[i].find('x') == string::npos) {
            int shapeIdx = stoi(lines[i].substr(0, lines[i].find(':')));
            Shape shape;
            i++;
            int row = 0;
            
            while (i < lines.size() && !lines[i].empty() && 
                   !(isdigit(lines[i][0]) && lines[i].find(':') != string::npos) &&
                   lines[i].find('x') == string::npos) {
                for (size_t c = 0; c < lines[i].length(); c++) {
                    if (lines[i][c] == '#') {
                        shape.coords.push_back({row, (int)c});
                    }
                }
                row++;
                i++;
            }
            i--;
            shapes[shapeIdx] = shape;
        }
    }
    
    // Parse regions
    struct Region {
        int width, height;
        vector<int> presents;
    };
    
    vector<Region> regions;
    for (const string& line : lines) {
        if (line.find('x') != string::npos && line.find(':') != string::npos && 
            isdigit(line[0])) {
            Region r;
            size_t colonPos = line.find(':');
            size_t xPos = line.find('x');
            r.width = stoi(line.substr(0, xPos));
            r.height = stoi(line.substr(xPos + 1, colonPos - xPos - 1));
            
            stringstream ss(line.substr(colonPos + 1));
            int count;
            int idx = 0;
            while (ss >> count) {
                for (int j = 0; j < count; j++) {
                    r.presents.push_back(idx);
                }
                idx++;
            }
            regions.push_back(r);
        }
    }
    
    // Pre-compute all orientations
    map<int, vector<Shape>> allOrientations;
    for (auto& [idx, shape] : shapes) {
        allOrientations[idx] = getAllOrientations(shape);
    }
    
    int fittable = 0;
    
    for (auto& r : regions) {
        int area = r.width * r.height;
        int needed = 0;
        for (int p : r.presents) {
            needed += shapes[p].coords.size();
        }
        
        if (needed <= area) {
            vector<vector<int>> grid(r.height, vector<int>(r.width, -1));
            if (tryPlace(0, r.presents, grid, r.width, r.height, allOrientations)) {
                fittable++;
            }
        }
    }
    
    return fittable;
}

int main() {
    ifstream infile("../inputs/day-12-input.txt");
    if (!infile) {
        cerr << "Cannot open input file" << endl;
        return 1;
    }
    
    vector<string> lines;
    string line;
    while (getline(infile, line)) {
        lines.push_back(line);
    }
    infile.close();
    
    // Benchmark
    const int iterations = 1;
    int result = 0;
    map<int, Shape> shapes;
    
    auto start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; i++) {
        result = solve(lines, shapes);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    
    double total_s = duration.count() / 1000.0;
    double avg_ms = duration.count() / (double)iterations;
    
    cout << "C++ (Day 12 Part 1 - Optimized)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << fixed << setprecision(3) 
         << avg_ms << " ms (" << iterations << " iterations)" << endl;
    cout << "Total time: " << fixed << setprecision(2) 
         << total_s << " s" << endl;
    
    return 0;
}

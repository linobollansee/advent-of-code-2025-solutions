#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <sstream>

using namespace std;

struct Shape {
    vector<pair<int, int>> coords;
};

bool tryPlace(int idx, const vector<int>& presents, vector<vector<int>>& grid,
              int width, int height, const map<int, Shape>& shapes) {
    if (idx >= presents.size()) return true;
    
    int shapeIdx = presents[idx];
    const Shape& shape = shapes.at(shapeIdx);
    
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            bool canPlace = true;
            for (const auto& [dr, dc] : shape.coords) {
                int nr = r + dr, nc = c + dc;
                if (nr >= height || nc >= width || grid[nr][nc] != -1) {
                    canPlace = false;
                    break;
                }
            }
            
            if (canPlace) {
                for (const auto& [dr, dc] : shape.coords) {
                    grid[r + dr][c + dc] = idx;
                }
                
                if (tryPlace(idx + 1, presents, grid, width, height, shapes)) {
                    return true;
                }
                
                for (const auto& [dr, dc] : shape.coords) {
                    grid[r + dr][c + dc] = -1;
                }
            }
        }
    }
    
    return false;
}

int solve() {
    ifstream file("../inputs/day-12-input.txt");
    vector<string> lines;
    string line;
    
    while (getline(file, line)) {
        lines.push_back(line);
    }
    file.close();
    
    map<int, Shape> shapes;
    
    // Parse shapes
    for (size_t i = 0; i < lines.size(); i++) {
        string trimmed = lines[i];
        while (!trimmed.empty() && isspace(trimmed.back())) trimmed.pop_back();
        while (!trimmed.empty() && isspace(trimmed.front())) trimmed.erase(0, 1);
        
        if (trimmed.empty()) continue;
        
        if (isdigit(trimmed[0]) && trimmed.find(':') != string::npos && 
            trimmed.find('x') == string::npos) {
            int shapeIdx = stoi(trimmed.substr(0, trimmed.find(':')));
            vector<pair<int, int>> coords;
            i++;
            int row = 0;
            
            while (i < lines.size() && !lines[i].empty() &&
                   !(isdigit(lines[i][0]) && lines[i].find(':') != string::npos) &&
                   lines[i].find('x') == string::npos) {
                for (size_t c = 0; c < lines[i].length(); c++) {
                    if (lines[i][c] == '#') {
                        coords.push_back({row, (int)c});
                    }
                }
                row++;
                i++;
            }
            i--;
            shapes[shapeIdx] = {coords};
        }
    }
    
    // Parse regions
    vector<tuple<int, int, vector<int>>> regions;
    for (const auto& line : lines) {
        if (line.find('x') != string::npos && line.find(':') != string::npos && 
            !line.empty() && isdigit(line[0])) {
            size_t colonPos = line.find(':');
            string dims = line.substr(0, colonPos);
            size_t xPos = dims.find('x');
            int width = stoi(dims.substr(0, xPos));
            int height = stoi(dims.substr(xPos + 1));
            
            string rest = line.substr(colonPos + 1);
            istringstream iss(rest);
            vector<int> counts;
            int count;
            while (iss >> count) {
                counts.push_back(count);
            }
            
            vector<int> presents;
            for (size_t idx = 0; idx < counts.size(); idx++) {
                for (int j = 0; j < counts[idx]; j++) {
                    presents.push_back(idx);
                }
            }
            
            regions.push_back({width, height, presents});
        }
    }
    
    int fittable = 0;
    
    for (const auto& [width, height, presents] : regions) {
        int area = width * height;
        int needed = 0;
        for (int p : presents) {
            needed += shapes[p].coords.size();
        }
        
        if (needed <= area) {
            vector<vector<int>> grid(height, vector<int>(width, -1));
            if (tryPlace(0, presents, grid, width, height, shapes)) {
                fittable++;
            }
        }
    }
    
    return fittable;
}

int main() {
    const int iterations = 1;
    auto start = chrono::high_resolution_clock::now();
    
    int result;
    for (int i = 0; i < iterations; i++) {
        result = solve();
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double avgMs = duration.count() / (double)iterations / 1000000.0;
    
    cout << "C++ (Day 12 Part 1 - Simple)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMs << " ms (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000000.0) << " s" << endl;
    
    return 0;
}

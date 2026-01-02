#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <chrono>

using namespace std;

struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};

int solvePart1(const vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].length();
    
    // Find the starting position 'S'
    int startCol = grid[0].find('S');
    
    // Simulate tachyon beams using BFS
    queue<pair<int, int>> beams;
    beams.push({0, startCol});
    unordered_set<pair<int, int>, PairHash> visited;
    visited.insert({0, startCol});
    
    while (!beams.empty()) {
        int size = beams.size();
        
        for (int i = 0; i < size; i++) {
            auto [row, col] = beams.front();
            beams.pop();
            
            int newRow = row + 1;
            if (newRow >= rows) continue;
            
            char cell = grid[newRow][col];
            
            if (cell == '.') {
                auto key = make_pair(newRow, col);
                if (visited.find(key) == visited.end()) {
                    visited.insert(key);
                    beams.push({newRow, col});
                }
            } else if (cell == '^') {
                visited.insert({newRow, col});
                
                if (col > 0) {
                    auto leftKey = make_pair(newRow, col - 1);
                    if (visited.find(leftKey) == visited.end()) {
                        visited.insert(leftKey);
                        beams.push({newRow, col - 1});
                    }
                }
                
                if (col < cols - 1) {
                    auto rightKey = make_pair(newRow, col + 1);
                    if (visited.find(rightKey) == visited.end()) {
                        visited.insert(rightKey);
                        beams.push({newRow, col + 1});
                    }
                }
            }
        }
    }
    
    // Count activated splitters
    int count = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == '^' && visited.find({r, c}) != visited.end()) {
                count++;
            }
        }
    }
    
    return count;
}

int main() {
    // Read input
    ifstream file("../inputs/day-7-input.txt");
    vector<string> grid;
    string line;
    
    while (getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        grid.push_back(line);
    }
    file.close();
    
    // Benchmark
    const int iterations = 1;
    auto start = chrono::high_resolution_clock::now();
    
    int result;
    for (int i = 0; i < iterations; i++) {
        result = solvePart1(grid);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double avgMicros = duration.count() / (double)iterations / 1000.0;
    
    cout << "C++ (Day 7 Part 1 - Optimized)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

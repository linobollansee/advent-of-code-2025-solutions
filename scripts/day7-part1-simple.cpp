#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <queue>
#include <chrono>
#include <sstream>

using namespace std;

int solvePart1(const vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].length();
    
    // Find the starting position 'S'
    int startCol = -1;
    for (int c = 0; c < cols; c++) {
        if (grid[0][c] == 'S') {
            startCol = c;
            break;
        }
    }
    
    // Simulate tachyon beams
    queue<pair<int, int>> beams;
    beams.push({0, startCol});
    set<pair<int, int>> beamPositions;
    
    while (!beams.empty()) {
        int size = beams.size();
        
        for (int i = 0; i < size; i++) {
            auto [row, col] = beams.front();
            beams.pop();
            
            // Move beam down
            int newRow = row + 1;
            
            if (newRow >= rows) continue; // Beam exits
            
            char cell = grid[newRow][col];
            
            if (cell == '.') {
                // Continue downward
                auto key = make_pair(newRow, col);
                if (beamPositions.find(key) == beamPositions.end()) {
                    beamPositions.insert(key);
                    beams.push({newRow, col});
                }
            } else if (cell == '^') {
                // Split into left and right beams
                beamPositions.insert({newRow, col});
                
                // Left beam
                if (col - 1 >= 0) {
                    auto leftKey = make_pair(newRow, col - 1);
                    if (beamPositions.find(leftKey) == beamPositions.end()) {
                        beamPositions.insert(leftKey);
                        beams.push({newRow, col - 1});
                    }
                }
                
                // Right beam
                if (col + 1 < cols) {
                    auto rightKey = make_pair(newRow, col + 1);
                    if (beamPositions.find(rightKey) == beamPositions.end()) {
                        beamPositions.insert(rightKey);
                        beams.push({newRow, col + 1});
                    }
                }
            }
        }
    }
    
    // Count splitters that were activated
    int activatedSplitters = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == '^' && beamPositions.find({r, c}) != beamPositions.end()) {
                activatedSplitters++;
            }
        }
    }
    
    return activatedSplitters;
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
    
    cout << "C++ (Day 7 Part 1 - Simple)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

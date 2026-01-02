#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <chrono>

using namespace std;

long long solvePart2(const vector<string>& grid) {
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
    
    // BFS approach - process level by level
    map<tuple<int, int, string>, long long> currentStates;
    currentStates[{0, startCol, "down"}] = 1;
    
    for (int row = 0; row < rows; row++) {
        map<tuple<int, int, string>, long long> nextStates;
        
        for (const auto& [stateKey, count] : currentStates) {
            auto [r, c, dir] = stateKey;
            
            if (r != row) continue;
            
            char cell = grid[r][c];
            
            if (cell == '.' || cell == 'S') {
                // Continue downward
                auto nextKey = make_tuple(r + 1, c, string("down"));
                nextStates[nextKey] += count;
            } else if (cell == '^') {
                // Quantum split
                // Left path
                if (c - 1 >= 0) {
                    auto leftKey = make_tuple(r + 1, c - 1, string("left"));
                    nextStates[leftKey] += count;
                }
                // Right path
                if (c + 1 < cols) {
                    auto rightKey = make_tuple(r + 1, c + 1, string("right"));
                    nextStates[rightKey] += count;
                }
            }
        }
        
        currentStates = nextStates;
    }
    
    // Count total timelines that exited
    long long totalTimelines = 0;
    for (const auto& [key, count] : currentStates) {
        totalTimelines += count;
    }
    
    return totalTimelines;
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
    
    long long result;
    for (int i = 0; i < iterations; i++) {
        result = solvePart2(grid);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double avgMicros = duration.count() / (double)iterations / 1000.0;
    
    cout << "C++ (Day 7 Part 2 - Simple)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

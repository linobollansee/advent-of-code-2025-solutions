#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <chrono>

using namespace std;

struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};

long long solvePart2(const vector<string>& grid) {
    int rows = grid.size();
    int cols = grid[0].length();
    
    // Find the starting position 'S'
    int startCol = grid[0].find('S');
    
    // Track timelines per state
    unordered_map<pair<int, int>, long long, PairHash> currentStates;
    currentStates[{0, startCol}] = 1;
    
    for (int row = 0; row < rows; row++) {
        unordered_map<pair<int, int>, long long, PairHash> nextStates;
        
        for (const auto& [key, count] : currentStates) {
            auto [r, c] = key;
            if (r != row) continue;
            
            char cell = grid[r][c];
            
            if (cell == '.' || cell == 'S') {
                nextStates[{r + 1, c}] += count;
            } else if (cell == '^') {
                if (c > 0) {
                    nextStates[{r + 1, c - 1}] += count;
                }
                if (c < cols - 1) {
                    nextStates[{r + 1, c + 1}] += count;
                }
            }
        }
        
        currentStates = nextStates;
    }
    
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
    
    cout << "C++ (Day 7 Part 2 - Optimized)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

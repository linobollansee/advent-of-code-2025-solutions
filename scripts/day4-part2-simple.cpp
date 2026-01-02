#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

int countNeighbors(const vector<string>& grid, int row, int col) {
    int count = 0;
    int rows = grid.size();
    int cols = grid[0].size();
    
    // 8 directions
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    for (int i = 0; i < 8; i++) {
        int newRow = row + dx[i];
        int newCol = col + dy[i];
        if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
            if (grid[newRow][newCol] == '@') {
                count++;
            }
        }
    }
    
    return count;
}

int solve() {
    ifstream file("../inputs/day-4-input.txt");
    vector<string> grid;
    string line;
    
    while (getline(file, line)) {
        grid.push_back(line);
    }
    file.close();
    
    int totalRemoved = 0;
    bool changed = true;
    
    while (changed) {
        changed = false;
        vector<pair<int, int>> toRemove;
        
        // Find all cells with < 4 neighbors
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] == '@') {
                    int neighbors = countNeighbors(grid, i, j);
                    if (neighbors < 4) {
                        toRemove.push_back({i, j});
                    }
                }
            }
        }
        
        // Remove them
        if (!toRemove.empty()) {
            changed = true;
            totalRemoved += toRemove.size();
            for (auto& pos : toRemove) {
                grid[pos.first][pos.second] = '.';
            }
        }
    }
    
    return totalRemoved;
}

int main() {
    const int iterations = 1;
    int answer = 0;
    
    auto start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; i++) {
        answer = solve();
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    
    double avgTime = static_cast<double>(duration.count()) / iterations;
    double totalTimeMs = duration.count() / 1000.0;
    
    cout << "C++ (Day 4 Part 2 - Simple)" << endl;
    cout << "Answer: " << answer << endl;
    cout << "Average time: " << avgTime << " microseconds" << endl;
    cout << "Total time: " << totalTimeMs << " ms" << endl;
    
    return 0;
}

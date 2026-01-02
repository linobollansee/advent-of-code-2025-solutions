#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>

using namespace std;

int solve() {
    ifstream file("../inputs/day-4-input.txt");
    vector<string> grid;
    string line;
    
    while (getline(file, line)) {
        grid.push_back(line);
    }
    file.close();
    
    int rows = grid.size();
    int cols = grid[0].size();
    int result = 0;
    
    // 8 directions
    static const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static const int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] == '@') {
                int count = 0;
                
                // Inline neighbor counting for better performance
                for (int d = 0; d < 8; d++) {
                    int newRow = i + dx[d];
                    int newCol = j + dy[d];
                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && grid[newRow][newCol] == '@') {
                        count++;
                        if (count >= 4) break; // Early exit optimization
                    }
                }
                
                if (count < 4) {
                    result++;
                }
            }
        }
    }
    
    return result;
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
    
    cout << "C++ (Day 4 Part 1 - Optimized)" << endl;
    cout << "Answer: " << answer << endl;
    cout << "Average time: " << avgTime << " microseconds" << endl;
    cout << "Total time: " << totalTimeMs << " ms" << endl;
    
    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

// Optimized version - calculate crossings without iterating
int solvePart2(const vector<string>& rotations) {
    int position = 50;
    int count = 0;
    
    for (const string& rotation : rotations) {
        char direction = rotation[0];
        int distance = stoi(rotation.substr(1));
        
        if (direction == 'L') {
            // Count full rotations
            int fullRotations = distance / 100;
            count += fullRotations;
            
            // Check if partial rotation crosses 0
            int remainder = distance % 100;
            int newPos = (position - remainder + 100) % 100;
            
            // Cross 0 if: remainder >= position and position > 0
            if (remainder >= position && position > 0) {
                count++;
            }
            
            position = newPos;
        } else {
            // Count crossings going right
            int crossings = (position + distance) / 100;
            count += crossings;
            position = (position + distance) % 100;
        }
    }
    
    return count;
}

int main() {
    // Read input
    ifstream file("../inputs/day-1-input.txt");
    vector<string> input;
    string line;
    while (getline(file, line)) {
        input.push_back(line);
    }
    file.close();
    
    // Benchmark
    const int iterations = 1;
    auto start = chrono::high_resolution_clock::now();
    
    int result;
    for (int i = 0; i < iterations; i++) {
        result = solvePart2(input);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double avgMicros = duration.count() / (double)iterations / 1000.0;
    
    cout << "C++ (Day 1 Part 2 - Optimized)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

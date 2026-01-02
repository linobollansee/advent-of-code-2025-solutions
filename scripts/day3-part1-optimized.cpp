#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;

int solvePart1(const vector<string>& banks) {
    int totalJoltage = 0;
    
    for (const string& bank : banks) {
        int maxJoltage = 0;
        
        for (size_t i = 0; i < bank.length(); i++) {
            for (size_t j = i + 1; j < bank.length(); j++) {
                string twoDigit = string() + bank[i] + bank[j];
                int value = stoi(twoDigit);
                maxJoltage = max(maxJoltage, value);
            }
        }
        
        totalJoltage += maxJoltage;
    }
    
    return totalJoltage;
}

int main() {
    // Read input
    ifstream file("../inputs/day-3-input.txt");
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
        result = solvePart1(input);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double avgMicros = duration.count() / (double)iterations / 1000.0;
    
    cout << "C++ (Day 3 Part 1 - Optimized)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

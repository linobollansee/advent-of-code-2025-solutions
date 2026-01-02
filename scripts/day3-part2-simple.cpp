#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;

long long solvePart2(const vector<string>& banks) {
    long long totalJoltage = 0;
    
    for (const string& bank : banks) {
        int n = bank.length();
        const int toSelect = 12;
        
        string selected = "";
        int availableStart = 0;
        
        for (int pos = 0; pos < toSelect; pos++) {
            int remaining = toSelect - pos - 1;
            int mustLeaveAvailable = remaining;
            int canSearchUntil = n - mustLeaveAvailable;
            
            char maxDigit = '0';
            int maxPos = availableStart;
            
            for (int i = availableStart; i < canSearchUntil; i++) {
                if (bank[i] > maxDigit) {
                    maxDigit = bank[i];
                    maxPos = i;
                }
            }
            
            selected += maxDigit;
            availableStart = maxPos + 1;
        }
        
        long long joltage = stoll(selected);
        totalJoltage += joltage;
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
    
    long long result;
    for (int i = 0; i < iterations; i++) {
        result = solvePart2(input);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double avgMicros = duration.count() / (double)iterations / 1000.0;
    
    cout << "C++ (Day 3 Part 2 - Simple)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>

using namespace std;

bool isRepeatedAtLeastTwice(long long num) {
    string s = to_string(num);
    int len = s.length();
    
    for (int patternLen = 1; patternLen <= len / 2; patternLen++) {
        if (len % patternLen != 0) continue;
        
        string pattern = s.substr(0, patternLen);
        bool isValid = true;
        
        for (int i = patternLen; i < len; i += patternLen) {
            if (s.substr(i, patternLen) != pattern) {
                isValid = false;
                break;
            }
        }
        
        if (isValid) return true;
    }
    
    return false;
}

long long solvePart2(const string& input) {
    vector<pair<long long, long long>> ranges;
    stringstream ss(input);
    string range;
    
    while (getline(ss, range, ',')) {
        size_t pos = range.find('-');
        if (pos != string::npos) {
            long long start = stoll(range.substr(0, pos));
            long long end = stoll(range.substr(pos + 1));
            ranges.push_back({start, end});
        }
    }
    
    long long sum = 0;
    for (const auto& r : ranges) {
        for (long long id = r.first; id <= r.second; id++) {
            if (isRepeatedAtLeastTwice(id)) {
                sum += id;
            }
        }
    }
    
    return sum;
}

int main() {
    // Read input
    ifstream file("../inputs/day-2-input.txt");
    string input;
    getline(file, input);
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
    
    cout << "C++ (Day 2 Part 2 - Optimized)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

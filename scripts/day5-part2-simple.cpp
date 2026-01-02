#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>
#include <algorithm>

using namespace std;

struct Range {
    long long start;
    long long end;
};

long long solvePart2(const string& input) {
    vector<Range> ranges;
    
    stringstream ss(input);
    string line;
    
    while (getline(ss, line)) {
        if (line.empty()) break;
        
        size_t pos = line.find('-');
        long long start = stoll(line.substr(0, pos));
        long long end = stoll(line.substr(pos + 1));
        ranges.push_back({start, end});
    }
    
    // Merge overlapping ranges to avoid double counting
    vector<Range> merged;
    sort(ranges.begin(), ranges.end(), [](const Range& a, const Range& b) {
        return a.start < b.start;
    });
    
    for (const auto& range : ranges) {
        if (merged.empty()) {
            merged.push_back(range);
        } else {
            Range& last = merged.back();
            
            // If current range overlaps or is adjacent to the last one, merge them
            if (range.start <= last.end + 1) {
                last.end = max(last.end, range.end);
            } else {
                merged.push_back(range);
            }
        }
    }
    
    // Count all IDs in the merged ranges
    long long totalCount = 0;
    for (const auto& range : merged) {
        totalCount += range.end - range.start + 1;
    }
    
    return totalCount;
}

int main() {
    // Read input
    ifstream file("../inputs/day-5-input.txt");
    stringstream buffer;
    buffer << file.rdbuf();
    string input = buffer.str();
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
    
    cout << "C++ (Day 5 Part 2 - Simple)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

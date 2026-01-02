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
    
    // Sort and merge overlapping ranges
    sort(ranges.begin(), ranges.end(), [](const Range& a, const Range& b) {
        return a.start < b.start;
    });
    
    long long totalCount = 0;
    long long currentStart = ranges[0].start;
    long long currentEnd = ranges[0].end;
    
    for (size_t i = 1; i < ranges.size(); i++) {
        if (ranges[i].start <= currentEnd + 1) {
            currentEnd = max(currentEnd, ranges[i].end);
        } else {
            totalCount += currentEnd - currentStart + 1;
            currentStart = ranges[i].start;
            currentEnd = ranges[i].end;
        }
    }
    
    totalCount += currentEnd - currentStart + 1;
    
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
    
    cout << "C++ (Day 5 Part 2 - Optimized)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>

using namespace std;

struct Range {
    long long start;
    long long end;
};

int solvePart1(const string& input) {
    vector<Range> ranges;
    vector<long long> availableIds;
    
    stringstream ss(input);
    string line;
    bool readingRanges = true;
    
    while (getline(ss, line)) {
        if (line.empty()) {
            readingRanges = false;
            continue;
        }
        
        if (readingRanges) {
            size_t pos = line.find('-');
            long long start = stoll(line.substr(0, pos));
            long long end = stoll(line.substr(pos + 1));
            ranges.push_back({start, end});
        } else {
            availableIds.push_back(stoll(line));
        }
    }
    
    int freshCount = 0;
    
    for (long long id : availableIds) {
        for (const auto& range : ranges) {
            if (id >= range.start && id <= range.end) {
                freshCount++;
                break;
            }
        }
    }
    
    return freshCount;
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
    
    int result;
    for (int i = 0; i < iterations; i++) {
        result = solvePart1(input);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double avgMicros = duration.count() / (double)iterations / 1000.0;
    
    cout << "C++ (Day 5 Part 1 - Optimized)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

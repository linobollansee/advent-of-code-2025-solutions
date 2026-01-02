#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <sstream>

using namespace std;

struct Problem {
    vector<long long> numbers;
    char op;
};

long long solvePart1(const string& input) {
    stringstream ss(input);
    vector<string> lines;
    string line;
    
    while (getline(ss, line)) {
        lines.push_back(line);
    }
    
    if (lines.empty()) return 0;
    
    int width = lines[0].length();
    int height = lines.size();
    
    vector<Problem> problems;
    int col = 0;
    
    while (col < width) {
        // Check if this column starts a problem
        bool hasNonSpace = false;
        for (int row = 0; row < height; row++) {
            if (col < lines[row].length() && lines[row][col] != ' ') {
                hasNonSpace = true;
                break;
            }
        }
        
        if (!hasNonSpace) {
            col++;
            continue;
        }
        
        // Find the end of this problem
        int endCol = col;
        while (endCol < width) {
            bool isAllSpace = true;
            for (int row = 0; row < height; row++) {
                if (endCol < lines[row].length() && lines[row][endCol] != ' ') {
                    isAllSpace = false;
                    break;
                }
            }
            if (isAllSpace) break;
            endCol++;
        }
        
        // Extract this problem
        vector<long long> numbers;
        char op = '+';
        
        for (int row = 0; row < height; row++) {
            string cell = lines[row].substr(col, endCol - col);
            // Trim
            size_t start = cell.find_first_not_of(' ');
            size_t end = cell.find_last_not_of(' ');
            if (start != string::npos) {
                cell = cell.substr(start, end - start + 1);
                
                if (cell == "+" || cell == "*") {
                    op = cell[0];
                } else if (!cell.empty()) {
                    numbers.push_back(stoll(cell));
                }
            }
        }
        
        problems.push_back({numbers, op});
        col = endCol;
    }
    
    // Calculate answers
    long long grandTotal = 0;
    
    for (const auto& problem : problems) {
        long long result;
        if (problem.op == '+') {
            result = 0;
            for (long long num : problem.numbers) {
                result += num;
            }
        } else {
            result = 1;
            for (long long num : problem.numbers) {
                result *= num;
            }
        }
        grandTotal += result;
    }
    
    return grandTotal;
}

int main() {
    // Read input
    ifstream file("../inputs/day-6-input.txt");
    stringstream buffer;
    buffer << file.rdbuf();
    string input = buffer.str();
    file.close();
    
    // Remove trailing newline
    if (!input.empty() && input.back() == '\n') {
        input.pop_back();
    }
    if (!input.empty() && input.back() == '\r') {
        input.pop_back();
    }
    
    // Benchmark
    const int iterations = 1;
    auto start = chrono::high_resolution_clock::now();
    
    long long result;
    for (int i = 0; i < iterations; i++) {
        result = solvePart1(input);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double avgMicros = duration.count() / (double)iterations / 1000.0;
    
    cout << "C++ (Day 6 Part 1 - Simple)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <numeric>

using namespace std;

struct Problem {
    vector<long long> numbers;
    char op;
};

long long solvePart2(const string& input) {
    vector<string> lines;
    size_t pos = 0;
    size_t found;
    string temp = input;
    
    while ((found = temp.find('\n')) != string::npos) {
        lines.push_back(temp.substr(0, found));
        temp = temp.substr(found + 1);
    }
    if (!temp.empty()) lines.push_back(temp);
    
    int height = lines.size();
    int width = 0;
    for (const auto& line : lines) {
        width = max(width, (int)line.length());
    }
    
    vector<string> normalizedLines;
    for (const auto& line : lines) {
        string padded = line;
        while (padded.length() < width) padded += ' ';
        normalizedLines.push_back(padded);
    }
    
    vector<Problem> problems;
    int col = width - 1;
    
    while (col >= 0) {
        bool hasNonSpace = false;
        for (int row = 0; row < height; row++) {
            if (normalizedLines[row][col] != ' ') {
                hasNonSpace = true;
                break;
            }
        }
        
        if (!hasNonSpace) {
            col--;
            continue;
        }
        
        int startCol = col;
        while (startCol > 0) {
            bool isAllSpace = true;
            for (int row = 0; row < height; row++) {
                if (normalizedLines[row][startCol - 1] != ' ') {
                    isAllSpace = false;
                    break;
                }
            }
            if (isAllSpace) break;
            startCol--;
        }
        
        vector<long long> numbers;
        char op = '+';
        
        for (int c = col; c >= startCol; c--) {
            string digitStr = "";
            
            for (int row = 0; row < height; row++) {
                char ch = normalizedLines[row][c];
                if (ch == '+' || ch == '*') {
                    op = ch;
                } else if (ch != ' ') {
                    digitStr += ch;
                }
            }
            
            if (!digitStr.empty()) {
                numbers.push_back(stoll(digitStr));
            }
        }
        
        if (op != ' ' && !numbers.empty()) {
            problems.push_back({numbers, op});
        }
        
        col = startCol - 1;
    }
    
    long long grandTotal = 0;
    
    for (const auto& problem : problems) {
        long long result;
        if (problem.op == '+') {
            result = accumulate(problem.numbers.begin(), problem.numbers.end(), 0LL);
        } else {
            result = accumulate(problem.numbers.begin(), problem.numbers.end(), 1LL, multiplies<long long>());
        }
        grandTotal += result;
    }
    
    return grandTotal;
}

int main() {
    ifstream file("../inputs/day-6-input.txt");
    string input((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();
    
    const int iterations = 1;
    auto start = chrono::high_resolution_clock::now();
    
    long long result;
    for (int i = 0; i < iterations; i++) {
        result = solvePart2(input);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double avgMicros = duration.count() / (double)iterations / 1000.0;
    
    cout << "C++ (Day 6 Part 2 - Optimized)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

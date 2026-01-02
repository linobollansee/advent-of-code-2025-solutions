#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <sstream>

using namespace std;

struct Point {
    int x, y;
};

long long solvePart1(const vector<Point>& points) {
    long long maxArea = 0;
    
    // Try all pairs of points as opposite corners
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            int x1 = points[i].x;
            int y1 = points[i].y;
            int x2 = points[j].x;
            int y2 = points[j].y;
            
            // Calculate rectangle area (inclusive of both endpoints)
            long long area = ((long long)abs(x2 - x1) + 1) * (abs(y2 - y1) + 1);
            maxArea = max(maxArea, area);
        }
    }
    
    return maxArea;
}

int main() {
    // Read input
    ifstream file("../inputs/day-9-input.txt");
    vector<Point> points;
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Point p;
        
        getline(ss, token, ',');
        p.x = stoi(token);
        getline(ss, token, ',');
        p.y = stoi(token);
        
        points.push_back(p);
    }
    file.close();
    
    // Benchmark
    const int iterations = 1;
    auto start = chrono::high_resolution_clock::now();
    
    long long result;
    for (int i = 0; i < iterations; i++) {
        result = solvePart1(points);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double avgMicros = duration.count() / (double)iterations / 1000.0;
    
    cout << "C++ (Day 9 Part 1 - Simple)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

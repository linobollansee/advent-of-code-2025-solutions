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
    const int n = points.size();
    
    // Optimized: Try all pairs of points as opposite corners
    for (int i = 0; i < n - 1; i++) {
        const int x1 = points[i].x;
        const int y1 = points[i].y;
        
        for (int j = i + 1; j < n; j++) {
            const int x2 = points[j].x;
            const int y2 = points[j].y;
            
            // Calculate rectangle area (inclusive of both endpoints)
            const int width = abs(x2 - x1) + 1;
            const int height = abs(y2 - y1) + 1;
            const long long area = (long long)width * height;
            
            if (area > maxArea) {
                maxArea = area;
            }
        }
    }
    
    return maxArea;
}

int main() {
    // Read input
    ifstream file("../inputs/day-9-input.txt");
    vector<Point> points;
    points.reserve(500);
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
    
    cout << "C++ (Day 9 Part 1 - Optimized)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

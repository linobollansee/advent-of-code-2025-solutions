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

struct Edge {
    int minX, minY, maxX, maxY;
};

inline vector<Edge> getNormalizedEdges(const vector<Point>& tiles) {
    vector<Edge> edges;
    int n = tiles.size();
    edges.reserve(n);
    
    for (int i = 0; i < n - 1; i++) {
        edges.push_back({
            min(tiles[i].x, tiles[i+1].x),
            min(tiles[i].y, tiles[i+1].y),
            max(tiles[i].x, tiles[i+1].x),
            max(tiles[i].y, tiles[i+1].y)
        });
    }
    
    edges.push_back({
        min(tiles[n-1].x, tiles[0].x),
        min(tiles[n-1].y, tiles[0].y),
        max(tiles[n-1].x, tiles[0].x),
        max(tiles[n-1].y, tiles[0].y)
    });
    
    return edges;
}

inline bool isFullyContained(const vector<Edge>& edges, int minX, int minY, int maxX, int maxY) {
    for (const auto& edge : edges) {
        if (minX < edge.maxX && maxX > edge.minX && minY < edge.maxY && maxY > edge.minY) {
            return false;
        }
    }
    return true;
}

long long solvePart2(const vector<Point>& tiles) {
    const int n = tiles.size();
    long long maxArea = 0;
    const vector<Edge> edges = getNormalizedEdges(tiles);
    
    for (int i = 0; i < n - 1; i++) {
        const int x1 = tiles[i].x;
        const int y1 = tiles[i].y;
        
        for (int j = i + 1; j < n; j++) {
            const int x2 = tiles[j].x;
            const int y2 = tiles[j].y;
            
            const long long area = ((long long)abs(x1 - x2) + 1) * (abs(y1 - y2) + 1);
            
            if (area <= maxArea) continue;
            
            const int minX = min(x1, x2);
            const int maxX = max(x1, x2);
            const int minY = min(y1, y2);
            const int maxY = max(y1, y2);
            
            if (isFullyContained(edges, minX, minY, maxX, maxY)) {
                maxArea = area;
            }
        }
    }
    
    return maxArea;
}

int main() {
    ifstream file("../inputs/day-9-input.txt");
    vector<Point> tiles;
    tiles.reserve(500);
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Point p;
        
        getline(ss, token, ',');
        p.x = stoi(token);
        getline(ss, token, ',');
        p.y = stoi(token);
        
        tiles.push_back(p);
    }
    file.close();
    
    const int iterations = 1;
    auto start = chrono::high_resolution_clock::now();
    
    long long result;
    for (int i = 0; i < iterations; i++) {
        result = solvePart2(tiles);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double avgMicros = duration.count() / (double)iterations / 1000.0;
    
    cout << "C++ (Day 9 Part 2 - Optimized)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

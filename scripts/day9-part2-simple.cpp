#include <iostream>
#include <fstream>
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

vector<Edge> getNormalizedEdges(const vector<Point>& tiles) {
    vector<Edge> edges;
    int n = tiles.size();
    
    for (int i = 0; i < n - 1; i++) {
        edges.push_back({
            min(tiles[i].x, tiles[i+1].x),
            min(tiles[i].y, tiles[i+1].y),
            max(tiles[i].x, tiles[i+1].x),
            max(tiles[i].y, tiles[i+1].y)
        });
    }
    
    // Wrap around from last to first
    edges.push_back({
        min(tiles[n-1].x, tiles[0].x),
        min(tiles[n-1].y, tiles[0].y),
        max(tiles[n-1].x, tiles[0].x),
        max(tiles[n-1].y, tiles[0].y)
    });
    
    return edges;
}

bool isFullyContained(const vector<Edge>& edges, int minX, int minY, int maxX, int maxY) {
    for (const auto& edge : edges) {
        if (minX < edge.maxX && maxX > edge.minX && minY < edge.maxY && maxY > edge.minY) {
            return false;
        }
    }
    return true;
}

long long solvePart2(const vector<Point>& tiles) {
    int n = tiles.size();
    long long maxArea = 0;
    vector<Edge> edges = getNormalizedEdges(tiles);
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            long long area = ((long long)abs(tiles[i].x - tiles[j].x) + 1) * 
                            (abs(tiles[i].y - tiles[j].y) + 1);
            
            if (area <= maxArea) continue;
            
            int minX = min(tiles[i].x, tiles[j].x);
            int maxX = max(tiles[i].x, tiles[j].x);
            int minY = min(tiles[i].y, tiles[j].y);
            int maxY = max(tiles[i].y, tiles[j].y);
            
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
    
    cout << "C++ (Day 9 Part 2 - Simple)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

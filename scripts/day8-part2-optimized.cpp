#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <sstream>

using namespace std;

struct Junction {
    double x, y, z;
};

double distance(const Junction& p1, const Junction& p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    double dz = p1.z - p2.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

class UnionFind {
public:
    vector<int> parent;
    vector<int> size;
    int numComponents;
    
    UnionFind(int n) : parent(n), size(n, 1), numComponents(n) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    bool unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) return false;
        
        if (size[rootX] < size[rootY]) {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        } else {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
        
        numComponents--;
        return true;
    }
};

long long solvePart2(const vector<Junction>& junctions) {
    int n = junctions.size();
    
    // Create all pairs with their distances
    vector<pair<double, pair<int, int>>> pairs;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            pairs.push_back({distance(junctions[i], junctions[j]), {i, j}});
        }
    }
    
    // Sort by distance
    sort(pairs.begin(), pairs.end());
    
    // Connect pairs until all are in one circuit
    UnionFind uf(n);
    pair<int, int> lastConnection;
    
    for (const auto& pair : pairs) {
        if (uf.unionSets(pair.second.first, pair.second.second)) {
            lastConnection = pair.second;
            if (uf.numComponents == 1) {
                break;
            }
        }
    }
    
    // Return product of X coordinates
    long long x1 = (long long)junctions[lastConnection.first].x;
    long long x2 = (long long)junctions[lastConnection.second].x;
    return x1 * x2;
}

int main() {
    // Read input
    ifstream file("../inputs/day-8-input.txt");
    vector<Junction> junctions;
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Junction j;
        
        getline(ss, token, ',');
        j.x = stod(token);
        getline(ss, token, ',');
        j.y = stod(token);
        getline(ss, token, ',');
        j.z = stod(token);
        
        junctions.push_back(j);
    }
    file.close();
    
    // Benchmark
    const int iterations = 1;
    auto start = chrono::high_resolution_clock::now();
    
    long long result;
    for (int i = 0; i < iterations; i++) {
        result = solvePart2(junctions);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double avgMicros = duration.count() / (double)iterations / 1000.0;
    
    cout << "C++ (Day 8 Part 2 - Optimized)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

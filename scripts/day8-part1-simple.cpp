#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <sstream>
#include <map>

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
    
    UnionFind(int n) : parent(n), size(n, 1) {
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
        
        return true;
    }
    
    vector<int> getCircuitSizes() {
        map<int, int> circuits;
        for (int i = 0; i < parent.size(); i++) {
            int root = find(i);
            circuits[root] = size[root];
        }
        
        vector<int> sizes;
        for (const auto& [root, sz] : circuits) {
            sizes.push_back(sz);
        }
        sort(sizes.rbegin(), sizes.rend());
        return sizes;
    }
};

struct Pair {
    int i, j;
    double dist;
};

long long solvePart1(const vector<Junction>& junctions) {
    int n = junctions.size();
    
    // Create all pairs with their distances
    vector<Pair> pairs;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            pairs.push_back({i, j, distance(junctions[i], junctions[j])});
        }
    }
    
    // Sort by distance
    sort(pairs.begin(), pairs.end(), [](const Pair& a, const Pair& b) {
        return a.dist < b.dist;
    });
    
    // Connect the 1000 shortest pairs
    UnionFind uf(n);
    int limit = min(1000, (int)pairs.size());
    for (int k = 0; k < limit; k++) {
        uf.unionSets(pairs[k].i, pairs[k].j);
    }
    
    // Get circuit sizes
    vector<int> sizes = uf.getCircuitSizes();
    
    // Multiply the three largest
    return (long long)sizes[0] * sizes[1] * sizes[2];
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
        result = solvePart1(junctions);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double avgMicros = duration.count() / (double)iterations / 1000.0;
    
    cout << "C++ (Day 8 Part 1 - Simple)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

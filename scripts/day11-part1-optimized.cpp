#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <sstream>
#include <chrono>

using namespace std;

unordered_map<string, size_t> cache;

size_t dfs(const string& current, const string& target, 
           const map<string, vector<string>>& graph) {
    if (current == target) {
        return 1;
    }
    
    if (cache.find(current) != cache.end()) {
        return cache[current];
    }
    
    auto it = graph.find(current);
    if (it == graph.end()) {
        cache[current] = 0;
        return 0;
    }
    
    size_t count = 0;
    for (const auto& next : it->second) {
        count += dfs(next, target, graph);
    }
    
    cache[current] = count;
    return count;
}

size_t solvePart1(const map<string, vector<string>>& graph) {
    cache.clear();
    return dfs("you", "out", graph);
}

int main() {
    ifstream file("../inputs/day-11-input.txt");
    map<string, vector<string>> graph;
    string line;
    
    while (getline(file, line)) {
        size_t colonPos = line.find(':');
        if (colonPos != string::npos) {
            string from = line.substr(0, colonPos);
            string rest = line.substr(colonPos + 2);
            
            vector<string> tos;
            istringstream iss(rest);
            string to;
            while (iss >> to) {
                tos.push_back(to);
            }
            
            graph[from] = tos;
        }
    }
    file.close();
    
    const int iterations = 1;
    auto start = chrono::high_resolution_clock::now();
    
    size_t result;
    for (int i = 0; i < iterations; i++) {
        result = solvePart1(graph);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double avgMicros = duration.count() / (double)iterations / 1000.0;
    
    cout << "C++ (Day 11 Part 1 - Optimized)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

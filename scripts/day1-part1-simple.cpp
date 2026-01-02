#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
using namespace std;

int solvePart1(const vector<string>& rotations) {
    int position = 50;
    int count = 0;
    
    for (const auto& rotation : rotations) {
        char direction = rotation[0];
        int distance = stoi(rotation.substr(1));
        
        if (direction == 'L') {
            position -= distance;
        } else {
            position += distance;
        }
        
        // Handle wrap-around
        position = ((position % 100) + 100) % 100;
        
        // Check if at zero
        if (position == 0) {
            count++;
        }
    }
    
    return count;
}

int main() {
    // Read input file
    ifstream file("../inputs/day-1-input.txt");
    vector<string> rotations;
    string line;
    
    while (getline(file, line)) {
        if (!line.empty()) {
            rotations.push_back(line);
        }
    }
    file.close();
    
    // Benchmark
    const int iterations = 1;
    int result = 0;
    
    auto start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; i++) {
        result = solvePart1(rotations);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    
    double total_ms = duration.count() / 1'000'000.0;
    double avg_micros = duration.count() / 1000.0 / iterations;
    
    cout << "C++ (Simple Version)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << fixed << setprecision(3) 
         << avg_micros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << fixed << setprecision(2) 
         << total_ms << " ms" << endl;
    
    return 0;
}

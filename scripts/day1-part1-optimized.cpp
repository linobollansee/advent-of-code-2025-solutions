#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>

int solvePart1Optimized(const std::vector<std::string>& rotations) {
    int position = 50;
    int count = 0;
    
    for (const auto& rotation : rotations) {
        char direction = rotation[0];
        int distance = std::stoi(rotation.substr(1));
        
        if (direction == 'L') {
            position = (position - distance % 100 + 100) % 100;
        } else { // 'R'
            position = (position + distance) % 100;
        }
        
        if (position == 0) {
            count++;
        }
    }
    
    return count;
}

int main() {
    // Read and parse input
    std::ifstream infile("../inputs/day-1-input.txt");
    std::vector<std::string> rotations;
    std::string line;
    
    while (std::getline(infile, line)) {
        if (!line.empty()) {
            rotations.push_back(line);
        }
    }
    infile.close();
    
    // Benchmark
    const int iterations = 1;
    int result = 0;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    for (int i = 0; i < iterations; i++) {
        result = solvePart1Optimized(rotations);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    
    double total_ms = duration.count() / 1'000'000.0;
    double avg_micros = duration.count() / 1000.0 / iterations;
    
    std::cout << "C++" << std::endl;
    std::cout << "Answer: " << result << std::endl;
    std::cout << "Average time: " << std::fixed << std::setprecision(3) 
              << avg_micros << " microseconds (" << iterations << " iterations)" << std::endl;
    std::cout << "Total time: " << std::fixed << std::setprecision(2) 
              << total_ms << " ms" << std::endl;
    
    return 0;
}

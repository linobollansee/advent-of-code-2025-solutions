#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <chrono>
#include <limits>

using namespace std;

struct Machine {
    string lights;
    vector<vector<int>> buttons;
    vector<int> joltages;
};

Machine parseMachine(const string& line) {
    Machine m;
    regex pattern(R"(\[(.*?)\](.*)\{(.*)\})");
    smatch match;
    regex_search(line, match, pattern);
    
    m.lights = match[1];
    string buttonsStr = match[2];
    string joltagesStr = match[3];
    
    // Parse joltages
    size_t pos = 0;
    while ((pos = joltagesStr.find(',')) != string::npos) {
        m.joltages.push_back(stoi(joltagesStr.substr(0, pos)));
        joltagesStr.erase(0, pos + 1);
    }
    m.joltages.push_back(stoi(joltagesStr));
    
    // Parse buttons
    regex buttonPattern(R"(\(([0-9,]+)\))");
    sregex_iterator iter(buttonsStr.begin(), buttonsStr.end(), buttonPattern);
    sregex_iterator end;
    
    while (iter != end) {
        vector<int> button;
        string btnStr = (*iter)[1];
        size_t p = 0;
        while ((p = btnStr.find(',')) != string::npos) {
            button.push_back(stoi(btnStr.substr(0, p)));
            btnStr.erase(0, p + 1);
        }
        button.push_back(stoi(btnStr));
        m.buttons.push_back(button);
        ++iter;
    }
    
    return m;
}

int solvePart1(const vector<Machine>& machines) {
    int total = 0;
    
    for (const auto& machine : machines) {
        vector<int> target;
        target.reserve(machine.lights.size());
        for (char c : machine.lights) {
            target.push_back(c == '#' ? 1 : 0);
        }
        
        const int n = target.size();
        const int m = machine.buttons.size();
        int minPresses = numeric_limits<int>::max();
        const int limit = 1 << m;
        
        for (int mask = 0; mask < limit; mask++) {
            vector<int> state(n, 0);
            int presses = 0;
            
            for (int i = 0; i < m; i++) {
                if (mask & (1 << i)) {
                    presses++;
                    for (int light : machine.buttons[i]) {
                        state[light] ^= 1;
                    }
                }
            }
            
            if (state == target && presses < minPresses) {
                minPresses = presses;
            }
        }
        
        total += minPresses;
    }
    
    return total;
}

int main() {
    ifstream file("../inputs/day-10-input.txt");
    vector<Machine> machines;
    machines.reserve(200);
    string line;
    
    while (getline(file, line)) {
        machines.push_back(parseMachine(line));
    }
    file.close();
    
    const int iterations = 1;
    auto start = chrono::high_resolution_clock::now();
    
    int result;
    for (int i = 0; i < iterations; i++) {
        result = solvePart1(machines);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double avgMicros = duration.count() / (double)iterations / 1000.0;
    
    cout << "C++ (Day 10 Part 1 - Optimized)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

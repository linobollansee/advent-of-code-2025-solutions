#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <chrono>
#include <unordered_map>
#include <bitset>

using namespace std;

struct Machine {
    string lights;
    vector<vector<int>> buttons;
    vector<int> joltages;
};

struct VectorHasher {
    size_t operator()(const vector<int>& v) const {
        size_t hash = 0;
        for (int i : v) {
            hash = hash * 31 + i;
        }
        return hash;
    }
};

Machine parseMachine(const string& line) {
    Machine m;
    regex pattern(R"(\[(.*?)\](.*)\{(.*)\})");
    smatch match;
    regex_search(line, match, pattern);
    
    m.lights = match[1];
    string buttonsStr = match[2];
    string joltagesStr = match[3];
    
    size_t pos = 0;
    while ((pos = joltagesStr.find(',')) != string::npos) {
        m.joltages.push_back(stoi(joltagesStr.substr(0, pos)));
        joltagesStr.erase(0, pos + 1);
    }
    m.joltages.push_back(stoi(joltagesStr));
    
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

unordered_map<vector<int>, unordered_map<vector<int>, int, VectorHasher>, VectorHasher> 
getAllParityMaps(int nCounters, const vector<vector<int>>& switches) {
    unordered_map<vector<int>, unordered_map<vector<int>, int, VectorHasher>, VectorHasher> parityMaps;
    
    for (int i = 0; i < (1 << switches.size()); i++) {
        bitset<16> bits(i);
        vector<int> result(nCounters, 0);
        
        for (size_t j = 0; j < switches.size(); j++) {
            if (bits[j]) {
                for (int ele : switches[j]) {
                    result[ele]++;
                }
            }
        }
        
        vector<int> parityKey;
        for (int ele : result) {
            parityKey.push_back(ele % 2);
        }
        
        int nFlips = bits.count();
        
        if (parityMaps[parityKey].find(result) == parityMaps[parityKey].end() ||
            parityMaps[parityKey][result] > nFlips) {
            parityMaps[parityKey][result] = nFlips;
        }
    }
    
    return parityMaps;
}

pair<bool, int> findMinSwitchFlips(
    const vector<int>& current,
    const vector<vector<int>>& switches,
    const unordered_map<vector<int>, unordered_map<vector<int>, int, VectorHasher>, VectorHasher>& parityMaps,
    unordered_map<vector<int>, pair<bool, int>, VectorHasher>& cache
) {
    auto it = cache.find(current);
    if (it != cache.end()) {
        return it->second;
    }
    
    bool allZero = true;
    for (int x : current) {
        if (x != 0) {
            allZero = false;
            break;
        }
    }
    if (allZero) {
        cache[current] = {true, 0};
        return {true, 0};
    }
    
    for (int x : current) {
        if (x < 0) {
            cache[current] = {false, 0};
            return {false, 0};
        }
    }
    
    vector<int> currentParity;
    for (int c : current) {
        currentParity.push_back(c % 2);
    }
    
    auto pmIt = parityMaps.find(currentParity);
    if (pmIt == parityMaps.end()) {
        cache[current] = {false, 0};
        return {false, 0};
    }
    
    int minFlips = 999999;
    
    for (const auto& [pattern, nFlips] : pmIt->second) {
        bool valid = true;
        for (size_t i = 0; i < pattern.size(); i++) {
            if (pattern[i] > current[i]) {
                valid = false;
                break;
            }
        }
        
        if (!valid) continue;
        
        vector<int> next;
        next.reserve(current.size());
        for (size_t i = 0; i < current.size(); i++) {
            next.push_back((current[i] - pattern[i]) / 2);
        }
        
        auto [found, count] = findMinSwitchFlips(next, switches, parityMaps, cache);
        
        if (found) {
            minFlips = min(minFlips, nFlips + 2 * count);
        }
    }
    
    if (minFlips == 999999) {
        cache[current] = {false, 0};
        return {false, 0};
    }
    
    cache[current] = {true, minFlips};
    return {true, minFlips};
}

int solvePart2(const vector<Machine>& machines) {
    int total = 0;
    
    for (const auto& machine : machines) {
        auto parityMaps = getAllParityMaps(machine.joltages.size(), machine.buttons);
        unordered_map<vector<int>, pair<bool, int>, VectorHasher> cache;
        auto [found, count] = findMinSwitchFlips(machine.joltages, machine.buttons, parityMaps, cache);
        total += count;
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
        result = solvePart2(machines);
    }
    
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    double avgMicros = duration.count() / (double)iterations / 1000.0;
    
    cout << "C++ (Day 10 Part 2 - Optimized)" << endl;
    cout << "Answer: " << result << endl;
    cout << "Average time: " << avgMicros << " microseconds (" << iterations << " iterations)" << endl;
    cout << "Total time: " << (duration.count() / 1000000.0) << " ms" << endl;
    
    return 0;
}

import time
import re

def parse_machine(line):
    match = re.match(r'\[(.*?)\](.*)\{(.*)\}', line)
    lights = match.group(1)
    buttons_str = match.group(2).strip()
    joltages = list(map(int, match.group(3).split(',')))
    
    buttons = []
    for button_match in re.finditer(r'\(([0-9,]+)\)', buttons_str):
        buttons.append(list(map(int, button_match.group(1).split(','))))
    
    return {'lights': lights, 'buttons': buttons, 'joltages': joltages}

def get_all_parity_maps(n_counters, switches):
    parity_maps = {}
    
    for i in range(1 << len(switches)):
        result = [0] * n_counters
        n_flips = 0
        
        for j in range(len(switches)):
            if i & (1 << j):
                n_flips += 1
                for ele in switches[j]:
                    result[ele] += 1
        
        parity_key = tuple(x % 2 for x in result)
        result_key = tuple(result)
        
        if parity_key not in parity_maps:
            parity_maps[parity_key] = {}
        
        if result_key not in parity_maps[parity_key] or \
           parity_maps[parity_key][result_key] > n_flips:
            parity_maps[parity_key][result_key] = n_flips
    
    return parity_maps

def find_min_switch_flips(current, switches, parity_maps, cache):
    key = tuple(current)
    
    if key in cache:
        return cache[key]
    
    if all(x == 0 for x in current):
        cache[key] = (True, 0)
        return (True, 0)
    
    if any(x < 0 for x in current):
        cache[key] = (False, 0)
        return (False, 0)
    
    current_parity = tuple(x % 2 for x in current)
    
    if current_parity not in parity_maps:
        cache[key] = (False, 0)
        return (False, 0)
    
    min_flips = float('inf')
    
    for pattern, n_flips in parity_maps[current_parity].items():
        # Check validity
        if not all(p <= c for p, c in zip(pattern, current)):
            continue
        
        next_state = tuple((c - p) // 2 for c, p in zip(current, pattern))
        found, count = find_min_switch_flips(list(next_state), switches, parity_maps, cache)
        
        if found:
            min_flips = min(min_flips, n_flips + 2 * count)
    
    if min_flips == float('inf'):
        cache[key] = (False, 0)
        return (False, 0)
    
    cache[key] = (True, min_flips)
    return (True, min_flips)

def solve_part2(machines):
    total = 0
    
    for machine in machines:
        parity_maps = get_all_parity_maps(len(machine['joltages']), machine['buttons'])
        cache = {}
        found, count = find_min_switch_flips(machine['joltages'], machine['buttons'], parity_maps, cache)
        total += count
    
    return total

# Read input
with open("../inputs/day-10-input.txt", "r") as f:
    input_data = f.read().strip().split('\n')

machines = [parse_machine(line) for line in input_data]

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part2(machines)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 10 Part 2 - Simple)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

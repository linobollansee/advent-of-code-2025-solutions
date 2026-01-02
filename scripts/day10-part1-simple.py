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

def solve_part1(machines):
    total = 0
    
    for machine in machines:
        target = [1 if c == '#' else 0 for c in machine['lights']]
        n = len(target)
        m = len(machine['buttons'])
        
        # Try all combinations
        min_presses = float('inf')
        for mask in range(1 << m):
            state = [0] * n
            presses = 0
            
            for i in range(m):
                if mask & (1 << i):
                    presses += 1
                    for light in machine['buttons'][i]:
                        state[light] ^= 1
            
            if state == target:
                min_presses = min(min_presses, presses)
        
        total += min_presses
    
    return total

# Read input
with open("../inputs/day-10-input.txt", "r") as f:
    input_data = f.read().strip().split('\n')

machines = [parse_machine(line) for line in input_data]

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part1(machines)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 10 Part 1 - Simple)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

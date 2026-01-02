import time

def solve_part1(banks):
    total_joltage = 0
    
    for bank in banks:
        max_joltage = 0
        
        for i in range(len(bank)):
            for j in range(i + 1, len(bank)):
                two_digit = int(bank[i] + bank[j])
                max_joltage = max(max_joltage, two_digit)
        
        total_joltage += max_joltage
    
    return total_joltage

# Read input
with open("../inputs/day-3-input.txt", "r") as f:
    input_data = f.read().strip().split('\n')

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part1(input_data)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 3 Part 1 - Simple)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

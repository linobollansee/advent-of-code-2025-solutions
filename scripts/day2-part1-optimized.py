import time

def is_repeated_twice(num):
    """Optimized version - same as simple for this problem"""
    s = str(num)
    length = len(s)
    
    if length % 2 != 0:
        return False
    
    half = length // 2
    first_half = s[:half]
    second_half = s[half:]
    
    return first_half == second_half

def solve_part1(input_data):
    ranges = [r.strip() for r in input_data.split(',') if r.strip()]
    total = 0
    
    for range_str in ranges:
        start, end = map(int, range_str.split('-'))
        
        for id_num in range(start, end + 1):
            if is_repeated_twice(id_num):
                total += id_num
    
    return total

# Read input
with open("../inputs/day-2-input.txt", "r") as f:
    input_data = f.read().strip()

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part1(input_data)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 2 Part 1 - Optimized)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

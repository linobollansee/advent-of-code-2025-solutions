import time

def solve_part1(input_data):
    parts = input_data.strip().split('\n\n')
    
    ranges = []
    for line in parts[0].split('\n'):
        start, end = map(int, line.split('-'))
        ranges.append((start, end))
    
    available_ids = list(map(int, parts[1].split('\n'))) if len(parts) > 1 else []
    
    fresh_count = 0
    
    for id_num in available_ids:
        is_fresh = False
        
        for start, end in ranges:
            if start <= id_num <= end:
                is_fresh = True
                break
        
        if is_fresh:
            fresh_count += 1
    
    return fresh_count

# Read input
with open("../inputs/day-5-input.txt", "r") as f:
    input_data = f.read()

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part1(input_data)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 5 Part 1 - Simple)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

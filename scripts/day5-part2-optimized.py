import time

def solve_part2(input_data):
    parts = input_data.strip().split('\n\n')
    
    ranges = []
    for line in parts[0].split('\n'):
        start, end = map(int, line.split('-'))
        ranges.append((start, end))
    
    # Sort and merge overlapping ranges
    ranges.sort(key=lambda x: x[0])
    
    total_count = 0
    current_start = ranges[0][0]
    current_end = ranges[0][1]
    
    for i in range(1, len(ranges)):
        start, end = ranges[i]
        if start <= current_end + 1:
            current_end = max(current_end, end)
        else:
            total_count += current_end - current_start + 1
            current_start = start
            current_end = end
    
    total_count += current_end - current_start + 1
    
    return total_count

# Read input
with open("../inputs/day-5-input.txt", "r") as f:
    input_data = f.read()

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part2(input_data)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 5 Part 2 - Optimized)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

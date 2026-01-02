import time

def solve_part2(input_data):
    parts = input_data.strip().split('\n\n')
    
    ranges = []
    for line in parts[0].split('\n'):
        start, end = map(int, line.split('-'))
        ranges.append((start, end))
    
    # Merge overlapping ranges to avoid double counting
    merged = []
    sorted_ranges = sorted(ranges, key=lambda x: x[0])
    
    for start, end in sorted_ranges:
        if not merged:
            merged.append([start, end])
        else:
            last = merged[-1]
            
            # If current range overlaps or is adjacent to the last one, merge them
            if start <= last[1] + 1:
                last[1] = max(last[1], end)
            else:
                merged.append([start, end])
    
    # Count all IDs in the merged ranges
    total_count = 0
    for start, end in merged:
        total_count += end - start + 1
    
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

print(f"Python (Day 5 Part 2 - Simple)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

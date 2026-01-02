import time

def solve_part1(points):
    max_area = 0
    n = len(points)
    
    # Optimized: Try all pairs of points as opposite corners
    for i in range(n - 1):
        x1, y1 = points[i]
        for j in range(i + 1, n):
            x2, y2 = points[j]
            
            # Calculate rectangle area (inclusive of both endpoints)
            width = abs(x2 - x1) + 1
            height = abs(y2 - y1) + 1
            area = width * height
            
            if area > max_area:
                max_area = area
    
    return max_area

# Read input
with open("../inputs/day-9-input.txt", "r") as f:
    input_data = f.read().strip().split('\n')

points = [list(map(int, line.split(','))) for line in input_data]

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part1(points)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 9 Part 1 - Optimized)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

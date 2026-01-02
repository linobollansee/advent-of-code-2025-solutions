import time

def solve(grid):
    rows = len(grid)
    cols = len(grid[0])
    accessible_count = 0
    
    directions = [
        (-1, -1), (-1, 0), (-1, 1),
        (0, -1), (0, 1),
        (1, -1), (1, 0), (1, 1)
    ]
    
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == '@':
                adjacent_rolls = 0
                
                for dr, dc in directions:
                    nr, nc = r + dr, c + dc
                    
                    if 0 <= nr < rows and 0 <= nc < cols and grid[nr][nc] == '@':
                        adjacent_rolls += 1
                
                if adjacent_rolls < 4:
                    accessible_count += 1
    
    return accessible_count

# Read input
with open("../inputs/day-4-input.txt", "r") as f:
    input_data = f.read().strip().split('\n')

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve(input_data)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 4 Part 1 - Optimized)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

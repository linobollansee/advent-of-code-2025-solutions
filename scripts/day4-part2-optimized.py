import time

def solve_part2(grid):
    mutable_grid = [list(row) for row in grid]
    rows = len(mutable_grid)
    cols = len(mutable_grid[0])
    
    directions = [
        (-1, -1), (-1, 0), (-1, 1),
        (0, -1), (0, 1),
        (1, -1), (1, 0), (1, 1)
    ]
    
    total_removed = 0
    
    while True:
        accessible = []
        
        for r in range(rows):
            for c in range(cols):
                if mutable_grid[r][c] == '@':
                    adjacent_rolls = 0
                    
                    for dr, dc in directions:
                        nr, nc = r + dr, c + dc
                        
                        if 0 <= nr < rows and 0 <= nc < cols and mutable_grid[nr][nc] == '@':
                            adjacent_rolls += 1
                    
                    if adjacent_rolls < 4:
                        accessible.append((r, c))
        
        if not accessible:
            break
        
        for r, c in accessible:
            mutable_grid[r][c] = '.'
        
        total_removed += len(accessible)
    
    return total_removed

# Read input
with open("../inputs/day-4-input.txt", "r") as f:
    input_data = f.read().strip().split('\n')

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part2(input_data)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 4 Part 2 - Optimized)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

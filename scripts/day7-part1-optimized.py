import time

def solve_part1(grid):
    rows = len(grid)
    cols = len(grid[0])
    
    # Find the starting position 'S'
    start_col = grid[0].index('S')
    
    # Simulate tachyon beams using BFS
    beams = [(0, start_col)]
    visited = {(0, start_col)}
    
    while beams:
        new_beams = []
        
        for row, col in beams:
            new_row = row + 1
            if new_row >= rows:
                continue
            
            cell = grid[new_row][col]
            
            if cell == '.':
                key = (new_row, col)
                if key not in visited:
                    visited.add(key)
                    new_beams.append((new_row, col))
            elif cell == '^':
                visited.add((new_row, col))
                
                if col > 0:
                    left_key = (new_row, col - 1)
                    if left_key not in visited:
                        visited.add(left_key)
                        new_beams.append((new_row, col - 1))
                
                if col < cols - 1:
                    right_key = (new_row, col + 1)
                    if right_key not in visited:
                        visited.add(right_key)
                        new_beams.append((new_row, col + 1))
        
        beams = new_beams
    
    # Count activated splitters
    count = 0
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == '^' and (r, c) in visited:
                count += 1
    
    return count

# Read input
with open("../inputs/day-7-input.txt", "r") as f:
    input_data = f.read().strip().split('\n')

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part1(input_data)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 7 Part 1 - Optimized)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

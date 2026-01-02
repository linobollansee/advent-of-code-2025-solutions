import time

def solve_part1(grid):
    rows = len(grid)
    cols = len(grid[0])
    
    # Find the starting position 'S'
    start_col = -1
    for c in range(cols):
        if grid[0][c] == 'S':
            start_col = c
            break
    
    # Simulate tachyon beams
    beams = [(0, start_col)]
    beam_positions = set()
    
    while beams:
        new_beams = []
        
        for row, col in beams:
            # Move beam down
            new_row = row + 1
            
            if new_row >= rows:
                continue  # Beam exits
            
            cell = grid[new_row][col]
            
            if cell == '.':
                # Continue downward
                key = (new_row, col)
                if key not in beam_positions:
                    beam_positions.add(key)
                    new_beams.append((new_row, col))
            elif cell == '^':
                # Split into left and right beams
                beam_positions.add((new_row, col))
                
                # Left beam
                if col - 1 >= 0:
                    left_key = (new_row, col - 1)
                    if left_key not in beam_positions:
                        beam_positions.add(left_key)
                        new_beams.append((new_row, col - 1))
                
                # Right beam
                if col + 1 < cols:
                    right_key = (new_row, col + 1)
                    if right_key not in beam_positions:
                        beam_positions.add(right_key)
                        new_beams.append((new_row, col + 1))
        
        beams = new_beams
    
    # Count splitters that were activated
    activated_splitters = 0
    for r in range(rows):
        for c in range(cols):
            if grid[r][c] == '^' and (r, c) in beam_positions:
                activated_splitters += 1
    
    return activated_splitters

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

print(f"Python (Day 7 Part 1 - Simple)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

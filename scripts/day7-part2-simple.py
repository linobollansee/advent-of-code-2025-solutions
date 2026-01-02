import time

def solve_part2(grid):
    rows = len(grid)
    cols = len(grid[0])
    
    # Find the starting position 'S'
    start_col = -1
    for c in range(cols):
        if grid[0][c] == 'S':
            start_col = c
            break
    
    # BFS approach - process level by level
    current_states = {(0, start_col, 'down'): 1}
    
    for row in range(rows):
        next_states = {}
        
        for state_key, count in current_states.items():
            r, c, direction = state_key
            
            if r != row:
                continue
            
            cell = grid[r][c]
            
            if cell == '.' or cell == 'S':
                # Continue downward
                next_key = (r + 1, c, 'down')
                next_states[next_key] = next_states.get(next_key, 0) + count
            elif cell == '^':
                # Quantum split - creates two timelines for each incoming timeline
                # Left path
                if c - 1 >= 0:
                    left_key = (r + 1, c - 1, 'left')
                    next_states[left_key] = next_states.get(left_key, 0) + count
                # Right path
                if c + 1 < cols:
                    right_key = (r + 1, c + 1, 'right')
                    next_states[right_key] = next_states.get(right_key, 0) + count
        
        current_states = next_states
    
    # Count total timelines that exited
    total_timelines = sum(current_states.values())
    
    return total_timelines

# Read input
with open("../inputs/day-7-input.txt", "r") as f:
    input_data = f.read().strip().split('\n')

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part2(input_data)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 7 Part 2 - Simple)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

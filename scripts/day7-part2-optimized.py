import time

def solve_part2(grid):
    rows = len(grid)
    cols = len(grid[0])
    
    # Find the starting position 'S'
    start_col = grid[0].index('S')
    
    # Track timelines per state
    current_states = {(0, start_col): 1}
    
    for row in range(rows):
        next_states = {}
        
        for (r, c), count in current_states.items():
            if r != row:
                continue
            
            cell = grid[r][c]
            
            if cell == '.' or cell == 'S':
                next_key = (r + 1, c)
                next_states[next_key] = next_states.get(next_key, 0) + count
            elif cell == '^':
                if c > 0:
                    left_key = (r + 1, c - 1)
                    next_states[left_key] = next_states.get(left_key, 0) + count
                if c < cols - 1:
                    right_key = (r + 1, c + 1)
                    next_states[right_key] = next_states.get(right_key, 0) + count
        
        current_states = next_states
    
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

print(f"Python (Day 7 Part 2 - Optimized)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

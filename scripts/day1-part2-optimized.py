import time

def solve_part2(rotations):
    """Optimized version - calculate crossings without iterating"""
    position = 50
    count = 0
    
    for rotation in rotations:
        direction = rotation[0]
        distance = int(rotation[1:])
        
        if direction == 'L':
            # Count full rotations
            full_rotations = distance // 100
            count += full_rotations
            
            # Check if partial rotation crosses 0
            remainder = distance % 100
            new_pos = (position - remainder) % 100
            
            # Cross 0 if: remainder >= position and position > 0
            if remainder >= position and position > 0:
                count += 1
            
            position = new_pos
        else:
            # Count crossings going right
            crossings = (position + distance) // 100
            count += crossings
            position = (position + distance) % 100
    
    return count

# Read input
with open("../inputs/day-1-input.txt", "r") as f:
    input_data = f.read().strip().split('\n')

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part2(input_data)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 1 Part 2 - Optimized)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

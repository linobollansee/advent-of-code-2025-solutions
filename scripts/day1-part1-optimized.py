import time

def solve_part1_optimized(rotations):
    """Optimized Part 1: Count times dial points at 0 after rotations"""
    position = 50
    count = 0
    
    for rotation in rotations:
        direction = rotation[0]
        distance = int(rotation[1:])
        
        if direction == 'L':
            position = (position - distance % 100 + 100) % 100
        else:  # 'R'
            position = (position + distance) % 100
        
        if position == 0:
            count += 1
    
    return count

# Read and parse input
with open("../inputs/day-1-input.txt", "r") as f:
    input_data = [line.strip() for line in f if line.strip()]

# Benchmark
iterations = 1
start_time = time.perf_counter()

result = 0
for _ in range(iterations):
    result = solve_part1_optimized(input_data)

end_time = time.perf_counter()
total_time = (end_time - start_time)
avg_micros = (total_time / iterations) * 1_000_000

print(f"Python")
print(f"Answer: {result}")
print(f"Average time: {avg_micros:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

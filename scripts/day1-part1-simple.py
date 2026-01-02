import time

# Read input file
with open("../inputs/day-1-input.txt") as f:
    rotations = f.read().strip().split("\n")

def solve_part1(rotations):
    position = 50
    count = 0

    for rotation in rotations:
        direction = rotation[0]
        distance = int(rotation[1:])
        
        if direction == "L":
            position -= distance
        else:
            position += distance
        
        # Handle wrap-around
        position = position % 100
        
        # Check if at zero
        if position == 0:
            count += 1
    
    return count

# Benchmark
iterations = 1
start_time = time.perf_counter()

result = 0
for _ in range(iterations):
    result = solve_part1(rotations)

end_time = time.perf_counter()
total_time = (end_time - start_time)
avg_micros = (total_time / iterations) * 1_000_000

print(f"Python (Simple Version)")
print(f"Answer: {result}")
print(f"Average time: {avg_micros:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

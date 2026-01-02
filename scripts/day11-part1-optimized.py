import time

def dfs(current, target, graph, cache=None):
    if cache is None:
        cache = {}
    
    if current == target:
        return 1
    
    if current in cache:
        return cache[current]
    
    if current not in graph:
        cache[current] = 0
        return 0
    
    count = 0
    for next_node in graph[current]:
        count += dfs(next_node, target, graph, cache)
    
    cache[current] = count
    return count

def solve_part1(lines):
    graph = {}
    
    for line in lines:
        parts = line.split(': ')
        if len(parts) == 2:
            from_node = parts[0]
            to_nodes = parts[1].split()
            graph[from_node] = to_nodes
    
    return dfs("you", "out", graph)

# Read input
with open("../inputs/day-11-input.txt", "r") as f:
    input_data = f.read().strip().split('\n')

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part1(input_data)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 11 Part 1 - Optimized)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

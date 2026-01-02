import time

def dfs(current, visited_dac, visited_fft, graph, cache=None):
    if cache is None:
        cache = {}
    
    if current == "out" and visited_dac and visited_fft:
        return 1
    
    key = (current, visited_dac, visited_fft)
    if key in cache:
        return cache[key]
    
    if current not in graph:
        cache[key] = 0
        return 0
    
    count = 0
    for next_node in graph[current]:
        new_dac = visited_dac or next_node == "dac"
        new_fft = visited_fft or next_node == "fft"
        count += dfs(next_node, new_dac, new_fft, graph, cache)
    
    cache[key] = count
    return count

def solve_part2(lines):
    graph = {}
    
    for line in lines:
        parts = line.split(': ')
        if len(parts) == 2:
            from_node = parts[0]
            to_nodes = parts[1].split()
            graph[from_node] = to_nodes
    
    return dfs("svr", False, False, graph)

# Read input
with open("../inputs/day-11-input.txt", "r") as f:
    input_data = f.read().strip().split('\n')

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part2(input_data)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 11 Part 2 - Optimized)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

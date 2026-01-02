import time

def dfs(current, target, graph, visited=None):
    if visited is None:
        visited = set()
    
    if current == target:
        return 1
    
    if current not in graph:
        return 0
    
    count = 0
    for next_node in graph[current]:
        if next_node not in visited:
            visited.add(next_node)
            count += dfs(next_node, target, graph, visited)
            visited.remove(next_node)
    
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

print(f"Python (Day 11 Part 1 - Simple)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

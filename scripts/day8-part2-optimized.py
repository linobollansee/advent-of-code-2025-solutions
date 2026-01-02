import time
import math

def distance(p1, p2):
    dx = p1[0] - p2[0]
    dy = p1[1] - p2[1]
    dz = p1[2] - p2[2]
    return math.sqrt(dx * dx + dy * dy + dz * dz)

class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.size = [1] * n
        self.num_components = n
    
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        
        if root_x == root_y:
            return False
        
        if self.size[root_x] < self.size[root_y]:
            self.parent[root_x] = root_y
            self.size[root_y] += self.size[root_x]
        else:
            self.parent[root_y] = root_x
            self.size[root_x] += self.size[root_y]
        
        self.num_components -= 1
        return True

def solve_part2(input_data):
    junctions = [list(map(int, line.split(','))) for line in input_data]
    n = len(junctions)
    
    # Create all pairs with their distances
    pairs = []
    for i in range(n):
        for j in range(i + 1, n):
            pairs.append((distance(junctions[i], junctions[j]), i, j))
    
    # Sort by distance
    pairs.sort()
    
    # Connect pairs until all are in one circuit
    uf = UnionFind(n)
    last_connection = None
    
    for dist, i, j in pairs:
        if uf.union(i, j):
            last_connection = (i, j)
            if uf.num_components == 1:
                break
    
    # Return product of X coordinates
    return junctions[last_connection[0]][0] * junctions[last_connection[1]][0]

# Read input
with open("../inputs/day-8-input.txt", "r") as f:
    input_data = f.read().strip().split('\n')

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part2(input_data)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 8 Part 2 - Optimized)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

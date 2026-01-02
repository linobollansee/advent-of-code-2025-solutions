import time

def get_normalized_edges(tiles):
    edges = []
    n = len(tiles)
    
    for i in range(n - 1):
        edges.append({
            'minX': min(tiles[i][0], tiles[i+1][0]),
            'minY': min(tiles[i][1], tiles[i+1][1]),
            'maxX': max(tiles[i][0], tiles[i+1][0]),
            'maxY': max(tiles[i][1], tiles[i+1][1])
        })
    
    edges.append({
        'minX': min(tiles[n-1][0], tiles[0][0]),
        'minY': min(tiles[n-1][1], tiles[0][1]),
        'maxX': max(tiles[n-1][0], tiles[0][0]),
        'maxY': max(tiles[n-1][1], tiles[0][1])
    })
    
    return edges

def is_fully_contained(edges, min_x, min_y, max_x, max_y):
    for edge in edges:
        if (min_x < edge['maxX'] and max_x > edge['minX'] and 
            min_y < edge['maxY'] and max_y > edge['minY']):
            return False
    return True

def solve_part2(tiles):
    n = len(tiles)
    max_area = 0
    edges = get_normalized_edges(tiles)
    
    for i in range(n - 1):
        x1, y1 = tiles[i]
        
        for j in range(i + 1, n):
            x2, y2 = tiles[j]
            
            area = (abs(x1 - x2) + 1) * (abs(y1 - y2) + 1)
            
            if area <= max_area:
                continue
            
            min_x = min(x1, x2)
            max_x = max(x1, x2)
            min_y = min(y1, y2)
            max_y = max(y1, y2)
            
            if is_fully_contained(edges, min_x, min_y, max_x, max_y):
                max_area = area
    
    return max_area

# Read input
with open("../inputs/day-9-input.txt", "r") as f:
    input_data = f.read().strip().split('\n')

tiles = [list(map(int, line.split(','))) for line in input_data]

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part2(tiles)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 9 Part 2 - Optimized)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

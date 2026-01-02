import time
from typing import List, Dict

class Shape:
    def __init__(self, coords):
        self.coords = coords

def try_place(idx: int, presents: List[int], grid: List[List[int]], 
              width: int, height: int, shapes: Dict[int, Shape]) -> bool:
    if idx >= len(presents):
        return True
    
    shape_idx = presents[idx]
    shape = shapes[shape_idx]
    
    for r in range(height):
        for c in range(width):
            can_place = True
            for dr, dc in shape.coords:
                nr, nc = r + dr, c + dc
                if nr >= height or nc >= width or grid[nr][nc] != -1:
                    can_place = False
                    break
            
            if can_place:
                for dr, dc in shape.coords:
                    grid[r + dr][c + dc] = idx
                
                if try_place(idx + 1, presents, grid, width, height, shapes):
                    return True
                
                for dr, dc in shape.coords:
                    grid[r + dr][c + dc] = -1
    
    return False

def solve():
    with open("../inputs/day-12-input.txt") as f:
        lines = [line.rstrip() for line in f]
    
    shapes = {}
    
    # Parse shapes
    i = 0
    while i < len(lines):
        line = lines[i].strip()
        if not line:
            i += 1
            continue
        
        if line and line[0].isdigit() and ':' in line and 'x' not in line:
            shape_idx = int(line.split(':')[0])
            coords = []
            i += 1
            row = 0
            
            while i < len(lines) and lines[i].strip() and \
                  not (lines[i][0].isdigit() and ':' in lines[i]) and 'x' not in lines[i]:
                for c, ch in enumerate(lines[i]):
                    if ch == '#':
                        coords.append((row, c))
                row += 1
                i += 1
            
            shapes[shape_idx] = Shape(coords)
        else:
            i += 1
    
    # Parse regions
    regions = []
    for line in lines:
        if 'x' in line and ':' in line and line[0].isdigit():
            dims, rest = line.split(':')
            width, height = map(int, dims.split('x'))
            counts = list(map(int, rest.split()))
            
            presents = []
            for idx, count in enumerate(counts):
                presents.extend([idx] * count)
            
            regions.append({'width': width, 'height': height, 'presents': presents})
    
    fittable = 0
    
    for r in regions:
        area = r['width'] * r['height']
        needed = sum(len(shapes[p].coords) for p in r['presents'])
        
        if needed <= area:
            grid = [[-1] * r['width'] for _ in range(r['height'])]
            if try_place(0, r['presents'], grid, r['width'], r['height'], shapes):
                fittable += 1
    
    return fittable

# Benchmark
iterations = 1
start_time = time.perf_counter()

result = 0
for _ in range(iterations):
    result = solve()

end_time = time.perf_counter()
total_time = end_time - start_time
avg_ms = (total_time / iterations) * 1000

print(f"Python (Day 12 Part 1 - Simple)")
print(f"Answer: {result}")
print(f"Average time: {avg_ms:.3f} ms ({iterations} iterations)")
print(f"Total time: {total_time:.2f} s")

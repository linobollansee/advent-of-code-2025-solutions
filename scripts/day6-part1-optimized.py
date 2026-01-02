import time

def solve_part1(input_data):
    lines = input_data.split('\n')
    width = len(lines[0])
    height = len(lines)
    
    grand_total = 0
    col = 0
    
    while col < width:
        # Skip empty columns
        has_non_space = False
        for row in range(height):
            if col < len(lines[row]) and lines[row][col] != ' ':
                has_non_space = True
                break
        
        if not has_non_space:
            col += 1
            continue
        
        # Find the end of this problem
        end_col = col
        while end_col < width:
            is_all_space = True
            for row in range(height):
                if end_col < len(lines[row]) and lines[row][end_col] != ' ':
                    is_all_space = False
                    break
            if is_all_space:
                break
            end_col += 1
        
        # Extract and calculate this problem
        result = 0
        operator = '+'
        
        for row in range(height):
            cell = lines[row][col:end_col].strip()
            if cell:
                if cell == '+':
                    operator = '+'
                elif cell == '*':
                    operator = '*'
                    result = result or 1
                else:
                    num = int(cell)
                    if operator == '+':
                        result += num
                    else:
                        result = (result or 1) * num
        
        grand_total += result
        col = end_col
    
    return grand_total

# Read input
with open("../inputs/day-6-input.txt", "r") as f:
    input_data = f.read().strip()

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part1(input_data)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 6 Part 1 - Optimized)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

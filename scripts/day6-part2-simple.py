import time

def solve_part2(input_data):
    lines = input_data.split('\n')
    height = len(lines)
    width = max(len(line) for line in lines)
    
    normalized_lines = [line.ljust(width) for line in lines]
    
    problems = []
    col = width - 1
    
    while col >= 0:
        has_non_space = False
        for row in range(height):
            if normalized_lines[row][col] != ' ':
                has_non_space = True
                break
        
        if not has_non_space:
            col -= 1
            continue
        
        start_col = col
        while start_col > 0:
            is_all_space = True
            for row in range(height):
                if normalized_lines[row][start_col - 1] != ' ':
                    is_all_space = False
                    break
            if is_all_space:
                break
            start_col -= 1
        
        numbers = []
        operator = None
        
        for c in range(col, start_col - 1, -1):
            digit_str = ""
            
            for row in range(height):
                char = normalized_lines[row][c]
                if char in ('+', '*'):
                    operator = char
                elif char != ' ':
                    digit_str += char
            
            if digit_str:
                numbers.append(int(digit_str))
        
        if operator and numbers:
            problems.append({'numbers': numbers, 'operator': operator})
        
        col = start_col - 1
    
    grand_total = 0
    
    for problem in problems:
        if problem['operator'] == '+':
            result = sum(problem['numbers'])
        else:
            result = 1
            for num in problem['numbers']:
                result *= num
        grand_total += result
    
    return grand_total

# Read input
with open("../inputs/day-6-input.txt", "r") as f:
    input_data = f.read().strip()

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part2(input_data)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 6 Part 2 - Simple)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

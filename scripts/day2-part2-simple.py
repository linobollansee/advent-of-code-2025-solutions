import time

def is_repeated_at_least_twice(num):
    """Check if a number is made of some sequence repeated at least twice"""
    s = str(num)
    length = len(s)
    
    for pattern_len in range(1, length // 2 + 1):
        if length % pattern_len != 0:
            continue
        
        pattern = s[:pattern_len]
        is_valid = True
        
        for i in range(pattern_len, length, pattern_len):
            if s[i:i+pattern_len] != pattern:
                is_valid = False
                break
        
        if is_valid:
            return True
    
    return False

def solve_part2(input_data):
    ranges = [r.strip() for r in input_data.split(',') if r.strip()]
    total = 0
    
    for range_str in ranges:
        start, end = map(int, range_str.split('-'))
        
        for id_num in range(start, end + 1):
            if is_repeated_at_least_twice(id_num):
                total += id_num
    
    return total

# Read input
with open("../inputs/day-2-input.txt", "r") as f:
    input_data = f.read().strip()

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part2(input_data)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 2 Part 2 - Simple)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

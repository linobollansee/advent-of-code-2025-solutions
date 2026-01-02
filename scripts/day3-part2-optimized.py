import time

def solve_part2(banks):
    total_joltage = 0
    
    for bank in banks:
        n = len(bank)
        to_select = 12
        
        selected = []
        available_start = 0
        
        for pos in range(to_select):
            remaining = to_select - pos - 1
            must_leave_available = remaining
            can_search_until = n - must_leave_available
            
            max_digit = "0"
            max_pos = available_start
            
            for i in range(available_start, can_search_until):
                if bank[i] > max_digit:
                    max_digit = bank[i]
                    max_pos = i
            
            selected.append(max_digit)
            available_start = max_pos + 1
        
        joltage = int(''.join(selected))
        total_joltage += joltage
    
    return total_joltage

# Read input
with open("../inputs/day-3-input.txt", "r") as f:
    input_data = f.read().strip().split('\n')

# Benchmark
iterations = 1
start_time = time.perf_counter()

for _ in range(iterations):
    result = solve_part2(input_data)

end_time = time.perf_counter()
total_time = end_time - start_time
avg_time_us = (total_time / iterations) * 1_000_000

print(f"Python (Day 3 Part 2 - Optimized)")
print(f"Answer: {result}")
print(f"Average time: {avg_time_us:.3f} microseconds ({iterations} iterations)")
print(f"Total time: {total_time * 1000:.2f} ms")

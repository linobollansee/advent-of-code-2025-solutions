const fs = require("fs");

// Optimized Part 1: Count times dial points at 0 after rotations
function solvePart1Optimized(rotations) {
  let position = 50;
  let count = 0;

  for (let i = 0; i < rotations.length; i++) {
    const rotation = rotations[i];
    const direction = rotation.charCodeAt(0); // L=76, R=82
    const distance = parseInt(rotation.substring(1), 10);

    if (direction === 76) {
      // 'L'
      position = (position - (distance % 100) + 100) % 100;
    } else {
      // 'R'
      position = (position + distance) % 100;
    }

    if (position === 0) count++;
  }

  return count;
}

// Read and parse input
const input = fs
  .readFileSync("../inputs/day-1-input.txt", "utf-8")
  .trim()
  .split(/\r?\n/);

// Benchmark
const iterations = 1;
const startTime = process.hrtime.bigint();

let result;
for (let i = 0; i < iterations; i++) {
  result = solvePart1Optimized(input);
}

const endTime = process.hrtime.bigint();
const totalNanos = Number(endTime - startTime);
const avgMicros = (totalNanos / iterations / 1000).toFixed(3);

console.log(`JavaScript (Node.js)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

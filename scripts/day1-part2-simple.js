const fs = require("fs");

// Simple, straightforward version
function solvePart2(rotations) {
  let position = 50;
  let count = 0;

  for (const rotation of rotations) {
    const direction = rotation[0];
    const distance = parseInt(rotation.substring(1));

    if (direction === "L") {
      // Count how many times we pass through 0 going left
      for (let i = 1; i <= distance; i++) {
        position = (position - 1) % 100;
        if (position < 0) position += 100;
        if (position === 0) count++;
      }
    } else {
      // Count how many times we pass through 0 going right
      for (let i = 1; i <= distance; i++) {
        position = (position + 1) % 100;
        if (position === 0) count++;
      }
    }
  }

  return count;
}

const input = fs
  .readFileSync("../inputs/day-1-input.txt", "utf-8")
  .trim()
  .split(/\r?\n/);

const iterations = 1;
const startTime = process.hrtime.bigint();

let result;
for (let i = 0; i < iterations; i++) {
  result = solvePart2(input);
}

const endTime = process.hrtime.bigint();
const totalNanos = Number(endTime - startTime);
const avgMicros = (totalNanos / iterations / 1000).toFixed(3);

console.log(`JavaScript (Day 1 Part 2 - Simple)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

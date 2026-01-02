const fs = require("fs");

// Read input file
const input = fs
  .readFileSync("../inputs/day-1-input.txt", "utf-8")
  .trim()
  .split("\n");

function solvePart1(input) {
  let position = 50;
  let count = 0;

  for (const rotation of input) {
    const direction = rotation[0];
    const distance = Number(rotation.slice(1));

    if (direction === "L") {
      position -= distance;
    } else {
      position += distance;
    }

    // Handle wrap-around
    position = ((position % 100) + 100) % 100;

    // Check if at zero
    if (position === 0) {
      count++;
    }
  }

  return count;
}

// Benchmark
const iterations = 1;
const startTime = process.hrtime.bigint();

let result;
for (let i = 0; i < iterations; i++) {
  result = solvePart1(input);
}

const endTime = process.hrtime.bigint();
const totalNanos = Number(endTime - startTime);
const avgMicros = (totalNanos / iterations / 1000).toFixed(3);

console.log(`JavaScript (Simple Version)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

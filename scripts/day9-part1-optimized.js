const fs = require("fs");

function solvePart1(points) {
  let maxArea = 0;
  const n = points.length;

  // Optimized: Try all pairs of points as opposite corners
  for (let i = 0; i < n - 1; i++) {
    const [x1, y1] = points[i];
    for (let j = i + 1; j < n; j++) {
      const [x2, y2] = points[j];

      // Calculate rectangle area (inclusive of both endpoints)
      const width = Math.abs(x2 - x1) + 1;
      const height = Math.abs(y2 - y1) + 1;
      const area = width * height;

      if (area > maxArea) {
        maxArea = area;
      }
    }
  }

  return maxArea;
}

const input = fs
  .readFileSync("../inputs/day-9-input.txt", "utf-8")
  .trim()
  .split(/\r?\n/);

const points = input.map((line) => line.split(",").map(Number));

const iterations = 1;
const startTime = process.hrtime.bigint();

let result;
for (let i = 0; i < iterations; i++) {
  result = solvePart1(points);
}

const endTime = process.hrtime.bigint();
const totalNanos = Number(endTime - startTime);
const avgMicros = (totalNanos / iterations / 1000).toFixed(3);

console.log(`JavaScript (Day 9 Part 1 - Optimized)`);
console.log(`Answer: ${result}`);
console.log(
  `Average time: ${avgMicros} microseconds (${iterations} iterations)`
);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

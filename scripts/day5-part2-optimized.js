const fs = require("fs");

function solvePart2(input) {
  const ranges = input[0].split("\n").map((line) => {
    const [start, end] = line.split("-").map(Number);
    return { start, end };
  });

  // Sort and merge overlapping ranges
  ranges.sort((a, b) => a.start - b.start);

  let totalCount = 0;
  let currentStart = ranges[0].start;
  let currentEnd = ranges[0].end;

  for (let i = 1; i < ranges.length; i++) {
    if (ranges[i].start <= currentEnd + 1) {
      currentEnd = Math.max(currentEnd, ranges[i].end);
    } else {
      totalCount += currentEnd - currentStart + 1;
      currentStart = ranges[i].start;
      currentEnd = ranges[i].end;
    }
  }

  totalCount += currentEnd - currentStart + 1;

  return totalCount;
}

const input = fs
  .readFileSync("../inputs/day-5-input.txt", "utf-8")
  .trim()
  .split(/\r?\n\r?\n/);

const iterations = 1;
const startTime = process.hrtime.bigint();

let result;
for (let i = 0; i < iterations; i++) {
  result = solvePart2(input);
}

const endTime = process.hrtime.bigint();
const totalNanos = Number(endTime - startTime);
const avgMicros = (totalNanos / iterations / 1000).toFixed(3);

console.log(`JavaScript (Day 5 Part 2 - Optimized)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

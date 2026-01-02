const fs = require("fs");

function solvePart2(input) {
  const ranges = input[0].split("\n").map((line) => {
    const [start, end] = line.split("-").map(Number);
    return { start, end };
  });

  // Merge overlapping ranges to avoid double counting
  const merged = [];
  const sorted = ranges.sort((a, b) => a.start - b.start);

  for (const range of sorted) {
    if (merged.length === 0) {
      merged.push({ ...range });
    } else {
      const last = merged[merged.length - 1];

      // If current range overlaps or is adjacent to the last one, merge them
      if (range.start <= last.end + 1) {
        last.end = Math.max(last.end, range.end);
      } else {
        merged.push({ ...range });
      }
    }
  }

  // Count all IDs in the merged ranges
  let totalCount = 0;
  for (const range of merged) {
    totalCount += range.end - range.start + 1;
  }

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

console.log(`JavaScript (Day 5 Part 2 - Simple)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

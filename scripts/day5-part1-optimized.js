const fs = require("fs");

function solvePart1(input) {
  const ranges = input[0].split("\n").map((line) => {
    const [start, end] = line.split("-").map(Number);
    return { start, end };
  });

  const availableIds = input.length > 1 ? input[1].split("\n").map(Number) : [];

  let freshCount = 0;

  for (const id of availableIds) {
    for (const range of ranges) {
      if (id >= range.start && id <= range.end) {
        freshCount++;
        break;
      }
    }
  }

  return freshCount;
}

const input = fs
  .readFileSync("../inputs/day-5-input.txt", "utf-8")
  .trim()
  .split(/\r?\n\r?\n/);

const iterations = 1;
const startTime = process.hrtime.bigint();

let result;
for (let i = 0; i < iterations; i++) {
  result = solvePart1(input);
}

const endTime = process.hrtime.bigint();
const totalNanos = Number(endTime - startTime);
const avgMicros = (totalNanos / iterations / 1000).toFixed(3);

console.log(`JavaScript (Day 5 Part 1 - Optimized)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

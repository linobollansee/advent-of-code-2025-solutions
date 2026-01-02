const fs = require("fs");

// Simple version - check if a number is made of some sequence repeated exactly twice
function isRepeatedTwice(num) {
  const str = num.toString();
  const len = str.length;

  if (len % 2 !== 0) return false;

  const half = len / 2;
  const firstHalf = str.substring(0, half);
  const secondHalf = str.substring(half);

  return firstHalf === secondHalf;
}

function solvePart1(input) {
  const ranges = input.split(",").filter((r) => r.trim());
  let sum = 0;

  for (const range of ranges) {
    const [start, end] = range.trim().split("-").map(Number);

    for (let id = start; id <= end; id++) {
      if (isRepeatedTwice(id)) {
        sum += id;
      }
    }
  }

  return sum;
}

const input = fs.readFileSync("../inputs/day-2-input.txt", "utf-8").trim();

const iterations = 1;
const startTime = process.hrtime.bigint();

let result;
for (let i = 0; i < iterations; i++) {
  result = solvePart1(input);
}

const endTime = process.hrtime.bigint();
const totalNanos = Number(endTime - startTime);
const avgMicros = (totalNanos / iterations / 1000).toFixed(3);

console.log(`JavaScript (Day 2 Part 1 - Simple)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

const fs = require("fs");

function solvePart1(banks) {
  let totalJoltage = 0;

  for (const bank of banks) {
    let maxJoltage = 0;

    for (let i = 0; i < bank.length; i++) {
      for (let j = i + 1; j < bank.length; j++) {
        const twoDigit = parseInt(bank[i] + bank[j]);
        maxJoltage = Math.max(maxJoltage, twoDigit);
      }
    }

    totalJoltage += maxJoltage;
  }

  return totalJoltage;
}

const input = fs
  .readFileSync("../inputs/day-3-input.txt", "utf-8")
  .trim()
  .split(/\r?\n/);

const iterations = 1;
const startTime = process.hrtime.bigint();

let result;
for (let i = 0; i < iterations; i++) {
  result = solvePart1(input);
}

const endTime = process.hrtime.bigint();
const totalNanos = Number(endTime - startTime);
const avgMicros = (totalNanos / iterations / 1000).toFixed(3);

console.log(`JavaScript (Day 3 Part 1 - Optimized)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

const fs = require("fs");

function solvePart2(banks) {
  let totalJoltage = 0;

  for (const bank of banks) {
    const n = bank.length;
    const toSelect = 12;

    let selected = [];
    let availableStart = 0;

    for (let pos = 0; pos < toSelect; pos++) {
      const remaining = toSelect - pos - 1;
      const mustLeaveAvailable = remaining;
      const canSearchUntil = n - mustLeaveAvailable;

      let maxDigit = "0";
      let maxPos = availableStart;

      for (let i = availableStart; i < canSearchUntil; i++) {
        if (bank[i] > maxDigit) {
          maxDigit = bank[i];
          maxPos = i;
        }
      }

      selected.push(maxDigit);
      availableStart = maxPos + 1;
    }

    const joltage = parseInt(selected.join(""));
    totalJoltage += joltage;
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
  result = solvePart2(input);
}

const endTime = process.hrtime.bigint();
const totalNanos = Number(endTime - startTime);
const avgMicros = (totalNanos / iterations / 1000).toFixed(3);

console.log(`JavaScript (Day 3 Part 2 - Optimized)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

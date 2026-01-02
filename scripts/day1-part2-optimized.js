const fs = require("fs");

function solvePart2(rotations) {
  let position = 50;
  let count = 0;

  for (const rotation of rotations) {
    const direction = rotation[0];
    const distance = parseInt(rotation.substring(1), 10);

    if (direction === "L") {
      // Going left from position, count how many times we pass 0
      // We cross 0 every 100 steps, plus potentially once more if the partial step crosses it
      const fullRotations = Math.floor(distance / 100);
      count += fullRotations;

      // For the remaining partial rotation
      const remainder = distance % 100;
      const newPos = (position - remainder + 100) % 100;

      // We cross 0 in the partial rotation if: starting position <= remainder
      // (e.g., position=30, remainder=40 means we go 30->0 and continue past it)
      // Use >= because landing exactly on 0 counts as crossing
      // But position=0 is special: moving left from 0 doesn't cross it
      if (remainder >= position && position > 0) {
        count++;
      }

      position = newPos;
    } else {
      // Going right: cross 0 when (position + step) >= 100
      const newPos = (position + distance) % 100;
      const crossings = Math.floor((position + distance) / 100);
      count += crossings;
      position = newPos;
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

console.log(`JavaScript (Day 1 Part 2 - Optimized)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

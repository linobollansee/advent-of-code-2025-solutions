const fs = require("fs");

function solvePart2(grid) {
  const rows = grid.length;
  const cols = grid[0].length;

  // Find the starting position 'S'
  let startCol = grid[0].indexOf("S");

  // Track timelines per state
  let currentStates = new Map([[`0,${startCol}`, 1]]);

  for (let row = 0; row < rows; row++) {
    const nextStates = new Map();

    for (const [stateKey, count] of currentStates) {
      const [r, c] = stateKey.split(",").map(Number);
      if (r !== row) continue;

      const cell = grid[r][c];

      if (cell === "." || cell === "S") {
        const nextKey = `${r + 1},${c}`;
        nextStates.set(nextKey, (nextStates.get(nextKey) || 0) + count);
      } else if (cell === "^") {
        if (c > 0) {
          const leftKey = `${r + 1},${c - 1}`;
          nextStates.set(leftKey, (nextStates.get(leftKey) || 0) + count);
        }
        if (c < cols - 1) {
          const rightKey = `${r + 1},${c + 1}`;
          nextStates.set(rightKey, (nextStates.get(rightKey) || 0) + count);
        }
      }
    }

    currentStates = nextStates;
  }

  let totalTimelines = 0;
  for (const count of currentStates.values()) {
    totalTimelines += count;
  }

  return totalTimelines;
}

const input = fs
  .readFileSync("../inputs/day-7-input.txt", "utf-8")
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

console.log(`JavaScript (Day 7 Part 2 - Optimized)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

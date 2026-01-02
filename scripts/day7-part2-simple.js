const fs = require("fs");

function solvePart2(grid) {
  const rows = grid.length;
  const cols = grid[0].length;

  // Find the starting position 'S'
  let startCol = -1;
  for (let c = 0; c < cols; c++) {
    if (grid[0][c] === "S") {
      startCol = c;
      break;
    }
  }

  // Track all unique states (row, col, and which path direction we came from)
  const states = new Map();

  // BFS approach - process level by level
  let currentStates = new Map();
  currentStates.set(`0,${startCol},down`, 1); // Initial state: 1 timeline

  for (let row = 0; row < rows; row++) {
    const nextStates = new Map();

    for (const [stateKey, count] of currentStates.entries()) {
      const [r, c, dir] = stateKey.split(",");
      const currentRow = parseInt(r);
      const currentCol = parseInt(c);

      if (currentRow !== row) continue;

      const cell = grid[currentRow][currentCol];

      if (cell === "." || cell === "S") {
        // Continue downward
        const nextKey = `${currentRow + 1},${currentCol},down`;
        nextStates.set(nextKey, (nextStates.get(nextKey) || 0) + count);
      } else if (cell === "^") {
        // Quantum split - creates two timelines for each incoming timeline
        // Left path
        if (currentCol - 1 >= 0) {
          const leftKey = `${currentRow + 1},${currentCol - 1},left`;
          nextStates.set(leftKey, (nextStates.get(leftKey) || 0) + count);
        }
        // Right path
        if (currentCol + 1 < cols) {
          const rightKey = `${currentRow + 1},${currentCol + 1},right`;
          nextStates.set(rightKey, (nextStates.get(rightKey) || 0) + count);
        }
      }
    }

    currentStates = nextStates;
  }

  // Count total timelines that exited
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

console.log(`JavaScript (Day 7 Part 2 - Simple)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

const fs = require("fs");

function solvePart1(grid) {
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

  // Simulate tachyon beams
  let beams = [[0, startCol]];
  const beamPositions = new Set();

  while (beams.length > 0) {
    const newBeams = [];

    for (const [row, col] of beams) {
      // Move beam down
      let newRow = row + 1;

      if (newRow >= rows) continue; // Beam exits

      const cell = grid[newRow][col];

      if (cell === ".") {
        // Continue downward
        const key = `${newRow},${col}`;
        if (!beamPositions.has(key)) {
          beamPositions.add(key);
          newBeams.push([newRow, col]);
        }
      } else if (cell === "^") {
        // Split into left and right beams
        beamPositions.add(`${newRow},${col}`);

        // Left beam
        if (col - 1 >= 0) {
          const leftKey = `${newRow},${col - 1}`;
          if (!beamPositions.has(leftKey)) {
            beamPositions.add(leftKey);
            newBeams.push([newRow, col - 1]);
          }
        }

        // Right beam
        if (col + 1 < cols) {
          const rightKey = `${newRow},${col + 1}`;
          if (!beamPositions.has(rightKey)) {
            beamPositions.add(rightKey);
            newBeams.push([newRow, col + 1]);
          }
        }
      }
    }

    beams = newBeams;
  }

  // Count splitters that were activated
  let activatedSplitters = 0;
  for (let r = 0; r < rows; r++) {
    for (let c = 0; c < cols; c++) {
      if (grid[r][c] === "^" && beamPositions.has(`${r},${c}`)) {
        activatedSplitters++;
      }
    }
  }

  return activatedSplitters;
}

const input = fs
  .readFileSync("../inputs/day-7-input.txt", "utf-8")
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

console.log(`JavaScript (Day 7 Part 1 - Simple)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

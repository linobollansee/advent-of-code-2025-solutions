const fs = require("fs");

function solvePart1(grid) {
  const rows = grid.length;
  const cols = grid[0].length;

  // Find the starting position 'S'
  let startCol = grid[0].indexOf("S");

  // Simulate tachyon beams using BFS
  let beams = [[0, startCol]];
  const visited = new Set([`0,${startCol}`]);

  while (beams.length > 0) {
    const newBeams = [];

    for (const [row, col] of beams) {
      const newRow = row + 1;
      if (newRow >= rows) continue;

      const cell = grid[newRow][col];

      if (cell === ".") {
        const key = `${newRow},${col}`;
        if (!visited.has(key)) {
          visited.add(key);
          newBeams.push([newRow, col]);
        }
      } else if (cell === "^") {
        visited.add(`${newRow},${col}`);

        if (col > 0) {
          const leftKey = `${newRow},${col - 1}`;
          if (!visited.has(leftKey)) {
            visited.add(leftKey);
            newBeams.push([newRow, col - 1]);
          }
        }

        if (col < cols - 1) {
          const rightKey = `${newRow},${col + 1}`;
          if (!visited.has(rightKey)) {
            visited.add(rightKey);
            newBeams.push([newRow, col + 1]);
          }
        }
      }
    }

    beams = newBeams;
  }

  // Count activated splitters
  let count = 0;
  for (let r = 0; r < rows; r++) {
    for (let c = 0; c < cols; c++) {
      if (grid[r][c] === "^" && visited.has(`${r},${c}`)) {
        count++;
      }
    }
  }

  return count;
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

console.log(`JavaScript (Day 7 Part 1 - Optimized)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

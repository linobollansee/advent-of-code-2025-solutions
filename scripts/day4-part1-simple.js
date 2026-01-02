const fs = require("fs");

function solve(grid) {
  const rows = grid.length;
  const cols = grid[0].length;
  let accessibleCount = 0;

  const directions = [
    [-1, -1],
    [-1, 0],
    [-1, 1],
    [0, -1],
    [0, 1],
    [1, -1],
    [1, 0],
    [1, 1],
  ];

  for (let r = 0; r < rows; r++) {
    for (let c = 0; c < cols; c++) {
      if (grid[r][c] === "@") {
        let adjacentRolls = 0;

        for (const [dr, dc] of directions) {
          const nr = r + dr;
          const nc = c + dc;

          if (
            nr >= 0 &&
            nr < rows &&
            nc >= 0 &&
            nc < cols &&
            grid[nr][nc] === "@"
          ) {
            adjacentRolls++;
          }
        }

        if (adjacentRolls < 4) {
          accessibleCount++;
        }
      }
    }
  }

  return accessibleCount;
}

const input = fs
  .readFileSync("../inputs/day-4-input.txt", "utf-8")
  .trim()
  .split(/\r?\n/);

const iterations = 1;
const startTime = process.hrtime.bigint();

let result;
for (let i = 0; i < iterations; i++) {
  result = solve(input);
}

const endTime = process.hrtime.bigint();
const totalNanos = Number(endTime - startTime);
const avgMicros = (totalNanos / iterations / 1000).toFixed(3);

console.log(`JavaScript (Day 4 Part 1 - Simple)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

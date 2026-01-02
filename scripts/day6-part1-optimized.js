const fs = require("fs");

function solvePart1(input) {
  const lines = input.split("\n");
  const width = lines[0].length;
  const height = lines.length;

  let grandTotal = 0;
  let col = 0;

  while (col < width) {
    // Skip empty columns
    let hasNonSpace = false;
    for (let row = 0; row < height; row++) {
      if (lines[row][col] && lines[row][col] !== " ") {
        hasNonSpace = true;
        break;
      }
    }

    if (!hasNonSpace) {
      col++;
      continue;
    }

    // Find the end of this problem
    let endCol = col;
    while (endCol < width) {
      let isAllSpace = true;
      for (let row = 0; row < height; row++) {
        if (lines[row][endCol] && lines[row][endCol] !== " ") {
          isAllSpace = false;
          break;
        }
      }
      if (isAllSpace) break;
      endCol++;
    }

    // Extract this problem
    let result = 0;
    let operator = "+";

    for (let row = 0; row < height; row++) {
      const cell = lines[row].substring(col, endCol).trim();
      if (cell) {
        if (cell === "+") {
          operator = "+";
        } else if (cell === "*") {
          operator = "*";
          result = result || 1;
        } else {
          const num = parseInt(cell);
          if (operator === "+") {
            result += num;
          } else {
            result = (result || 1) * num;
          }
        }
      }
    }

    grandTotal += result;
    col = endCol;
  }

  return grandTotal;
}

const input = fs.readFileSync("../inputs/day-6-input.txt", "utf-8").trim();

const iterations = 1;
const startTime = process.hrtime.bigint();

let result;
for (let i = 0; i < iterations; i++) {
  result = solvePart1(input);
}

const endTime = process.hrtime.bigint();
const totalNanos = Number(endTime - startTime);
const avgMicros = (totalNanos / iterations / 1000).toFixed(3);

console.log(`JavaScript (Day 6 Part 1 - Optimized)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

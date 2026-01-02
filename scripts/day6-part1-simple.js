const fs = require("fs");

function solvePart1(input) {
  const lines = input.split("\n");
  const width = lines[0].length;
  const height = lines.length;

  // Find problem boundaries
  const problems = [];
  let col = 0;

  while (col < width) {
    // Check if this column starts a problem
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
    const numbers = [];
    let operator = null;

    for (let row = 0; row < height; row++) {
      const cell = lines[row].substring(col, endCol).trim();
      if (cell) {
        if (cell === "+" || cell === "*") {
          operator = cell;
        } else {
          numbers.push(parseInt(cell));
        }
      }
    }

    problems.push({ numbers, operator });
    col = endCol;
  }

  // Calculate answers
  let grandTotal = 0;

  for (const problem of problems) {
    let result;
    if (problem.operator === "+") {
      result = problem.numbers.reduce((a, b) => a + b, 0);
    } else {
      result = problem.numbers.reduce((a, b) => a * b, 1);
    }
    grandTotal += result;
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

console.log(`JavaScript (Day 6 Part 1 - Simple)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

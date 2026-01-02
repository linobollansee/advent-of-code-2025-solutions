const fs = require("fs");

function solvePart2(input) {
  const lines = input.split("\n");
  const height = lines.length;
  const width = Math.max(...lines.map((l) => l.length));

  const normalizedLines = lines.map((line) => line.padEnd(width, " "));

  const problems = [];
  let col = width - 1;

  while (col >= 0) {
    let hasNonSpace = false;
    for (let row = 0; row < height; row++) {
      if (normalizedLines[row][col] !== " ") {
        hasNonSpace = true;
        break;
      }
    }

    if (!hasNonSpace) {
      col--;
      continue;
    }

    let startCol = col;
    while (startCol > 0) {
      let isAllSpace = true;
      for (let row = 0; row < height; row++) {
        if (normalizedLines[row][startCol - 1] !== " ") {
          isAllSpace = false;
          break;
        }
      }
      if (isAllSpace) break;
      startCol--;
    }

    const numbers = [];
    let operator = null;

    for (let c = col; c >= startCol; c--) {
      let digitStr = "";

      for (let row = 0; row < height; row++) {
        const char = normalizedLines[row][c];
        if (char === "+" || char === "*") {
          operator = char;
        } else if (char !== " ") {
          digitStr += char;
        }
      }

      if (digitStr.length > 0) {
        numbers.push(parseInt(digitStr));
      }
    }

    if (operator && numbers.length > 0) {
      problems.push({ numbers, operator });
    }
    col = startCol - 1;
  }

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
  result = solvePart2(input);
}

const endTime = process.hrtime.bigint();
const totalNanos = Number(endTime - startTime);
const avgMicros = (totalNanos / iterations / 1000).toFixed(3);

console.log(`JavaScript (Day 6 Part 2 - Simple)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

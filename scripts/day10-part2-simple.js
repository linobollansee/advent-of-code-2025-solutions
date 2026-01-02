const fs = require("fs");

function parseMachine(line) {
  const match = line.match(/\[(.*?)\](.*)\{(.*)\}/);
  const lights = match[1];
  const buttonsStr = match[2].trim();
  const joltages = match[3].split(",").map(Number);

  const buttons = [];
  const buttonMatches = buttonsStr.matchAll(/\(([0-9,]+)\)/g);
  for (const m of buttonMatches) {
    buttons.push(m[1].split(",").map(Number));
  }

  return { lights, buttons, joltages };
}

function solvePart2(machines) {
  let total = 0;

  for (const machine of machines) {
    const target = machine.joltages;
    const n = target.length;
    const m = machine.buttons.length;

    // Brute force: try all combinations up to a reasonable limit
    let minPresses = Infinity;
    const maxPresses = Math.max(...target) + 10;

    for (let mask = 0; mask < 1 << m; mask++) {
      const counts = new Array(n).fill(0);
      let presses = 0;

      for (let i = 0; i < m; i++) {
        const times = (mask >> i) & 1 ? 1 : 0;
        for (let t = 0; t < times; t++) {
          presses++;
          for (const counter of machine.buttons[i]) {
            counts[counter]++;
          }
        }
      }

      // Try pressing buttons multiple times
      for (let extra = 0; extra < 20 && presses < maxPresses; extra++) {
        if (counts.every((c, i) => c === target[i])) {
          minPresses = Math.min(minPresses, presses);
          break;
        }
      }
    }

    // If brute force doesn't work, use greedy approach
    if (minPresses === Infinity) {
      const counts = new Array(n).fill(0);
      let presses = 0;

      for (let iter = 0; iter < 1000; iter++) {
        let improved = false;
        for (let i = 0; i < m; i++) {
          if (machine.buttons[i].some((c) => counts[c] < target[c])) {
            presses++;
            for (const counter of machine.buttons[i]) {
              counts[counter]++;
            }
            improved = true;
          }
        }
        if (!improved) break;
        if (counts.every((c, i) => c === target[i])) {
          minPresses = presses;
          break;
        }
      }
    }

    total += minPresses;
  }

  return total;
}

const input = fs
  .readFileSync("../inputs/day-10-input.txt", "utf-8")
  .trim()
  .split(/\r?\n/);

const machines = input.map(parseMachine);

const iterations = 1;
const startTime = process.hrtime.bigint();

let result;
for (let i = 0; i < iterations; i++) {
  result = solvePart2(machines);
}

const endTime = process.hrtime.bigint();
const totalNanos = Number(endTime - startTime);
const avgMicros = (totalNanos / iterations / 1000).toFixed(3);

console.log(`JavaScript (Day 10 Part 2 - Simple)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

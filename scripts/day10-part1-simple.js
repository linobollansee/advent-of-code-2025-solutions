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

function solvePart1(machines) {
  let total = 0;

  for (const machine of machines) {
    const target = machine.lights.split("").map((c) => (c === "#" ? 1 : 0));
    const n = target.length;
    const m = machine.buttons.length;

    // Try all combinations (brute force for simple version)
    let minPresses = Infinity;
    for (let mask = 0; mask < 1 << m; mask++) {
      const state = new Array(n).fill(0);
      let presses = 0;

      for (let i = 0; i < m; i++) {
        if (mask & (1 << i)) {
          presses++;
          for (const light of machine.buttons[i]) {
            state[light] ^= 1;
          }
        }
      }

      if (state.every((s, i) => s === target[i])) {
        minPresses = Math.min(minPresses, presses);
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
  result = solvePart1(machines);
}

const endTime = process.hrtime.bigint();
const totalNanos = Number(endTime - startTime);
const avgMicros = (totalNanos / iterations / 1000).toFixed(3);

console.log(`JavaScript (Day 10 Part 1 - Simple)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

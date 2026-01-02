const fs = require("fs");

function dfs(current, target, graph, cache = new Map()) {
  if (current === target) {
    return 1;
  }

  if (cache.has(current)) {
    return cache.get(current);
  }

  if (!graph[current]) {
    cache.set(current, 0);
    return 0;
  }

  let count = 0;
  for (const next of graph[current]) {
    count += dfs(next, target, graph, cache);
  }

  cache.set(current, count);
  return count;
}

function solvePart1(lines) {
  const graph = {};

  for (const line of lines) {
    const parts = line.split(": ");
    if (parts.length === 2) {
      const from = parts[0];
      const tos = parts[1].split(" ");
      graph[from] = tos;
    }
  }

  return dfs("you", "out", graph);
}

const input = fs
  .readFileSync("../inputs/day-11-input.txt", "utf-8")
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

console.log(`JavaScript (Day 11 Part 1 - Optimized)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

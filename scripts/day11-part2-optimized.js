const fs = require("fs");

function dfs(current, visitedDac, visitedFft, graph, cache = new Map()) {
  if (current === "out" && visitedDac && visitedFft) {
    return 1;
  }

  const key = `${current},${visitedDac ? 1 : 0},${visitedFft ? 1 : 0}`;
  if (cache.has(key)) {
    return cache.get(key);
  }

  if (!graph[current]) {
    cache.set(key, 0);
    return 0;
  }

  let count = 0;
  for (const next of graph[current]) {
    const newDac = visitedDac || next === "dac";
    const newFft = visitedFft || next === "fft";
    count += dfs(next, newDac, newFft, graph, cache);
  }

  cache.set(key, count);
  return count;
}

function solvePart2(lines) {
  const graph = {};

  for (const line of lines) {
    const parts = line.split(": ");
    if (parts.length === 2) {
      const from = parts[0];
      const tos = parts[1].split(" ");
      graph[from] = tos;
    }
  }

  return dfs("svr", false, false, graph);
}

const input = fs
  .readFileSync("../inputs/day-11-input.txt", "utf-8")
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

console.log(`JavaScript (Day 11 Part 2 - Optimized)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

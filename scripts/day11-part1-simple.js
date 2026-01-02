const fs = require("fs");

function dfs(current, target, graph, visited = new Set()) {
  if (current === target) {
    return 1;
  }

  if (!graph[current]) {
    return 0;
  }

  let count = 0;
  for (const next of graph[current]) {
    if (!visited.has(next)) {
      visited.add(next);
      count += dfs(next, target, graph, visited);
      visited.delete(next);
    }
  }

  return count;
}

function solvePart1(lines) {
  const graph = {};

  for (const line of lines) {
    const [from, ...tos] = line.split(/[: ]+/).filter(Boolean);
    graph[from] = tos;
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

console.log(`JavaScript (Day 11 Part 1 - Simple)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

const fs = require("fs");

function getNormalizedEdges(tiles) {
  const edges = [];
  const n = tiles.length;

  for (let i = 0; i < n - 1; i++) {
    edges.push({
      minX: Math.min(tiles[i][0], tiles[i + 1][0]),
      minY: Math.min(tiles[i][1], tiles[i + 1][1]),
      maxX: Math.max(tiles[i][0], tiles[i + 1][0]),
      maxY: Math.max(tiles[i][1], tiles[i + 1][1]),
    });
  }

  // Wrap around from last to first
  edges.push({
    minX: Math.min(tiles[n - 1][0], tiles[0][0]),
    minY: Math.min(tiles[n - 1][1], tiles[0][1]),
    maxX: Math.max(tiles[n - 1][0], tiles[0][0]),
    maxY: Math.max(tiles[n - 1][1], tiles[0][1]),
  });

  return edges;
}

function isFullyContained(edges, minX, minY, maxX, maxY) {
  for (const edge of edges) {
    if (
      minX < edge.maxX &&
      maxX > edge.minX &&
      minY < edge.maxY &&
      maxY > edge.minY
    ) {
      return false;
    }
  }
  return true;
}

function solvePart2(tiles) {
  const n = tiles.length;
  let maxArea = 0;
  const edges = getNormalizedEdges(tiles);

  for (let i = 0; i < n; i++) {
    for (let j = i + 1; j < n; j++) {
      const area =
        (Math.abs(tiles[i][0] - tiles[j][0]) + 1) *
        (Math.abs(tiles[i][1] - tiles[j][1]) + 1);

      if (area <= maxArea) continue;

      const minX = Math.min(tiles[i][0], tiles[j][0]);
      const maxX = Math.max(tiles[i][0], tiles[j][0]);
      const minY = Math.min(tiles[i][1], tiles[j][1]);
      const maxY = Math.max(tiles[i][1], tiles[j][1]);

      if (isFullyContained(edges, minX, minY, maxX, maxY)) {
        maxArea = area;
      }
    }
  }

  return maxArea;
}

const input = fs
  .readFileSync("../inputs/day-9-input.txt", "utf-8")
  .trim()
  .split(/\r?\n/);

const tiles = input.map((line) => line.split(",").map(Number));

const iterations = 1;
const startTime = process.hrtime.bigint();

let result;
for (let i = 0; i < iterations; i++) {
  result = solvePart2(tiles);
}

const endTime = process.hrtime.bigint();
const totalNanos = Number(endTime - startTime);
const avgMicros = (totalNanos / iterations / 1000).toFixed(3);

console.log(`JavaScript (Day 9 Part 2 - Simple)`);
console.log(`Answer: ${result}`);
console.log(
  `Average time: ${avgMicros} microseconds (${iterations} iterations)`
);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

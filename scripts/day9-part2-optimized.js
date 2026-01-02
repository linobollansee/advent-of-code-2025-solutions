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

  for (let i = 0; i < n - 1; i++) {
    const [x1, y1] = tiles[i];

    for (let j = i + 1; j < n; j++) {
      const [x2, y2] = tiles[j];

      const area = (Math.abs(x1 - x2) + 1) * (Math.abs(y1 - y2) + 1);

      if (area <= maxArea) continue;

      const minX = Math.min(x1, x2);
      const maxX = Math.max(x1, x2);
      const minY = Math.min(y1, y2);
      const maxY = Math.max(y1, y2);

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

console.log(`JavaScript (Day 9 Part 2 - Optimized)`);
console.log(`Answer: ${result}`);
console.log(
  `Average time: ${avgMicros} microseconds (${iterations} iterations)`
);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

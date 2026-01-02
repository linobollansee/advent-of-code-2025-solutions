const fs = require("fs");

class Shape {
  constructor(coords) {
    this.coords = coords;
  }
}

function getAllOrientations(shape) {
  const seen = new Set();
  const result = [];

  for (let flip = 0; flip < 2; flip++) {
    for (let rot = 0; rot < 4; rot++) {
      let coords = shape.coords.map(([r, c]) => [r, c]);

      if (flip) {
        coords = coords.map(([r, c]) => [r, -c]);
      }

      for (let i = 0; i < rot; i++) {
        coords = coords.map(([r, c]) => [c, -r]);
      }

      let minR = Math.min(...coords.map(([r]) => r));
      let minC = Math.min(...coords.map(([, c]) => c));
      coords = coords.map(([r, c]) => [r - minR, c - minC]);

      const key = coords
        .map(([r, c]) => `${r},${c}`)
        .sort()
        .join("|");

      if (!seen.has(key)) {
        seen.add(key);
        result.push(new Shape(coords));
      }
    }
  }

  return result;
}

function tryPlace(idx, presents, grid, width, height, orientations) {
  if (idx >= presents.length) return true;

  const shapeIdx = presents[idx];

  for (const shape of orientations[shapeIdx]) {
    for (let r = 0; r < height; r++) {
      for (let c = 0; c < width; c++) {
        let canPlace = true;
        for (const [dr, dc] of shape.coords) {
          const nr = r + dr,
            nc = c + dc;
          if (nr >= height || nc >= width || grid[nr][nc] !== -1) {
            canPlace = false;
            break;
          }
        }

        if (canPlace) {
          for (const [dr, dc] of shape.coords) {
            grid[r + dr][c + dc] = idx;
          }

          if (tryPlace(idx + 1, presents, grid, width, height, orientations)) {
            return true;
          }

          for (const [dr, dc] of shape.coords) {
            grid[r + dr][c + dc] = -1;
          }
        }
      }
    }
  }

  return false;
}

function solve() {
  const lines = fs
    .readFileSync("../inputs/day-12-input.txt", "utf-8")
    .split("\n");
  const shapes = {};

  // Parse shapes
  for (let i = 0; i < lines.length; i++) {
    const line = lines[i].trim();
    if (!line) continue;

    if (/^\d+:$/.test(line)) {
      const shapeIdx = parseInt(line);
      const coords = [];
      i++;
      let row = 0;

      while (
        i < lines.length &&
        lines[i].trim() &&
        !/^\d+:$/.test(lines[i]) &&
        !lines[i].includes("x")
      ) {
        for (let c = 0; c < lines[i].length; c++) {
          if (lines[i][c] === "#") {
            coords.push([row, c]);
          }
        }
        row++;
        i++;
      }
      i--;
      shapes[shapeIdx] = new Shape(coords);
    }
  }

  // Parse regions
  const regions = [];
  for (const line of lines) {
    if (line.includes("x") && line.includes(":") && /^\d/.test(line)) {
      const [dims, rest] = line.split(":");
      const [width, height] = dims.split("x").map(Number);
      const counts = rest.trim().split(/\s+/).map(Number);

      const presents = [];
      counts.forEach((count, idx) => {
        for (let j = 0; j < count; j++) {
          presents.push(idx);
        }
      });

      regions.push({ width, height, presents });
    }
  }

  // Pre-compute all orientations
  const allOrientations = {};
  for (const idx in shapes) {
    allOrientations[idx] = getAllOrientations(shapes[idx]);
  }

  let fittable = 0;

  for (const r of regions) {
    const area = r.width * r.height;
    const needed = r.presents.reduce(
      (sum, p) => sum + shapes[p].coords.length,
      0
    );

    if (needed <= area) {
      const grid = Array.from({ length: r.height }, () =>
        Array(r.width).fill(-1)
      );
      if (tryPlace(0, r.presents, grid, r.width, r.height, allOrientations)) {
        fittable++;
      }
    }
  }

  return fittable;
}

// Benchmark
const iterations = 1;
const startTime = process.hrtime.bigint();

let result;
for (let i = 0; i < iterations; i++) {
  result = solve();
}

const endTime = process.hrtime.bigint();
const totalNanos = Number(endTime - startTime);
const avgMs = (totalNanos / iterations / 1000000).toFixed(3);

console.log(`JavaScript (Day 12 Part 1 - Optimized)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMs} ms (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000000).toFixed(2)} s`);

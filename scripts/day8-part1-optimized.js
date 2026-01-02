const fs = require("fs");

function distance(p1, p2) {
  const dx = p1[0] - p2[0];
  const dy = p1[1] - p2[1];
  const dz = p1[2] - p2[2];
  return Math.sqrt(dx * dx + dy * dy + dz * dz);
}

class UnionFind {
  constructor(n) {
    this.parent = Array.from({ length: n }, (_, i) => i);
    this.size = Array(n).fill(1);
  }

  find(x) {
    if (this.parent[x] !== x) {
      this.parent[x] = this.find(this.parent[x]);
    }
    return this.parent[x];
  }

  union(x, y) {
    const rootX = this.find(x);
    const rootY = this.find(y);

    if (rootX === rootY) return false;

    if (this.size[rootX] < this.size[rootY]) {
      this.parent[rootX] = rootY;
      this.size[rootY] += this.size[rootX];
    } else {
      this.parent[rootY] = rootX;
      this.size[rootX] += this.size[rootY];
    }

    return true;
  }

  getCircuitSizes() {
    const circuits = new Map();
    for (let i = 0; i < this.parent.length; i++) {
      const root = this.find(i);
      circuits.set(root, this.size[root]);
    }
    return Array.from(circuits.values()).sort((a, b) => b - a);
  }
}

function solvePart1(input) {
  const junctions = input.map((line) => line.split(",").map(Number));
  const n = junctions.length;

  // Create all pairs with their distances
  const pairs = [];
  for (let i = 0; i < n; i++) {
    for (let j = i + 1; j < n; j++) {
      pairs.push({
        i,
        j,
        dist: distance(junctions[i], junctions[j]),
      });
    }
  }

  // Sort by distance
  pairs.sort((a, b) => a.dist - b.dist);

  // Connect the 1000 shortest pairs
  const uf = new UnionFind(n);
  const limit = Math.min(1000, pairs.length);
  for (let k = 0; k < limit; k++) {
    uf.union(pairs[k].i, pairs[k].j);
  }

  // Get circuit sizes and multiply the three largest
  const sizes = uf.getCircuitSizes();
  return sizes[0] * sizes[1] * sizes[2];
}

const input = fs
  .readFileSync("../inputs/day-8-input.txt", "utf-8")
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

console.log(`JavaScript (Day 8 Part 1 - Optimized)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

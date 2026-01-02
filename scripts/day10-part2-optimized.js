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

function getAllParityMaps(nCounters, switches) {
  const parityMaps = new Map();

  for (let i = 0; i < 1 << switches.length; i++) {
    const result = new Array(nCounters).fill(0);
    let nFlips = 0;

    for (let j = 0; j < switches.length; j++) {
      if (i & (1 << j)) {
        nFlips++;
        for (const ele of switches[j]) {
          result[ele]++;
        }
      }
    }

    const parityKey = result.map((x) => x % 2).join(",");
    const resultKey = result.join(",");

    if (!parityMaps.has(parityKey)) {
      parityMaps.set(parityKey, new Map());
    }

    if (
      !parityMaps.get(parityKey).has(resultKey) ||
      parityMaps.get(parityKey).get(resultKey) > nFlips
    ) {
      parityMaps.get(parityKey).set(resultKey, nFlips);
    }
  }

  return parityMaps;
}

function findMinSwitchFlips(current, switches, parityMaps, cache) {
  const key = current.join(",");

  if (cache.has(key)) {
    return cache.get(key);
  }

  if (current.every((x) => x === 0)) {
    cache.set(key, { found: true, count: 0 });
    return { found: true, count: 0 };
  }

  if (current.some((x) => x < 0)) {
    cache.set(key, { found: false, count: 0 });
    return { found: false, count: 0 };
  }

  const currentParity = current.map((x) => x % 2).join(",");

  if (!parityMaps.has(currentParity)) {
    cache.set(key, { found: false, count: 0 });
    return { found: false, count: 0 };
  }

  let minFlips = Infinity;

  for (const [patternStr, nFlips] of parityMaps.get(currentParity)) {
    const pattern = patternStr.split(",").map(Number);

    // Check validity
    let valid = true;
    for (let i = 0; i < pattern.length; i++) {
      if (pattern[i] > current[i]) {
        valid = false;
        break;
      }
    }

    if (!valid) continue;

    const next = current.map((c, i) => (c - pattern[i]) / 2);
    const result = findMinSwitchFlips(next, switches, parityMaps, cache);

    if (result.found) {
      minFlips = Math.min(minFlips, nFlips + 2 * result.count);
    }
  }

  if (minFlips === Infinity) {
    cache.set(key, { found: false, count: 0 });
    return { found: false, count: 0 };
  }

  cache.set(key, { found: true, count: minFlips });
  return { found: true, count: minFlips };
}

function solvePart2(machines) {
  let total = 0;

  for (const machine of machines) {
    const parityMaps = getAllParityMaps(
      machine.joltages.length,
      machine.buttons
    );
    const cache = new Map();
    const result = findMinSwitchFlips(
      machine.joltages,
      machine.buttons,
      parityMaps,
      cache
    );
    total += result.count;
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

console.log(`JavaScript (Day 10 Part 2 - Optimized)`);
console.log(`Answer: ${result}`);
console.log(`Average time: ${avgMicros} microseconds (${iterations} iterations)`);
console.log(`Total time: ${(totalNanos / 1000000).toFixed(2)} ms`);

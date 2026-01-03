# Advent of Code 2025 Solutions

This repository contains solutions for [Advent of Code 2025](https://adventofcode.com/2025) challenges implemented in multiple programming languages.

## 🌟 Features

- **Multi-language implementations**: Solutions in C++, JavaScript, and Python
- **Dual approaches**: Both simple and optimized versions for learning and performance comparison
- **Automated runners**: PowerShell scripts to execute all solutions at once
- **Organized structure**: Clean separation of inputs, solutions, and problem descriptions

## 📁 Project Structure

```
advent-of-code/
├── scripts/          # Solution implementations
│   ├── day1-part1-simple.{cpp,js,py}
│   ├── day1-part1-optimized.{cpp,js,py}
│   ├── day1-part2-simple.{cpp,js,py}
│   └── day1-part2-optimized.{cpp,js,py}
│   └── ... (continues for each day)
├── inputs/           # Puzzle input data
│   ├── day-1-input.txt
│   └── ...
├── days/             # Problem descriptions
│   ├── day-1.txt
│   └── ...
├── solutions/        # Additional solution files
├── build/            # Compiled C++ binaries
└── run-all-*.ps1     # Automation scripts
```

## 🚀 Getting Started

### Prerequisites

Depending on which language implementations you want to run:

- **C++**: A C++ compiler (g++, clang, or MSVC)
- **JavaScript**: Node.js (v14 or higher)
- **Python**: Python 3.x

### Running Solutions

#### Run All Solutions (by Language)

```powershell
# Run all C++ solutions
.\run-all-cpp.ps1

# Run all JavaScript solutions
.\run-all-javascript.ps1

# Run all Python solutions
.\run-all-python.ps1
```

#### Run Individual Solutions

**C++:**

```powershell
# Compile (if needed)
g++ scripts/day1-part1-simple.cpp -o build/day1-part1-simple.exe

# Run (from build directory)
cd build
.\day1-part1-simple.exe
```

**JavaScript:**

```powershell
# Run from scripts directory
cd scripts
node day1-part1-simple.js
```

**Python:**

```powershell
# Run from scripts directory
cd scripts
python day1-part1-simple.py
```

## 💡 Solution Variants

Each day's challenge includes two implementations:

- **Simple**: Straightforward, readable solutions focusing on clarity
- **Optimized**: Performance-focused implementations with algorithmic improvements

This dual approach allows for:

- Learning different problem-solving techniques
- Understanding optimization trade-offs
- Comparing execution times across approaches

## ️ Development

### Adding New Solutions

1. Create solution files in the `scripts/` directory following the naming convention:

   ```
   day{N}-part{1|2}-{simple|optimized}.{cpp|js|py}
   ```

2. Add the corresponding input file to `inputs/`:

   ```
   day-{N}-input.txt
   ```

3. (Optional) Add problem description to `days/`:
   ```
   day-{N}.txt
   ```

## 📝 Notes

- Input files are specific to each user's Advent of Code account and are not shared publicly
- Solutions are designed to work with the standard input format from Advent of Code
- Performance measurements may vary based on hardware and system state

## 📜 License

This project is open source and available for educational purposes.

## 🔗 Resources

- [Advent of Code Official Site](https://adventofcode.com/)
- [Advent of Code Subreddit](https://www.reddit.com/r/adventofcode/)

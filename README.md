# C++ Profiler Utility

A lightweight, hierarchical C++ profiler for measuring execution time of code blocks with support for nested timings and CSV export.

## Features

- **Hierarchical Timing**: Track nested code blocks and visualize their relationships
- **RAII-based Scoped Timers**: Automatic timing with scope-based cleanup
- **CSV Export**: Export profiling results for further analysis
- **Console Output**: Pretty-printed hierarchical timing results
- **Zero Dependencies**: Uses only standard C++ libraries

## Building

### Requirements
- CMake 3.10 or higher
- C++11 compatible compiler

### Build Instructions

```bash
mkdir build
cd build
cmake ..
make
```

## Usage

### Scoped Timer (Recommended)

The RAII-based approach automatically handles timing cleanup:

```cpp
#include "profiler.h"

int main() {
    Profiler profiler;

    {
        auto timer = profiler.scopedTimer("Main Process");

        // Your code here
        processData();

        {
            auto nestedTimer = profiler.scopedTimer("Nested Operation");
            // Nested operation code
        }
    }

    profiler.printResults();
    profiler.exportToCSV("results.csv");

    return 0;
}
```

### Manual Begin/End

Alternative approach for explicit control:

```cpp
profiler.beginTiming("Operation Name");
// Your code here
profiler.endTiming();
```

## API Reference

### Core Methods

- `scopedTimer(const std::string& name)` - Returns a RAII timer object
- `beginTiming(const std::string& name)` - Manually start timing a block
- `endTiming()` - End the current timing block
- `printResults()` - Print hierarchical timing results to console
- `exportToCSV(const std::string& filename)` - Export results to CSV file
- `reset()` - Clear all timing data for a new profiling session

## Example Output

Console output shows hierarchical timing:

```
Main Process: 123.45 ms
  Initialization: 23.12 ms
  Data Processing: 89.34 ms
    Step 1: 45.67 ms
    Step 2: 43.67 ms
      Substep 2.1: 12.34 ms
```

## Running the Example

After building, run the example program:

```bash
./build/profiler_example
```

This will:
1. Run various profiled operations
2. Print timing results to console
3. Generate `profiling_results.csv` and `profiling_results_2.csv`

## License

MIT License

#include "profiler.h"
#include <iostream>
#include <thread>
#include <vector>
#include <cmath>

// Example function that does some work
void processData(int iterations) {
    double result = 0.0;
    for (int i = 0; i < iterations; i++) {
        result += std::sqrt(i * 3.14159);
    }
}

void databaseOperation() {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void apiCall() {
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
}

void complexOperation(Profiler& profiler) {
    auto timer = profiler.scopedTimer("Complex Operation");

    processData(100000);

    {
        auto dbTimer = profiler.scopedTimer("Database Query");
        databaseOperation();
    }

    {
        auto apiTimer = profiler.scopedTimer("API Call");
        apiCall();
    }

    processData(50000);
}

int main() {
    Profiler profiler;

    // Example 1: Using scoped timers (RAII approach - recommended)
    {
        auto mainTimer = profiler.scopedTimer("Main Process");

        {
            auto initTimer = profiler.scopedTimer("Initialization");
            processData(200000);
        }

        {
            auto dataTimer = profiler.scopedTimer("Data Processing");

            {
                auto step1 = profiler.scopedTimer("Step 1");
                processData(150000);
            }

            {
                auto step2 = profiler.scopedTimer("Step 2");
                processData(100000);

                {
                    auto substep = profiler.scopedTimer("Substep 2.1");
                    processData(50000);
                }
            }
        }

        complexOperation(profiler);
    }

    // Print results to console
    profiler.printResults();

    // Export to CSV
    profiler.exportToCSV("profiling_results.csv");

    std::cout << "\n--- Running another profiling session ---\n" << std::endl;

    // Example 2: Using manual begin/end (alternative approach)
    profiler.reset();

    profiler.beginTiming("Second Session");
    processData(100000);

    profiler.beginTiming("Nested Task");
    processData(50000);
    profiler.endTiming();

    profiler.endTiming();

    profiler.printResults();
    profiler.exportToCSV("profiling_results_2.csv");

    return 0;
}

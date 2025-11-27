#ifndef PROFILER_H
#define PROFILER_H

#include <chrono>
#include <string>
#include <vector>
#include <memory>
#include <fstream>

class Profiler {
public:
    struct TimingEntry {
        std::string name;
        std::chrono::high_resolution_clock::time_point start;
        std::chrono::high_resolution_clock::time_point end;
        double duration_ms;
        int depth;
        std::vector<std::shared_ptr<TimingEntry>> children;
        TimingEntry* parent;

        TimingEntry(const std::string& n, int d, TimingEntry* p = nullptr)
            : name(n), duration_ms(0.0), depth(d), parent(p) {}
    };

    class ScopedTimer {
    public:
        ScopedTimer(Profiler& profiler, const std::string& name)
            : profiler_(profiler) {
            profiler_.beginTiming(name);
        }

        ~ScopedTimer() {
            profiler_.endTiming();
        }

    private:
        Profiler& profiler_;
    };

    Profiler() : current_entry_(nullptr), current_depth_(0) {}

    void beginTiming(const std::string& name);
    void endTiming();
    void reset();
    void exportToCSV(const std::string& filename) const;
    void printResults() const;

    ScopedTimer scopedTimer(const std::string& name) {
        return ScopedTimer(*this, name);
    }

private:
    std::vector<std::shared_ptr<TimingEntry>> root_entries_;
    TimingEntry* current_entry_;
    int current_depth_;

    void printEntry(const TimingEntry& entry) const;
    void writeEntryToCSV(std::ofstream& file, const TimingEntry& entry) const;
};

#endif // PROFILER_H

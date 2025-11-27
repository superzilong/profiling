#include "profiler.h"
#include <iostream>
#include <iomanip>

void Profiler::beginTiming(const std::string& name) {
    auto entry = std::make_shared<TimingEntry>(name, current_depth_, current_entry_);
    entry->start = std::chrono::high_resolution_clock::now();

    if (current_entry_ == nullptr) {
        root_entries_.push_back(entry);
    } else {
        current_entry_->children.push_back(entry);
    }

    current_entry_ = entry.get();
    current_depth_++;
}

void Profiler::endTiming() {
    if (current_entry_ == nullptr) {
        std::cerr << "Error: No active timing entry to end" << std::endl;
        return;
    }

    current_entry_->end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        current_entry_->end - current_entry_->start
    );
    current_entry_->duration_ms = duration.count() / 1000.0;

    current_depth_--;
    current_entry_ = current_entry_->parent;
}

void Profiler::reset() {
    root_entries_.clear();
    current_entry_ = nullptr;
    current_depth_ = 0;
}

void Profiler::printResults() const {
    std::cout << "\n========== Profiling Results ==========" << std::endl;
    for (const auto& entry : root_entries_) {
        printEntry(*entry);
    }
    std::cout << "======================================\n" << std::endl;
}

void Profiler::printEntry(const TimingEntry& entry) const {
    std::string indent(entry.depth * 2, ' ');
    std::cout << indent << entry.name << ": "
              << std::fixed << std::setprecision(3)
              << entry.duration_ms << " ms" << std::endl;

    for (const auto& child : entry.children) {
        printEntry(*child);
    }
}

void Profiler::exportToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    file << "Name,Depth,Duration_ms,Parent\n";

    for (const auto& entry : root_entries_) {
        writeEntryToCSV(file, *entry);
    }

    file.close();
    std::cout << "Profiling data exported to " << filename << std::endl;
}

void Profiler::writeEntryToCSV(std::ofstream& file, const TimingEntry& entry) const {
    std::string parent_name = entry.parent ? entry.parent->name : "ROOT";

    file << "\"" << entry.name << "\","
         << entry.depth << ","
         << std::fixed << std::setprecision(6) << entry.duration_ms << ","
         << "\"" << parent_name << "\"\n";

    for (const auto& child : entry.children) {
        writeEntryToCSV(file, *child);
    }
}

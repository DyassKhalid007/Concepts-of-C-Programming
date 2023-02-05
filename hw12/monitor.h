#pragma once

#include <chrono>
#include <unordered_map>
#include <string>
#include <filesystem>
#include <map>
#include <iostream>
#include "logger.h"


namespace fs = std::filesystem;

/**
 * The File Monitor class keeps a record of files in the targetPath and their last modification time
 * Once the monitor has been started, it will continue checking every interval for new, modified and deleted files
 * until it is stopped
 */
class FileMonitor {
public:
    FileMonitor(const std::string &targetpath,
                std::chrono::milliseconds interval = std::chrono::milliseconds(1'000),
                const std::string &logfile = "log.txt");

    /**
     * Run the monitor.
     * Check the directory every `interval` until `timeout`.
     * Log file changes using the logger.
     */
    void start(std::chrono::seconds timeout = std::chrono::minutes{1});

private:
    Logger logger;
    std::chrono::duration<int, std::milli> interval;
    std::map<fs::path, fs::file_time_type> original_state;
    std::string filename;
};

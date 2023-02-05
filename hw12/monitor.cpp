#include "monitor.h"

#include <thread>


using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
using namespace std::chrono_literals;
FileMonitor::FileMonitor(const std::string &targetpath,
                         std::chrono::milliseconds interval,
                         const std::string &logfilename)
    : logger{logfilename}
    , interval{interval} 
{

    filename = targetpath;

    for (const auto& dirEntry : recursive_directory_iterator(targetpath)){

        original_state[dirEntry.path()] = fs::last_write_time(dirEntry);
    }
     








    
}

// Monitor the targetpath for changes and pass information to the logger in case of differences
void FileMonitor::start(std::chrono::seconds timeout) {

            std::jthread worker([&]{

            auto end_time = std::chrono::system_clock::now() + timeout;
            while (std::chrono::system_clock::now() < end_time) {

            for (const auto& entry : recursive_directory_iterator(filename)) {
            auto path = entry.path();
            auto current_write_time = fs::last_write_time(entry);
            auto last_write = original_state[path];

            // Check if the file has been modified
            if (current_write_time > last_write) {
                std::cout << path << " has been modified.\n";

                logger.log(entry.path(),status::changed);
                original_state[path] = current_write_time;
            }

            // Check if the file has been deleted
            if (!fs::exists(path) && original_state.count(path)) {
                std::cout << path << " has been deleted.\n";
                logger.log(entry.path(),status::removed);
                original_state.erase(path);
            }
        }

            // Check for new files
            for (const auto& entry : recursive_directory_iterator(filename)) {
            if (!original_state.count(entry.path())) {
                std::cout << entry.path() << " is a new file.\n";
                logger.log(entry.path(),status::added);
                original_state[entry.path()] = fs::last_write_time(entry);
                }
            }
     }

        std::this_thread::sleep_for(interval);
    });

        worker.join();
        

       
            







        





    


}

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

            std::thread worker([&]{

            auto start(std::chrono::high_resolution_clock::now());
            while (true) {


            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = end - start;
            if (elapsed>= timeout) {
                 break;
            
            }
            for (const auto& entry : recursive_directory_iterator(filename)) {
            if (!original_state.count(entry.path())) {
                std::cout << entry.path() << " is a new file.\n";
                logger.log(entry.path(),status::added);
                original_state[entry.path()] = fs::last_write_time(entry);
            }
            }

            for (const auto& entry : recursive_directory_iterator(filename)) {
            auto path = entry.path();
            auto current_write_time = fs::last_write_time(entry);
            auto last_write = original_state[path];

            // std:: cout << path << " about to be checked.\n"; 

            // Check if the file has been modified
            if (current_write_time > last_write) {
                std::cout << path << " has been modified.\n";

                logger.log(entry.path(),status::changed);
                original_state[path] = current_write_time;
            }


      }


      std::erase_if(original_state,[&](auto kv){

        if(!fs::exists(kv.first)){

            std::cout << kv.first << " has been deleted.\n";
            logger.log(kv.first,status::removed);
            return true;
        }
        return false;

      });




                    
        
 


        // std::cout << "\n" << std::endl;
        std::this_thread::sleep_for(interval);
     }
        
    });

        worker.join();
        // std::cout << "Hello" << std::endl;
        
}

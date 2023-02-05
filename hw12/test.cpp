#include <iostream>
#include <chrono>
#include <thread>

void performTask(std::chrono::seconds timeout,std::chrono::duration<int, std::milli> interval) {


    std::jthread worker([&]{

   
    auto start = std::chrono::high_resolution_clock::now();

    while (true) {
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = end - start;

        if (elapsed >= timeout) {
            break;
        }

        // Perform a task
        std::cout << "Performing task..." << std::endl;

        // Wait for 1 second before checking elapsed time again
        std::this_thread::sleep_for(interval);
    }

    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
    std::cout << "Timeout reached after " << elapsed.count() << " nanoseconds." << std::endl;

     });

     worker.join();
}

int main() {
    performTask(std::chrono::seconds(5),std::chrono::duration<int, std::milli> (5000));
    

    return 0;
}

#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <string>
#include <algorithm>
#include <random>
#include <print>

struct Data {

    std::vector<char> buffer;

    Data(size_t size) : buffer(size) {

        std::println("Data CTR: started.");

        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dist('0', '9');
        for (auto& c : buffer) c = static_cast<char>(dist(gen));

        std::println("Data CTR: finished.");

    }

    ~Data() {

        std::println("Data DTR.");

    }

};

void worker(std::string name, std::string pattern, std::shared_ptr<Data> data) {

    std::println("{}: search started...", name);
    
    auto it = std::search(
        data->buffer.begin(), data->buffer.end(),
        pattern.begin(), pattern.end());

    if (it != data->buffer.end()) {

        auto pos = std::distance(data->buffer.begin(), it);
        std::println("{}: found at {}.", name, pos);

    }

    std::println("{}: search finished.", name);

}

int main() {

    auto shared_data = std::make_shared<Data>(1024 * 1024 * 1024);

    std::weak_ptr<Data> observer = shared_data;

    std::string pi = "3141592653589793";
    std::string e  = "1718281828459045";
    std::string today  = "20260413";
    std::string group = "207";

    std::thread(worker, "PI", pi, shared_data).detach();
    std::thread(worker, "E", e, shared_data).detach();
    std::thread(worker, "today", today, shared_data).detach();
    std::thread(worker, "group", group, shared_data).detach();

    shared_data.reset();

    while (true) {

        if (auto locked = observer.lock()) {

            std::println("Main: data in memory, use_count = {}.", locked.use_count());

        } else {

            std::println("Main: data destroyed.");
            break;

        }

        std::this_thread::sleep_for(std::chrono::milliseconds(20));

    }

}

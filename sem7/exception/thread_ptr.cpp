#include <thread>
#include <exception>
#include <random>
#include <print>

constexpr int magic0 = 0;
constexpr int magic65536 = 65536;
constexpr int magic1024 = 1024;
constexpr int magic207 = 207;
constexpr int magic256 = 256;

void
worker(int id, std::exception_ptr& e_ptr) noexcept 
try {

    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(magic0, magic65536 - 1);

    for (int it = 0; it < magic1024; ++it) {

        if (dist(gen) == magic207) {
            throw std::runtime_error(std::format("Поток {} обнаружил число {} на итерации {}", id, magic207, it));
        }

    }

} 
catch (...) {

    e_ptr = std::current_exception();

}

int
main()
{

    std::vector<std::thread> threads;
    std::vector<std::exception_ptr> errors(magic256, nullptr);

    for (int id = 0; id < magic256; ++id) {
        threads.emplace_back(worker, id, std::ref(errors[id]));
    }

    for (auto& t : threads) {
        t.join();
    }

    for (int id = 0; id < magic256; ++id) {

        if (errors[id]) {

            try {
                std::rethrow_exception(errors[id]);
            } catch (const std::exception& e) {
                std::println("Exception caught: \"{}\".", e.what());
            }

        }

    }

}

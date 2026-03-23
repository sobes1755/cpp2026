#include <chrono>
#include <iostream>

template <typename T>
std::string pretty_type() {

    // std::cout << __PRETTY_FUNCTION__ << std::endl;

    std::string name = __PRETTY_FUNCTION__;
    
    size_t start = name.find("T = ") + 4;
    size_t end = name.find_last_of(";");
    
    if (start != std::string::npos && end != std::string::npos) {
        return name.substr(start, end - start);
    }
    
    return name;

}

int main() {

    using std::chrono::milliseconds;
    using std::chrono::system_clock;
    using std::chrono::current_zone;
    using std::chrono::zoned_time;

    auto now = system_clock::now();
    auto floored = floor<milliseconds>(now);

    auto local = zoned_time<milliseconds>(current_zone(), floored);
    auto moscow = zoned_time<milliseconds>("Europe/Moscow", floored);
    auto berlin = zoned_time<milliseconds>("Europe/Berlin", floored);
    auto newyork = zoned_time<milliseconds>("America/New_York", floored);
    auto tokyo = zoned_time<milliseconds>("Asia/Tokyo", floored);

    std::cout << pretty_type<decltype(now)>() << " now: " << now << std::endl;
    std::cout << pretty_type<decltype(floored)>() << " floored: " << floored << std::endl;
    std::cout << pretty_type<decltype(local)>() << " local: " << local << std::endl;

    std::cout << "Moscow: " << moscow << std::endl;
    std::cout << "Berlin: " << berlin << std::endl;
    std::cout << "New York: " << newyork << std::endl;
    std::cout << "Tokyo: " << tokyo << std::endl;

}

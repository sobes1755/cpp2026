#include <chrono>
#include <iostream>

int main() {

    using namespace std::chrono_literals;

    std::chrono::year_month_day ymd1 = 1755y/std::chrono::January/25;
    std::chrono::year_month_day ymd2{std::chrono::year{1755}, std::chrono::month{1}, std::chrono::day{25}};

    // std::chrono::sys_days = std::chrono::time_point<std::chrono::system_clock, std::chrono::days>

    std::chrono::sys_days tp1 = ymd1;
    std::chrono::sys_days tp2 = ymd2;

    // std::chrono::system_clock::time_point = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>

    std::chrono::system_clock::time_point tp_now = std::chrono::system_clock::now();

    std::cout << "Дата 1: " << ymd1 << std::endl;
    std::cout << "Дата 2: " << ymd2 << std::endl;

    std::cout << "Сейчас: " << tp_now << std::endl;

    // std::chrono::duration<int64_t, std::nano>

    auto diff1 = tp_now - tp1;
    auto diff2 = tp_now - tp2;

    std::cout << "Прошло от даты 1: ";

    std::cout << std::chrono::duration_cast<std::chrono::days>(diff1).count() << " дней = ";
    std::cout << std::chrono::duration_cast<std::chrono::hours>(diff1).count() << " часов = ";
    std::cout << std::chrono::duration_cast<std::chrono::minutes>(diff1).count() << " минут = ";
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(diff1).count() << " секунд." << std::endl;

    std::cout << "Прошло от даты 2: ";

    std::cout << std::chrono::duration_cast<std::chrono::days>(diff2).count() << " дней = ";
    std::cout << std::chrono::duration_cast<std::chrono::hours>(diff2).count() << " часов = ";
    std::cout << std::chrono::duration_cast<std::chrono::minutes>(diff2).count() << " минут = ";
    std::cout << std::chrono::duration_cast<std::chrono::seconds>(diff2).count() << " секунд." << std::endl;

}

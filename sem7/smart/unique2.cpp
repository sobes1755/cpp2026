#include <memory>
#include <print>

int
main()
{

    std::unique_ptr<int, void(*)(void*)> ptr(
        (int*)std::malloc(sizeof(int)), 
        std::free
    );

    *ptr = 2026;
    std::println("*ptr = {}", *ptr);

}

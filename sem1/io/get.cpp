#include <iostream>
#include <cstdio>

int main()
{

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    char c;

    while (std::cin.get(c)) {
        printf("%c", c);
        std::cout.put(c);
    }

}

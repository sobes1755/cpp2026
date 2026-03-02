#include <iostream>
#include <string>

namespace std {

    // Just for fun.

    std::ostream& putline(std::ostream& os, std::string& s) {
        return os << s << std::endl;
    }

}

int main()
{

    std::string s;

    while (std::getline(std::cin, s)) {
        std::putline(std::cout, s);
    }

}

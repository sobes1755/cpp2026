#include <iostream>
#include <cctype>    // std::isspace, etc.
#include <cstdlib>    // EXIT_SUCCESS
#include <iomanip>

enum State { SPACE, OTHER };

int main() {

    char c;

    State s = OTHER;

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cin >> std::noskipws;    

    while (std::cin >> c) {

        switch (s) {

            case OTHER:

                std::cout << c;

                if (std::isspace(c)) {
                    s = SPACE;
                }

                break;

            case SPACE:

                if (std::islower(c)) {
                    std::cout << std::toupper(c);
                } else {
                    std::cout << c;
                }

                s = OTHER;

                break;

        }
    }

    return EXIT_SUCCESS;

}


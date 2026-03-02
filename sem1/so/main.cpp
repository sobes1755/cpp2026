#include "ctrdtrlib.h"

#include <print>
#include <cstdlib>

int main() {

    std::println("Main: {} ctrdtrlib::fun().", "before");
    ctrdtrlib::fun();
    std::println("Main: {} ctrdtrlib::fun().", "after");

    return EXIT_SUCCESS;

}

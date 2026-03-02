/*

ctr101, ctr207, ctr65535 run when DL loads.
dtr65535, dtr207, dtr101 run when DL unloads.

*/

#include "ctrdtrlib.h"
#include <print>

namespace ctrdtrlib {

    void __attribute__((constructor(101))) ctr101() {
        std::println("SO: ctrdtrlib::ctr101() runs.");
    }
    void __attribute__((constructor(207))) ctr207() {
        std::println("SO: ctrdtrlib::ctr207() runs.");
    }
    void __attribute__((constructor(65535))) ctr65535() {
        std::println("SO: ctrdtrlib::ctr65535() runs.");
    }
    
    void __attribute__((destructor(65535))) dtr65535() {
        std::println("SO: ctrdtrlib::dtr65535() runs.");
    }
    void __attribute__((destructor(207))) dtr207() {
        std::println("SO: ctrdtrlib::dtr207() runs.");
    }
    void __attribute__((destructor(101))) dtr101() {
        std::println("SO: ctrdtrlib::dtr101() runs.");
    }

    void fun() {
        std::println("SO: ctrdtrlib::fun() runs.");
    }

}

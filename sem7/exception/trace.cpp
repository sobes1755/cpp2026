#include <stacktrace>  // -lstdc++exp
#include <string>
#include <print>

struct Error {

    std::string reason;
    std::stacktrace trace;

    Error(std::string &&r) : reason(r), trace(std::stacktrace::current()) {}

};

void h() {

    try {

        throw Error("No reason for anything exceptional");

    } catch (const std::exception& e) {

        std::println("Caught and rethrowed std::exception!");
        throw;

    } catch (const Error& e) {

        std::println("Caught and rethrowed Error!");        
        throw;

    } catch (...) {

        std::println("Caught and rethrowed unknown exception");
        throw;

    }
    
}

void g() {
    h();
}

void f() {
    g();
}

int
main()
{

    try {

        f();

    } catch (const std::exception& e) {

        std::println("Caught std::exception e!");        
        std::println("e.what() = \"{}\"", e.what());

    } catch (const Error& e) {

        std::println("Error e caught!");

        std::println("Reason: \"{}\"", e.reason);
        std::println("Stack trace:\n----------------\n{}----------------", e.trace);

    } catch (...) {

        std::println("Unknown exceptioon caught!");

    }

}

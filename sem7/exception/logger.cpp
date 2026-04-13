#include <exception>
#include <string>
#include <print>

struct Logger {

    std::string name_;
    
    Logger(const std::string& name) : name_(name) {
        std::println("CTR: \"{}\".", name_);
    }
    
    ~Logger() {
        std::println("DTR: \"{}\".", name_);
    }

};

void h() {
    Logger lh(__PRETTY_FUNCTION__);
    throw std::runtime_error("Something exceptional happened");
}

void g() {
    Logger lg(__PRETTY_FUNCTION__);
    h();
}

void f() {
    Logger lf(__PRETTY_FUNCTION__);
    g();
}

int
main()
{

    f();

}

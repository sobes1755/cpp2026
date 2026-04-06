#include <string>
#include <print>

class Pet {
protected:
    std::string name;

public:
    Pet(std::string n) : name(n) {
        OMG();
    }
    
    void OMG() const {
        talk();  // talk() = 0
    }
    
    virtual void talk() const = 0;
    
    virtual ~Pet() {}
};

class Dog : public Pet {
public:
    Dog(std::string n) : Pet(n) {}

    void talk() const override {
        std::println("{}: \"Гав!\"", name);
    }
};

int
main()
{

    Dog dog("Шарик"); 

}

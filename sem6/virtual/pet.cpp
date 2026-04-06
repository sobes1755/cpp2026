#include <string>
#include <print>
#include <vector>

class Pet {
protected:
    std::string name;

public:
    Pet(std::string n) : name(n) {}
    
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

class Cat : public Pet {
public:
    int lives;

public:
    Cat(std::string n, int l = 9) : Pet(n), lives(l) {}

    void talk() const override {
        std::println("{} ({} жизней): \"Мяу!\"", name, lives);
    }
};

int
main()
{

    // Pet pet("Хватайка");

    Dog dog("Шарик");
    Cat cat("Кот Матроскин");

    dog.talk();
    cat.talk();

    std::vector<Pet*> zoo = {&dog, &cat};

    for (const auto* pet: zoo) {
        pet->talk();
    }

}

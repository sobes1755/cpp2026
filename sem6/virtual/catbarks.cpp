#include <string>
#include <print>
#include <algorithm>  // std::swap

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
private:
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

    Dog dog("Шарик");
    Cat cat("Матроскин");

    Pet* p1{&dog};
    Pet* p2{&cat};

    p1->talk();  // Шарик: "Гав!"
    p2->talk();  // Матроскин: "Мяу!"

    void** dog_vptr = (void**)&dog;
    void** cat_vptr = (void**)&cat;

    std::swap(*dog_vptr, *cat_vptr);

    p1->talk();  // Шарик (мусор в lives?): "Мяу!"
    p2->talk();  // Матроскин: "Гав!"

    std::swap(*dog_vptr, *cat_vptr);

}

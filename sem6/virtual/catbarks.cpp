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

//    dog.talk();  // Эта конструкция оптимизируется даже с -O0.
//    cat.talk();

    Pet* p1{&dog};  // Эта конструкция не оптимизируется до -O1 включительно.
    Pet* p2{&cat};

    p1->talk();  // Шарик: "Гав!"
    p2->talk();  // Матроскин: "Мяу!"

    void** ptr2dogvptr = (void**)&dog;
    void** ptr2catvptr = (void**)&cat;

    std::swap(*ptr2dogvptr, *ptr2catvptr);

//    dog.talk();
//    cat.talk();

    p1->talk();  // Шарик (мусор в lives?): "Мяу!"
    p2->talk();  // Матроскин: "Гав!"

    std::swap(*ptr2dogvptr, *ptr2catvptr);

}

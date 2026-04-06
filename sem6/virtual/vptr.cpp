#include <string>
#include <print>

class Pet {
public:
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

    void omg() {
        Pet::talk();
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

    auto print_vtable = [](const auto& obj) {

        void *ptr = (void *) &obj;
        void *vptr = *(void **) ptr;
        void **vtable = (void **) vptr; 

        std::println("ptr = {}", ptr);
        std::println("vptr = {}", vptr);

        for (int offset = -2; offset < 4; ++offset) {
            std::println("vtable[{}] = {}", offset, vtable[offset]);
        }

        std::type_info* tiptr = (std::type_info*) vtable[-1];
        std::println("vtable[-1]->name() = {}", tiptr->name());

    };

    Dog dog("Шарик");
    Cat cat("Кот Матроскин");

    dog.talk();
    cat.talk();

    std::println("sizeof(Pet) = {}", sizeof(Pet));
    std::println("offsetof(name) = {}", offsetof(Pet, name));
    std::println("sizeof(std::string) = {}", sizeof(std::string));
    std::println("sizeof(Dog) = {}, sizeof(dog) = {}", sizeof(Dog), sizeof(dog));
    std::println("sizeof(Cat) = {}, sizeof(cat) = {}", sizeof(Cat), sizeof(cat));
    std::println("offsetof(lives) = {}", offsetof(Cat, lives));
    std::println("sizeof(int) = {}", sizeof(int));



    std::println("Address of Dog::talk() = {}", (void *)&Dog::talk);
    std::println("typeid(dog).name() = {}", typeid(dog).name());
    print_vtable(dog);

    std::println("Address of Cat::talk() = {}", (void *)&Cat::talk);
    std::println("typeid(cat).name() = {}", typeid(cat).name());
    print_vtable(cat);

}

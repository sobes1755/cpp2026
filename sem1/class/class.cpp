#include <print>


// private, protected, public 

struct S {
public:
   static constexpr int CEI {207};
   static int SI;
   int x {10};
   double y {1.0};
   bool z {true};
   using TI = int;

   static int sum() {
       return CEI + SI;
   }
   char getC() const {
       return c;
   }
   int getX() {
       return x;
   }

//   S() = delete;

   S() {
       std::println("{}", __PRETTY_FUNCTION__);
   }

   S(int xx) : x{xx} {
       std::println("{}, x = {}", __PRETTY_FUNCTION__, xx);
   }

   ~S() {
       int x = 888;
       std::println("{}, x = {}, this->x = {}", __PRETTY_FUNCTION__, x, this->x);
   }


private:
   char c {'A'};
//   S() {};
};

class C {
public:
   int x {20};
   double y {2.0};
   bool z {false};
};

int S::SI {65535};

S g{33};

int main() {

    std::println("111\n");

    S a{22};
    C b;

    {

        S l{44};

    }

    std::println("222\n");

    const S d;

    std::println("333\n");
 
    S::TI c {101};

    std::println("a.x = {}", a.x);
    std::println("b.y = {}", b.y);

    std::println("a.CE = {}", a.CEI);
    std::println("a.SI = {}", a.SI);
    std::println("c = {}", c);
    std::println("d.getC() = {}", d.getC());
    std::println("d.getX() = {}", a.getX());
}

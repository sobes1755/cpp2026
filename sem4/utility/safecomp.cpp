#include <utility>
#include <iostream>

int main() {

  std::cout << "(-1 < 0u) = " << (-1 < 0u) << std::endl;
  std::cout << "cmp_less(-1, 0u) = " << std::cmp_less(-1, 0u) << std::endl;

}

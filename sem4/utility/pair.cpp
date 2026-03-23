#include <utility>
#include <numbers>
#include <iostream>
#include "myswap.h"

int main() {

  using std::pair;
  using std::make_pair;

  pair<const char*, double> pair1("e", std::numbers::e);
  pair<const char*, double> pair2 = make_pair("pi", std::numbers::pi);
  auto pair3 = make_pair("sqrt2", std::numbers::sqrt2);

  std::cout << pair1.first << ", " << pair1.second << std::endl;
  std::cout << pair2.first << ", " << pair2.second << std::endl;
  std::cout << pair3.first << ", " << pair3.second << std::endl;

  pair3.first = "sqrt3";
  get<1>(pair3) = std::numbers::sqrt3;
  swap(pair2, pair3);
  myswap(pair1, pair2);

  std::cout << pair1.first << ", " << pair1.second << std::endl;
  std::cout << pair2.first << ", " << pair2.second << std::endl;
  std::cout << pair3.first << ", " << pair3.second << std::endl;

}


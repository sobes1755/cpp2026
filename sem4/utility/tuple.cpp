#include <tuple>
#include <numbers>
#include <iostream>

int main() {

  std::tuple<int, double, std::string> tup1(1, 1., "one");
  auto tup2 = std::make_tuple(2, 2., "two");

  std::cout << get<0>(tup1) << ", " << get<1>(tup1) << ", " << get<2>(tup1) << std::endl;
  std::cout << get<0>(tup2) << ", " << get<1>(tup2) << ", " << get<2>(tup2) << std::endl;

  std::cout << (tup1 < tup2) << std::endl;

  auto p = std::make_pair(1, true);
  std::tuple<int, bool> t3 = p;

  std::cout << get<0>(p) << ", " << get<1>(p) << std::endl;
  std::cout << get<0>(t3) << ", " << get<1>(t3) << std::endl;

  int v1 = 1;
  int v2 = 2;
  int v3 = 3;
  int v4 = 4;

  auto t = std::tie(v1, v2, v3, v4) = std::make_tuple(101, 102, 103, 104);

  std::cout << v1 << " " << v2 << " " << v3 << " " << v4 << std::endl;
  std::cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << " " << get<3>(t) << std::endl;

  v1 = 201;
  get<1>(t) = 202;

  std::cout << v1 << " " << v2 << " " << v3 << " " << v4 << std::endl;
  std::cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << " " << get<3>(t) << std::endl;

  int a, b;

  tie(std::ignore, a, std::ignore, b) = t;

  std::cout << a << " " << b << std::endl;

};

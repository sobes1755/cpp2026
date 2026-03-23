#include <utility>
#include <iostream>

int main() {

  int y1 = 2025;
  int y2 = 2026;

  auto min1 = std::min(y1, y2);
  auto min2 = std::min({-2, -1, 0, 1, 2});
  auto min3 = std::min({-1, 1, 0, -2, 2}, [](int a, int b){ return std::abs(a) < std::abs(b); });

  std::cout << min1 << std::endl;
  std::cout << min2 << std::endl;
  std::cout << min3 << std::endl;

  auto minmax1 = std::minmax(y1, y2);
  auto minmax2 = std::minmax({0, -2, -1, 2, 1});
  auto minmax3 = std::minmax({-1, 1, -2, 2}, [](int a, int b){ return std::abs(a) < std::abs(b); });

  std::cout << minmax1.first << ", " << minmax1.second << std::endl;
  std::cout << minmax2.first << ", " << minmax2.second << std::endl;
  std::cout << minmax3.first << ", " << minmax3.second << std::endl;

}

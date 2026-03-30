#include <set>
#include <iostream>

int
main()
{

    std::multiset<int> s{3, 1, 5, 3, 4, 5, 1, 4, 4, 3, 2, 2, 7, 6, 4, 3, 6};

    std::cout << "s = ";
    for (auto k: s)
       std::cout << k << " ";
    std::cout << "\n";

    s.erase(s.lower_bound(4), s.upper_bound(4));

    std::cout << "s = ";
    for (auto k: s)
       std::cout << k << " ";
    std::cout << "\n";

    std::cout << "s.count(3) = " << s.count(3) << '\n';

    std::cout << "*s.find(3) = " << *s.find(3) << '\n';
    std::cout << "*s.lower_bound(3) = " << *s.lower_bound(3) << '\n';
    std::cout << "*s.upper_bound(3) = " << *s.upper_bound(3) << '\n';

    auto pair = s.equal_range(3);
    std::cout << "[*s.equal_range(3).first, *s.equal_range(3).second] = [" << *pair.first << ", " << *pair.second << "]" << "\n";

}

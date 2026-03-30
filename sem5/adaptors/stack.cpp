#include <stack>
#include <iostream>

int
main()
{

    std::stack<int> s;

    std::cout << s.empty() << '\n';
    std::cout << s.size() << '\n';

    s.push(1);
    s.push(2);
    s.push(3);

    while (! s.empty()) {
        std::cout << "s.top() = " << s.top() << "\n";
        s.pop();
    }

    std::cout << s.empty() << '\n'; 
    std::cout << s.size() << '\n';

}

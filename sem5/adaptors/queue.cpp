#include <queue>
#include <iostream>

int
main()
{

    std::queue<int> q;

    std::cout << q.empty() << '\n';
    std::cout << q.size() << '\n';

    q.push(1);
    q.push(2);
    q.push(3);

    while (! q.empty()) {
        std::cout << "q.back() = " << q.back() << "\n";
        std::cout << "q.front() = " << q.front() << "\n";
        q.pop();
    }

    std::cout << q.empty() << '\n'; 
    std::cout << q.size() << '\n';

}

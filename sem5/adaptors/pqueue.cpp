#include <queue>
#include <iostream>

class Task {
public:
    std::string name_;
    int priority_;

    Task(std::string name, int priority) : name_{name}, priority_{priority} {}

    bool operator<(const Task& other) const {
        return priority_ < other.priority_;
    }
};

struct BadComparator {
    bool operator()(const Task& t1, const Task& t2) {
        return ! (t1 < t2); 
    }
};

int
main()
{

    std::vector<Task> tasks = {
        {"Сделать практикум", 5},
        {"Сделать матан", 2},
        {"Поспать", 10},
        {"Поесть", 9},
        {"Поиграть в футбол", 8},
        {"Сходить в кино", 7}
    };

    std::priority_queue<Task> pq(tasks.begin(), tasks.end());

    std::cout << "Список задач:" << std::endl;

    while (! pq.empty()) {
        const Task& task = pq.top();
        std::cout << "p = " << task.priority_ << ", n = \"" << task.name_ << "\"." << std::endl;
        pq.pop(); 
    }

    std::priority_queue<Task, std::vector<Task>, BadComparator> pq2;

    pq2.push_range(tasks);

    std::cout << "Список задач ошибочный:" << std::endl;

    while (! pq2.empty()) {
        const Task& task = pq2.top();
        std::cout << "p = " << task.priority_ << ", n = \"" << task.name_ << "\"." << std::endl;
        pq2.pop(); 
    }

}

#include <map>
#include <set>
#include <vector>

#include <iostream>

int main() {

    struct Area {
        int land;
        int water;
        int total() const { return land + water; }
    };

    std::map<std::string, Area> m = {
        {"Россия", {16377742, 747449}},
        {"Канада", {9093507, 891163}},
        {"Китай", {9326410, 270551}},
        {"США", {9147593, 685924}},
        {"Бразилия", {8358140, 157627}},
        {"Австралия", {7682300, 58924}},
        {"Индия", {2973193, 314070}},
        {"Аргентина", {2736690, 43710}},
        {"Казахстан", {2699700, 25200}},
        {"Алжир", {2381741, 0}},
        {"Конго (Заир)", {2267048, 77810}},
        {"Дания", {2210579, 660}},
        {"Саудовская Аравия", {2149690, 0}},
        {"Мексика", {1943945, 20430}},
        {"Индонезия", {1811569, 93000}},
        {"Судан", {1765050, 96035}},
        {"Ливия", {1759540, 0}},
        {"Иран", {1531595, 116600}},
        {"Монголия", {1553556, 10560}},
        {"Перу", {1279996, 5220}}
    };

    std::cout << "Forward iterator..." << std::endl << std::endl;

    for (auto it = m.begin(); it != m.end(); ++it) {
        auto& [name, area] = *it;
        std::cout << name << " " << area.total() << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Backward iterator..." << std::endl << std::endl;

    for (auto revit = m.rbegin(); revit != m.rend(); ++revit) {
        auto& [name, area] = *revit;
        std::cout << name << " " << area.total() << std::endl;
    }

    std::cout << std::endl;

}

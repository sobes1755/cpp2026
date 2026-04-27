/*

Ссылка для баловства с регулярными выражениями:
https://regex101.com/
Ссылка для рисования конечных автоматов:
https://www.madebyevan.com/fsm/

*/

#include <set>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <iostream>
#include <print>

using std::set;
using std::map;
using std::pair;
using std::stack;
using std::queue;
using std::string;

struct Automaton {

    set<char> alphabet = {'a', 'b', 'c'};

    int start_state;
    set<int> final_states;

    map<pair<int, char>, set<int>> trans;
    map<int, set<int>> eps_trans;

};

// Вычисление eps-замыкания (epsilon closure)

set<int>
eps_closure(const set<int>& states, const map<int, set<int>>& eps_trans) {

    stack<int> lifo;
    for (int s : states) lifo.push(s);

    set<int> closure = states;

    while (! lifo.empty()) {
        int p = lifo.top(); lifo.pop();
        if (eps_trans.count(p)) {
            for (int q : eps_trans.at(p)) {
                if (closure.find(q) == closure.end()) {
                    closure.insert(q);
                    lifo.push(q);
                }
            }
        }
    }

    return closure;

}

bool
parsed_by_nfa(const Automaton& nfa, const string& input) {

    // Начинаем с eps-замыкания начального состояния

    set<int> curr_states = eps_closure({nfa.start_state}, nfa.eps_trans);

    for (char c : input) {

        set<int> next_states;

        // Переходим

        for (int p: curr_states) {

            auto it = nfa.trans.find({p, c});

            if (it != nfa.trans.end()) {

                for (int q : it->second) {
                    next_states.insert(q);
                }

            }

        }

        // Добавляем eps-замыкание

        curr_states = eps_closure(next_states, nfa.eps_trans);
        
        if (curr_states.empty()) {
            return false;
        }

    }

    // Если в множестве состояний есть финальное состояние,
    // то строка принадлежит языку.

    for (int s : curr_states) {
        if (nfa.final_states.count(s)) {
           return true;
        }
    }

    return false;

}

// Распечатка конечного автомата

void print(const Automaton& a, string title) {

    std::println("");

    std::println("Описание автомата: \"{}\"", title);

    std::println("");

    std::println("Всего состояний: {} = {} + {}", 1 + a.final_states.size(), 1, a.final_states.size());

    std::print("Начальное состояние:");
    std::print(" {}", a.start_state);
    std::println("");

    if (a.final_states.size()) {
        std::print("Финальные состояния:");
        for (int s : a.final_states) std::print(" {}", s);
        std::println("");
    }

    std::println("");

    std::println("Всего переходов: {} = {} + {}", a.trans.size() + a.eps_trans.size(), a.trans.size(), a.eps_trans.size());

    if (a.trans.size()) {
        std::println("Обычные переходы:");
        for (auto const& [key, states] : a.trans)
            for (int s : states)
                std::println("{} --( {} )--> {}", key.first, key.second, s);
    }
    if (a.eps_trans.size()) {
        std::println("Эпсилон-переходы:");
        for (auto const& [key, states] : a.eps_trans)
            for (int s : states)
                std::println("{} --( eps )--> {}", key, s);
    }

    std::println("");

}

constexpr std::string RED = "\033[31m";
constexpr std::string GREEN = "\033[32m";
constexpr std::string RESET = "\033[0m";
constexpr std::string BOLD = "\033[1m";

int
main() {

    std::println("Регулярный язык: {}", "цепочки из алфавита {a,b,c}, начинающиеся на ab и не заканчивающиеся на ab");
    std::println("Регулярное выражение: {}", "ab ((a|b|c)*(a|c|bb|cb) | b)");

    // Строим вручную недетерминированный конечный автомат

    Automaton nfa;

    nfa.alphabet = {'a', 'b', 'c'};
    nfa.start_state = 0;

    // Начало ab
    nfa.trans[{0, 'a'}].insert(1);
    nfa.trans[{1, 'b'}].insert(2);
    nfa.trans[{1, 'b'}].insert(6);

    // Окончание b
    nfa.trans[{6, 'b'}].insert(7);
    nfa.final_states.insert(7);

    // Продолжение (a|b|c)*
    nfa.trans[{2, 'a'}].insert(2);
    nfa.trans[{2, 'b'}].insert(2);
    nfa.trans[{2, 'c'}].insert(2);

    // Окончания a|c|bb|cb
    nfa.trans[{2, 'a'}].insert(3);
    nfa.trans[{2, 'c'}].insert(3);
    nfa.final_states.insert(3);
    nfa.trans[{2, 'b'}].insert(4);
    nfa.trans[{2, 'c'}].insert(4);
    nfa.trans[{4, 'b'}].insert(5);
    nfa.final_states.insert(5);

    print(nfa, "Недетерминированный конечный автомат (НКА, NFA)");

    // Проверка строк на принадлежность языку

    std::println("Введите строку из алфавита {{a,b,c}} (или exit) для проверки с помощью НКА.");
    
    while (true) {

        string input;

        std::cout << "> ";
        std::cin >> input;

        if (input == "exit") {
           break;
        }

        if (parsed_by_nfa(nfa, input)) {
            std::println("Строка {}принадлежит{} языку.", GREEN, RESET);
        } else {
            std::println("Строка {}не принадлежит{} языку.", RED, RESET);
        }

    }

}

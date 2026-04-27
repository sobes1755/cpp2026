/*

Авторы алгоритмов NFA -> Min-DFA:
Эдвард Форрест Мур (Edward F. Moore), 23.11.1925 — 14.06.2003 (77 лет);
Януш Бжозовский (Janusz Brzozowski), 10.05.1935 — 24.10.2019 (84 года);
Джон Эдвард Хопкрофт (John Hopcroft), 7.10.1939 — ... (86 лет).

Ссылка для баловства с конечными автоматами (Regex -> NFA, NFA -> Min-DFA):
https://cyberzhg.github.io/toolbox/

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

// Обращение автомата (reverse)

Automaton
rev(const Automaton& a) {

    Automaton r;

    r.alphabet = a.alphabet;

    // Старый старт становится новым финишем

    r.final_states.insert(a.start_state);

    // Новый старт (-1) соединяем eps-переходами со старыми финишами

    r.start_state = -1;
    for (int s : a.final_states) {
        r.eps_trans[-1].insert(s);
    }
    
    // Разворачиваем переходы

    for (auto const& [key, states] : a.trans) {
        for (int s : states) r.trans[{s, key.second}].insert(key.first);
    }
    
    // Разворачиваем eps-переходы

    for (auto const& [key, states] : a.eps_trans) {
        for (int s : states) r.eps_trans[s].insert(key);
    }
    
    return r;

}

// Детерминизация автомата (determinization, subset construction)

Automaton
det(const Automaton& nfa) {

    Automaton dfa;
    dfa.alphabet = nfa.alphabet;
    
    map<set<int>, int> subset_to_id;
    queue<set<int>> q;
    
    set<int> start_subset = eps_closure({nfa.start_state}, nfa.eps_trans);
    subset_to_id[start_subset] = 0;
    dfa.start_state = 0;
    q.push(start_subset);
    
    int next_id = 1;

    while (!q.empty()) {

        set<int> curr_subset = q.front(); q.pop();
        int curr_id = subset_to_id[curr_subset];
        
        for (int s : curr_subset) {
            if (nfa.final_states.count(s)) {
                dfa.final_states.insert(curr_id);
                break;
            }
        }
        
        for (char c : dfa.alphabet) {

            set<int> next_raw;
            for (int s : curr_subset) {
                if (nfa.trans.count({s, c})) {
                    for (int n : nfa.trans.at({s, c})) next_raw.insert(n);
                }
            }
            if (next_raw.empty()) continue;
            
            set<int> next_subset = eps_closure(next_raw, nfa.eps_trans);
            if (subset_to_id.find(next_subset) == subset_to_id.end()) {
                subset_to_id[next_subset] = next_id++;
                q.push(next_subset);
            }
            dfa.trans[{curr_id, c}].insert(subset_to_id[next_subset]);

        }

    }

    return dfa;

}

// Алгоритм Бжозовского: min-DFA = det(rev(det(rev(NFA))))

Automaton
brzozowski(Automaton a) {

    return det(rev(det(rev(a))));

}

// Проверка строки детерминированным автоматом

bool
parsed_by_dfa(const Automaton& dfa, const string& input) {

    int s = dfa.start_state;

    for (char c : input) {

        auto it = dfa.trans.find({s, c});

        if (it != dfa.trans.end()) {
            s = *(it->second.begin());
        } else {
            return false;
        }

    }

    return dfa.final_states.count(s) > 0;

}

// Распечатка конечного автомата

void print(const Automaton& a, string title) {

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

    // Построение ДКА

    Automaton dfa = det(nfa);

    print(dfa, "ДКА (DFA)");

    // Минимизация по Бжозовскому

    Automaton min_dfa_brz = brzozowski(nfa);

    print(min_dfa_brz, "Минимальный ДКА (min-DFA) (по Бжозовскому)");

    // Проверка строк на принадлежность языку

    std::println("Введите строку из алфавита {{a,b,c}} (или exit) для проверки с помощью мимнимального ДКА.");
    
    while (true) {

        string input;

        std::cout << "> ";
        std::cin >> input;

        if (input == "exit") {
           break;
        }

        if (parsed_by_dfa(min_dfa_brz, input)) {
            std::println("Строка {}принадлежит{} языку.", GREEN, RESET);
        } else {
            std::println("Строка {}не принадлежит{} языку.", RED, RESET);
        }

    }

}

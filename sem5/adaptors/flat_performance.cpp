#include <map>
#include <unordered_map>
#include <flat_map>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>

int main() {

    using std::chrono::duration;
    using namespace std::chrono;

    static const long long size_insert = 16'277'216;
    static const long long size_search = 1'048'576;

    std::vector<long long> rnd_insert(size_insert);
    std::vector<long long> rnd_search(size_search);

    std::cout << "Generating..." << std::endl;
    
    std::mt19937_64 gen(207);

    std::uniform_int_distribution<long long> dis(
        std::numeric_limits<long long>::min(),
        std::numeric_limits<long long>::max());    
    std::uniform_int_distribution<size_t> dis_index(
        0,
        rnd_insert.size() - 1);

    auto t0 = system_clock::now();
    for (auto& v : rnd_insert) v = dis(gen);
    for (auto& v : rnd_search) v = rnd_insert[dis_index(gen)]; 
    duration<double> d0 = system_clock::now() - t0;
    std::cout << "mt19937_64: " << d0.count() << " sec" << std::endl;

    std::cout << "Inserting..." << std::endl;

    std::map<long long, long long> m;
    std::unordered_map<long long, long long> um;

    auto t1 = system_clock::now();
    for (auto v : rnd_insert) {
        m[v] = v;
    }
    duration<double> d1 = system_clock::now() - t1;
    std::cout << "m: " << d1.count() << " sec" << std::endl;

    auto t_insert_fm = system_clock::now();
//    std::flat_map<long long, long long> fm;
//    for (auto v : rnd_insert) {
//        fm[v] = v;
//    }
    std::flat_map<long long, long long> fm(m.begin(), m.end());
    duration<double> d_insert_fm = system_clock::now() - t_insert_fm;
    std::cout << "fm: " << d_insert_fm.count() << " sec" << std::endl;

    um.reserve(size_insert);

    auto t2 = system_clock::now();
    for (auto v : rnd_insert) {
        um[v] = v;
    }
    duration<double> d2 = system_clock::now() - t2;
    std::cout << "um: " << d2.count() << " sec" << std::endl;

    std::cout << "Searching..." << std::endl;

    auto t3 = system_clock::now();
    for (auto v : rnd_search) {
        [[maybe_unused]] volatile auto res = m.find(v);
    }
    duration<double> d3 = system_clock::now() - t3;
    std::cout << "m: " << d3.count() << " sec" << std::endl;

    auto t_search_fm = system_clock::now();
    for (auto v : rnd_search) {
        [[maybe_unused]] volatile auto res = fm.find(v);
    }
    duration<double> d_search_fm = system_clock::now() - t_search_fm;
    std::cout << "fm: " << d_search_fm.count() << " sec" << std::endl;

    auto t4 = system_clock::now();
    for (auto v : rnd_search) {
        [[maybe_unused]] volatile auto res = um.find(v);
    }
    duration<double> d4 = system_clock::now() - t4;
    std::cout << "um " << d4.count() << " sec" << std::endl;

}

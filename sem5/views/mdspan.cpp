// #include <mdspan>
#include <experimental/mdspan>
#include <vector>
#include <iostream>

int
main()
{

    std::vector v{1,2,3,4,5,6,7,8};

    std::cout << "v.size() = " << v.size() << "\n";
    std::cout << "v = ";
    for (auto& e : v)
         std::cout << e << " ";
    std::cout << "\n\n";

    std::mdspan m{v.data(), 2, 4};

    std::cout << "m.rank() = " << m.rank() <<'\n';
    std::cout << "m.extend(0) = " << m.extent(0) <<'\n';
    std::cout << "m.extend(1) = " << m.extent(1) <<'\n';

    for(std::size_t i = 0; i < m.extent(0); ++i){
        for(std::size_t j = 0; j < m.extent(1); ++j){
            std::cout << m[i, j] << " ";
        }
        std::cout<<'\n';
    }
    std::cout<<'\n';

    std::mdspan m2{v.data(), 4, 2};

    std::cout << "m2.rank():" << m2.rank() <<'\n';
    std::cout << "m2.extend(0) = " << m2.extent(0) <<'\n';
    std::cout << "m2.extend(1) = " << m2.extent(1) <<'\n';

    for(std::size_t i = 0; i < m2.extent(0); ++i){
        for(std::size_t j = 0; j < m2.extent(1); ++j){
            std::cout << m2[i,j] << " ";
        }
        std::cout<<'\n';
    }
    std::cout<<'\n';

}
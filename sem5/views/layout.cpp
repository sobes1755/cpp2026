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

    std::mdspan<int,
        std::extents<std::size_t,std::dynamic_extent,std::dynamic_extent>,
        std::layout_right>
        mr{v.data(), 4, 2};

    std::cout << "mr.rank() = " << mr.rank() <<'\n';
    std::cout << "mr.extend(0) = " << mr.extent(0) <<'\n';
    std::cout << "mr.extend(1) = " << mr.extent(1) <<'\n';

    for(std::size_t i = 0; i < mr.extent(0); ++i){
        for(std::size_t j = 0; j < mr.extent(1); ++j){
            std::cout << mr[i, j] << " ";
        }
        std::cout<<'\n';
    }
    std::cout<<'\n';

    std::mdspan<int,
        std::extents<std::size_t,std::dynamic_extent,std::dynamic_extent>,
        std::layout_left>
        ml{v.data(), 4, 2};

    std::cout << "ml.rank() = " << ml.rank() <<'\n';
    std::cout << "ml.extend(0) = " << ml.extent(0) <<'\n';
    std::cout << "ml.extend(1) = " << ml.extent(1) <<'\n';

    for(std::size_t i = 0; i < ml.extent(0); ++i){
        for(std::size_t j = 0; j < ml.extent(1); ++j){
            std::cout << ml[i, j] << " ";
        }
        std::cout<<'\n';
    }
    std::cout<<'\n';

}
 

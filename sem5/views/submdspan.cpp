// #include <mdspan>
#include <experimental/mdspan>
#include <vector>
#include <iostream>

int
main()
{

    constexpr size_t X = 2;
    constexpr size_t Y = 3;
    constexpr size_t Z = 4;

    std::vector<double> v(X * Y * Z);
    for (size_t i = 0; i < v.size(); ++i) v[i] = i;

    std::mdspan m3d{v.data(), X, Y, Z};

    for (size_t x = 0; x < X; ++x) {
        auto m2d = std::submdspan(m3d, x, std::full_extent, std::full_extent);

        std::cout << "x = " << x << ":\n";
        for (size_t i = 0; i < m2d.extent(0); ++i) {
            for (size_t j = 0; j < m2d.extent(1); ++j) 
                std::cout << m2d[i, j] << "\t";
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    for (size_t y = 0; y < Y; ++y) {
        auto m2d = std::submdspan(m3d, std::full_extent, y, std::full_extent);

        std::cout << "y = " << y << ":\n";
        for (size_t i = 0; i < m2d.extent(0); ++i) {
            for (size_t j = 0; j < m2d.extent(1); ++j) 
                std::cout << m2d[i, j] << "\t";
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    for (size_t z = 0; z < Z; ++z) {
        auto m2d = std::submdspan(m3d, std::full_extent, std::full_extent, z);

        std::cout << "z = " << z << ":\n";
        for (size_t i = 0; i < m2d.extent(0); ++i) {
            for (size_t j = 0; j < m2d.extent(1); ++j) 
                std::cout << m2d[i, j] << "\t";
            std::cout << "\n";
        }
        std::cout << "\n";
    }

}

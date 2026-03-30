// #include <mdspan>
#include <experimental/mdspan>
#include <vector>
#include <iostream>

template <typename T>
struct ScalingAccessor {

    using element_type = T;
    using data_handle_type = T*;
    using reference = T;
    using offset_policy = ScalingAccessor<T>;

    T scale_ = T{1};

    ScalingAccessor() = default;  // They say it's used by mdspan...
    explicit ScalingAccessor(T scale) : scale_(scale) {}  // They say "explicit" is recommended by C++ Core Guidelines...

    template <typename OtherT>
    ScalingAccessor(const ScalingAccessor<OtherT>& other) noexcept : scale_(other.scale_) {}  // Used by submdspan...

    constexpr reference access(data_handle_type p, std::size_t i) const noexcept {
        return p[i] * scale_;
    }
    constexpr data_handle_type offset(data_handle_type p, std::size_t i) const noexcept {
        return p + i;
    }

};

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
        std::extents<std::size_t, std::dynamic_extent, std::dynamic_extent>,
        std::layout_right>
        m{v.data(), 4, 2};

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

    std::dextents<std::size_t, 2> extents{4, 2};
    std::layout_right::mapping<std::dextents<std::size_t, 2>> mapping{extents};
    ScalingAccessor<int> accessor{2};

    std::mdspan ms{v.data(), mapping, accessor};

    std::cout << "ms.rank() = " << ms.rank() <<'\n';
    std::cout << "ms.extend(0) = " << ms.extent(0) <<'\n';
    std::cout << "ms.extend(1) = " << ms.extent(1) <<'\n';

    for(std::size_t i = 0; i < ms.extent(0); ++i){
        for(std::size_t j = 0; j < ms.extent(1); ++j){
            std::cout << ms[i, j] << " ";
        }
        std::cout<<'\n';
    }
    std::cout<<'\n';

}
 

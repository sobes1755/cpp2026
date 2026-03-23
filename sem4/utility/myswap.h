template <typename T>
inline void myswap(T& a, T& b) noexcept {
  T tmp(std::move(a));
  a = std::move(b);
  b = std::move(tmp);
}

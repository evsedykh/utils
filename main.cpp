#include <cstddef>
#include <iostream>
#include <ostream>
#include <tuple>
#include <vector>

std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec)
{
    for(int it: vec){
        os << it << " ";
    }
    return os;
}

namespace detail {

template<typename Wanted, size_t N, typename... Args>
struct GetIndexByTypeImpl
{
    static constexpr size_t value = N;
};

template<typename Wanted, size_t N, typename... Args>
struct GetIndexByTypeImpl<Wanted, N, Wanted, Args...>
{
    static constexpr size_t value = N;
};

template<typename Wanted, size_t N, class U, typename... Args>
struct GetIndexByTypeImpl<Wanted, N, U, Args...>
{
    static constexpr size_t value = GetIndexByTypeImpl<Wanted, N+1, Args...>::value;
};

} // namespace detail

template<typename Wanted, typename... Args>
Wanted getByType(const std::tuple<Args...> t)
{
    return std::get<detail::GetIndexByTypeImpl<Wanted, 0, Args...>::value>(t);
}

int main()
{
    std::tuple<int, double, std::vector<int>> t{10, 3.1415, {1, 2, 3, 4}};

    std::cout << "By index:\n" << std::get<0>(t) << "\n";
    std::cout << std::get<1>(t) << "\n";
    std::cout << std::get<2>(t) << "\n\n";

    // C++11
    std::cout << "By type (C++11) own getByType<T>():\n" << getByType<int>(t) << "\n";
    std::cout << getByType<double>(t) << "\n";
    std::cout << getByType<std::vector<int>>(t) << "\n\n";

#if (__cplusplus) == 201402L
    // C++14
    std::cout << "By type (C++14) std::get<T>():\n" << std::get<int>(t) << "\n";
    std::cout << std::get<double>(t) << "\n";
    std::cout << std::get<std::vector<int>>(t) << "\n\n";
#endif

    return 0;
}

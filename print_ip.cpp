#include <cstddef>
#include <iomanip>
#include <ios>
#include <limits>
#include <bitset>
#include <type_traits>
#include <iostream>
#include <vector>
#include <list>

template <typename T>       inline constexpr bool                  is_integer_v = std::numeric_limits<T>::is_integer;

template <typename T>       struct is_string                       : std::false_type {};
template <>                 struct is_string<std::string>          : std::true_type {};
template <typename T>       inline constexpr bool is_string_v = is_string<T>::value;

template <typename T>       struct is_vector                       : std::false_type {};
template <typename... Args> struct is_vector<std::vector<Args...>> : std::true_type {};
template <typename T>       inline constexpr bool is_vector_v = is_vector<T>::value;

template <typename T>       struct is_list                       : std::false_type {};
template <typename... Args> struct is_list<std::list<Args...>>   : std::true_type {};
template <typename T>       inline constexpr bool is_list_v = is_list<T>::value;

template <typename Int>
auto print_ip(const Int &val) -> std::enable_if_t<is_integer_v<Int>>
{
    const auto size = std::numeric_limits<Int>::digits;
    const auto size_with_padding = (size % 2 == 0) ? size : size + 1;
    std::bitset<size_with_padding> bs(val);

    auto bit_string = bs.to_string();
    const size_t bits = 8;
    for (size_t offset = 0; offset < bit_string.size(); offset += bits)
    {
        std::bitset<bits> bs(bit_string, offset, bits);

        if (offset + bits == bit_string.size())
            std::cout << bs.to_ullong();
        else
            std::cout << bs.to_ullong() << ".";
    }

    std::cout << std::endl;
}

template <typename Cont>
auto print_ip(const Cont &c) -> std::enable_if_t<is_string_v<Cont>>
{
    for (const auto &value : c)
        std::cout << value;

    std::cout << std::endl;
}

template <typename Cont>
auto print_ip(const Cont &c) -> std::enable_if_t<is_vector_v<Cont> || is_list_v<Cont>>
{
    for (const auto &value : c)
        if (value == c.front())
            std::cout << value;
        else
            std::cout << "." << value;

    std::cout << std::endl;
}

int main()
{
    print_ip(int8_t{-1});
    print_ip(int16_t{0});
    print_ip(int32_t{2130706433});
    print_ip(int64_t{8875824491850138409});
    print_ip(std::string{"Hello, World!"});
    print_ip(std::vector<int>{100, 200, 300, 400});
    print_ip(std::list<short>{400, 300, 200, 100});

    return 0;
}

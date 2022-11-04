#include <cstddef>
#include <iomanip>
#include <limits>
#include <bitset>
#include <type_traits>
#include <iostream>

template <typename Int>
void print_ip(const Int &val)
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

int main()
{
    print_ip(int8_t{-1});
    print_ip(int16_t{0});
    print_ip(int32_t{2130706433});
    print_ip(int64_t{8875824491850138409});

    return 0;
}

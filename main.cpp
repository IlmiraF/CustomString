#include "String.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main()
{
    std::vector<String> v;

    std::cout << "String count: ";
    size_t count;
    std::cin >> count;

    while (count-- > 0) {
        String s;
        std::cin >> s;
        v.push_back(s);
    }

    std::sort(v.begin(), v.end());
    std::reverse(v.begin(), v.end());

    for (auto& i : v)
    {
        std::cout << i << std::endl;
    }

    return 0;
}
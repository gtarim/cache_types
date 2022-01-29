#include <iostream>
#include "cache_lru.h"

int main()
{
    try
    {
        cache_lru<std::string, int> cache(4);

        cache.add("gokhan", 30.1);
        cache.add("haktan", 25);
        cache.add("didem", 26);
        cache.add("lale", 60);

        cache.print();
        cache.add("ersin", 65);
        cache.print();
        cache.add("yakup", 195);
        cache.print();
        cache.add("osman", 12195);
        cache.print();

        auto gokhan = cache.get("osman");
        std::cout << *gokhan << "\n";
    }
    catch(...)
    {
        return 1;
    }

}
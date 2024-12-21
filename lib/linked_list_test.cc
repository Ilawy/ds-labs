#include "linked_list.hh"
#include "iostream"

namespace ll = dst::list;

int main()
{
    try
    {
        ll::LinkedList<int> list;
        list.add(1);
        list.add(5);
        list.add(2);
        list.add(3);
        list.add(4);
        list.add(6);

        ll::LinkedList<int> list2 = list.toSorted();

        list.forEach([](int x)
                     { std::cout << x << std::endl; });
        // list.sort();
        std::cout << "=============" << std::endl;
        list2.forEach([](int x)
                      { std::cout << x << std::endl; });

        // list2.forEach([](int x)
        //               { std::cout << x << std::endl; });
    }

    catch (const char *e)
    {
        std::cout << "ERRROR " << e << std::endl;
    }

    return 0;
}
#include "linked_list.hh"
#include "iostream"

namespace ll = dst::list;

int main()
{
    try
    {
        ll::LinkedList<int> list;
        list.add(700);
        list.add(200);
        list.add(300);
        list.add(400);
        list.add(5);

        ll::LinkedList<int> list2 = list.toSorted();

        list.forEach([](int x)
                     { std::cout << x << std::endl; });
        std::cout << " ============= " << std::endl;
        list2.forEach([](int x)
                      { std::cout << x << std::endl; });
    }

    catch (const char *e)
    {
        std::cout << "ERRROR " << e << std::endl;
    }

    return 0;
}
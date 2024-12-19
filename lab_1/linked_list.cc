#include "../lib/linked_list.hh"
#include "iostream"
namespace list = dst::list;

#ifdef wasm
#include "../lib/wasm_exp.hh"
#endif

int main()
{

    list::LinkedList<int> x;
    x.add(1);
    x.add(3);
    x.add(5);
    x.add(9);
    x.add(12);
    x.deleteAt(0);
    x.insertAfter(24, 3);
    list::LinkedList<int> reversed = x.reverse();
    x.forEach([](int value, int index)
              { std::cout << value << "\t@\t" << index << std::endl; });
    reversed.forEach([](int value, int index)
                     { std::cout << value << "\t@\t" << index << std::endl; });
}


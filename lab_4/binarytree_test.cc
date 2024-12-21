#include "binarytree.hh"
#include "iostream"

using namespace std;

int main()
{
    dst::binarytree::Tree<int> t;
    t.add(100);
    t.add(6);
    t.add(9);
    t.add(8);  //
    t.add(1);  //
    t.add(60); //
    t.add(35); //
    t.add(42); //
    t.add(45); //
    t.add(48); //
    t.add(25); //
    t.add(22);
    t.findDataInTree(70) ? cout << "Found \n" : cout << "Not Found \n"; //

    t.displayAll();
    t.Remove(42);
    t.displayAll();
    t.Remove(22);
    t.displayAll();
    t.Remove(100);
    t.displayAll();

    return 0;
}

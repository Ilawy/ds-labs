#include <iostream>
#include "../lib/stack.hh"

namespace linked_stack = dst::linked_stack;
namespace array_stack = dst::array_stack;
using namespace std;

class Lol{
    public:
        int magic = 25;
};

void display_lol(int &lol){
    cout << "Lol: " << lol << endl;
}



int main(){
    array_stack::ArrayStack<int> as;
    as.push(4);
    as.push(12);
    as.push(24);
    cout << as.peek() << endl;
    // cout << as.pop() << endl;
    // cout << as.peek() << endl;
    // cout << as.pop() << endl;
    // cout << as.peek() << endl;
    // cout << as.pop() << endl;

    as.display(display_lol);
    return 0;
}
#include "../lib/e_list.hh"
#include "iostream"

namespace el = dst::EList;

int main(){
    el::EList<int> list;
    list.push(4);
    return 0;
}
#include <iostream>

#include "search.hh"
#include "assert.h"
#include "linked_list.hh"

// Assuming dst::list::LinkedList is defined elsewhere

template <typename T>
const auto f = dst::search::linear<T>;

void testLinear()
{
    int data[] = {1, 2, 3, 4, 5};
    int length = sizeof(data) / sizeof(data[0]);
    int target = 3;

    int result = dst::search::linear(data, length, target);
    assert(result == 2); // 3 is at index 2

    target = 6;
    result = dst::search::linear(data, length, target);
    assert(result == -1); // 6 is not in the array

    double dataDouble[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    double targetDouble = 3.3;
    result = dst::search::linear(dataDouble, length, targetDouble);
    assert(result == 2); // 3.3 is at index 2

    char dataChar[] = {'a', 'b', 'c', 'd', 'e'};
    char targetChar = 'c';
    result = dst::search::linear(dataChar, length, targetChar);
    assert(result == 2); // 'c' is at index 2
}

void testLinearMany()
{
    int data[] = {1, 2, 3, 3, 4, 3, 5};
    int length = sizeof(data) / sizeof(data[0]);
    int target = 3;

    dst::list::LinkedList<int> &result = dst::search::linearMany(data, length, target);
    assert(result.length() == 3); // 3 occurs 3 times

    int target2 = 6;
    dst::list::LinkedList<int> &result2 = dst::search::linearMany(data, length, target2);
    assert(result2.length() == 0); // 6 does not occur

    double dataDouble[] = {1.1, 2.2, 3.3, 3.3, 4.4, 3.3, 5.5};
    double targetDouble = 3.3;
    dst::list::LinkedList<int> &resultDouble = dst::search::linearMany(dataDouble, length, targetDouble);
    assert(resultDouble.length() == 3); // 3.3 occurs 3 times

    char dataChar[] = {'a', 'b', 'c', 'c', 'd', 'c', 'e'};
    char targetChar = 'c';
    dst::list::LinkedList<int> &resultChar = dst::search::linearMany(dataChar, length, targetChar);
    assert(resultChar.length() == 3); // 'c' occurs 3 times
}

void testBinary()
{
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size = sizeof(data) / sizeof(data[0]);
    int target = 5;

    int result = dst::search::binary(data, size, target);
    assert(result == 4); // 5 is at index 4

    target = 10;
    result = dst::search::binary(data, size, target);
    assert(result == -1); // 10 is not in the array

    double dataDouble[] = {1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9};
    double targetDouble = 5.5;
    result = dst::search::binary(dataDouble, size, targetDouble);
    assert(result == 4); // 5.5 is at index 4

    char dataChar[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};
    char targetChar = 'e';
    result = dst::search::binary(dataChar, size, targetChar);
    assert(result == 4); // 'e' is at index 4

    // Test edge cases
    int dataEdge[] = {1};
    size = sizeof(dataEdge) / sizeof(dataEdge[0]);
    target = 1;
    result = dst::search::binary(dataEdge, size, target);
    assert(result == 0); // 1 is at index 0

    target = 2;
    result = dst::search::binary(dataEdge, size, target);
    assert(result == -1); // 2 is not in the array

    // Test array with duplicate elements
    int dataDuplicate[] = {1, 2, 2, 2, 3, 4, 5};
    size = sizeof(dataDuplicate) / sizeof(dataDuplicate[0]);
    target = 2;
    result = dst::search::binary(dataDuplicate, size, target);
    assert(result >= 1 && result <= 3); // 2 is at index 1, 2, or 3

    // Test array with negative numbers
    int dataNegative[] = {-5, -4, -3, -2, -1, 0, 1, 2, 3};
    size = sizeof(dataNegative) / sizeof(dataNegative[0]);
    target = -3;
    result = dst::search::binary(dataNegative, size, target);
    assert(result == 2); // -3 is at index 2
}

int main()
{
    testLinear();
    testLinearMany();
    testBinary();
    std::cout << "All tests passed." << std::endl;
    return 0;
}

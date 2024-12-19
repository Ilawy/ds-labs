#include <iostream>
#include <stdexcept>
#include "../lib/queue.hh"

// Test cases for LinkedQueue
int main() {
    dst::array_queue::ArrayQueue<int> q;
    q.enqueue(1);
    q.enqueue(5);
    q.enqueue(10);
    for(int i = 0; i < 3; i++){
        std::cout << q.dequeue() << std::endl;
    }
    q.dequeue();
    return 0;
}

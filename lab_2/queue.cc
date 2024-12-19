#include <iostream>
#include <stdexcept>
#include "../lib/queue.hh"

// Test cases for LinkedQueue
void testLinkedQueue() {
    std::cout << "Testing LinkedQueue..." << std::endl;

    dst::linked_queue::LinkedQueue<int> queue;
    if (!queue.is_empty()) {
        std::cerr << "Error: Newly created queue is not empty." << std::endl;
    }

    queue.enqueue(10);
    if (queue.is_empty()) {
        std::cerr << "Error: Queue is empty after enqueue." << std::endl;
    }
    if (queue.get_front() != 10 || queue.get_rear() != 10) {
        std::cerr << "Error: Front or rear value is incorrect." << std::endl;
    }

    queue.enqueue(20);
    if (queue.get_front() != 10 || queue.get_rear() != 20) {
        std::cerr << "Error: Front or rear value is incorrect." << std::endl;
    }

    int dequeued = queue.dequeue();
    if (dequeued != 10) {
        std::cerr << "Error: Dequeued value is incorrect." << std::endl;
    }
    if (queue.is_empty()) {
        std::cerr << "Error: Queue is empty after dequeue." << std::endl;
    }

    try {
        dequeued = queue.dequeue();
        queue.dequeue();
        std::cerr << "Error: Dequeuing from an empty queue did not throw an exception." << std::endl;
    } catch (const char* e) {
        // Expected behavior
    }

    std::cout << "LinkedQueue test completed." << std::endl;
}

// Test cases for ArrayQueue
void testArrayQueue() {
    std::cout << "Testing ArrayQueue..." << std::endl;

    dst::array_queue::ArrayQueue<int> queue(5);
    if (!queue.is_empty()) {
        std::cerr << "Error: Newly created queue is not empty." << std::endl;
    }

    queue.enqueue(10);
    if (queue.is_empty()) {
        std::cerr << "Error: Queue is empty after enqueue." << std::endl;
    }
    if (queue.get_front() != 10 || queue.get_rear() != 10) {
        std::cerr << "Error: Front or rear value is incorrect." << std::endl;
    }

    queue.enqueue(20);
    if (queue.get_front() != 10 || queue.get_rear() != 20) {
        std::cerr << "Error: Front or rear value is incorrect." << std::endl;
    }

    int dequeued = queue.dequeue();
    if (dequeued != 10) {
        std::cerr << "Error: Dequeued value is incorrect." << std::endl;
    }
    if (queue.is_empty()) {
        std::cerr << "Error: Queue is empty after dequeue." << std::endl;
    }

    try {
        queue.dequeue();
        queue.dequeue();
        std::cerr << "Error: Dequeuing from an empty queue did not throw an exception." << std::endl;
    } catch (const char* e) {
        // Expected behavior
    }

    std::cout << "ArrayQueue test completed." << std::endl;
}

int main() {
    testLinkedQueue();
    testArrayQueue();
    return 0;
}

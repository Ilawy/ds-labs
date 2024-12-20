#pragma once
#include "iostream"
#include <type_traits> // For std::enable_if and std::is_arithmetic

namespace dst
{
    namespace list
    {
        template <typename T>
        class LinkedList;
        class ClassicLinkedList;

        namespace list = dst::list;

        enum LinkedListError
        {
            OutOfRange,
            CannotCreateElement
        };

        template <typename T>
        class Node
        {
        private:
            Node<T> *next;
            Node<T> *prev;
            T value;

        public:
            friend class LinkedList<T>;
            friend class ClassicLinkedList;
            Node() : next(nullptr), prev(nullptr) {}
            ~Node()
            {
            }
            Node(T value) : next(nullptr), prev(nullptr), value(value) {}
        };

        template <typename T>
        class LinkedList
        {
        private:
            list::Node<T> *head = nullptr;
            list::Node<T> *tail = nullptr;
            int size = 0;
            void swapNodes(Node<T> *node_a, Node<T> *node_b)
            {
                Node<T> *a_left = node_a->prev;
                Node<T> *a_right = node_a->next;
                Node<T> *b_left = node_b->prev;
                Node<T> *b_right = node_b->next;

                // flip nodes
                if (node_b->next == node_a)
                    return swapNodes(node_b, node_a);

                if (node_a->next == node_b)
                // is isbling
                {
                    // |a_left| <--> |node_b| <--> |node_a| <--> |b_right|
                    if (a_left != nullptr)
                        a_left->next = node_b;
                    node_b->prev = a_left;
                    node_b->next = node_a;
                    node_a->prev = node_b;
                    node_a->next = b_right;
                    if (b_right != nullptr)
                        b_right->prev = node_a;
                }
                else
                // two far nodes
                {
                    // |a_left| <--> |node_b| <--> |a_right|
                    // |b_left| <--> |node_a| <--> |b_right|
                    if (a_left != nullptr)
                    {
                        a_left->next = node_b;
                    }
                    node_b->prev = a_left;
                    node_b->next = a_right;
                    a_right->prev = node_b;

                    if (b_left != nullptr)
                    {
                        b_left->next = node_a;
                    }
                    node_a->prev = b_left;
                    node_a->next = b_right;
                    if (b_right != nullptr)
                    {
                        b_right->prev = node_a;
                    }
                }

                if (head == node_a)
                    head = node_b;
                else if (head == node_b)
                    head = node_a;
                if (tail == node_a)
                    tail = node_b;
                else if (tail == node_b)
                    tail = node_a;
            }

            Node<T> *node_at(int index)
            {
                if (index < 0 || index >= size)
                    throw "out of range";

                Node<T> *current = head;

                current = head;
                int currentIndex = 0;
                while (tail != nullptr)
                {
                    if (currentIndex == index)
                        return current;
                    current = current->next;
                    currentIndex++;
                }

                throw "LOL";
            }

        public:
            void test_swap()
            {
                swapNodes(node_at(0), node_at(1));
            }

            LinkedList()
            {
            }

            LinkedList(const LinkedList &original)
            {
                Node<T> *current = original.head;
                int i = 0;
                while (current != nullptr)
                {
                    this->add(current->value);
                    current = current->next;
                }
            }

            LinkedList &operator=(const LinkedList &other)
            {
                if (this == &other)
                    return *this;

                // Clear current list
                Node<T> *current = head;
                while (current)
                {
                    Node<T> *temp = current;
                    current = current->next;
                    delete temp;
                }
                head = tail = nullptr;

                Node<T> *otherCurrent = other.head;
                while (otherCurrent)
                {
                    Node<T> *newNode = new Node<T>(otherCurrent->value);
                    if (!head)
                    {
                        head = tail = newNode;
                    }
                    else
                    {
                        tail->next = newNode;
                        tail = newNode;
                    }
                    otherCurrent = otherCurrent->next;
                }

                return *this;
            }

            ~LinkedList()
            {
                if (head != nullptr)
                {
                    Node<T> *current = head;
                    while (current != nullptr)
                    {
                        Node<T> *next_node = current->next;
                        delete current;
                        current = next_node;
                    }
                    head = tail = nullptr;
                }
            }
            void add(T value)
            {
                /*
                cases
                    - the list is empty
                    - any other element
                */
                Node<T> *new_node = new Node(value);
                if (new_node == nullptr)
                    throw LinkedListError::CannotCreateElement;
                if (head == nullptr)
                {
                    // |head| --> |new_node| <-- |tail|
                    this->head = this->tail = new_node;
                }
                else
                {
                    Node<T> *last_node = tail;
                    if (last_node == nullptr)
                    {
                        last_node = head;
                    }
                    // |last_node| <--> |new_node| <-- |tail|
                    last_node->next = new_node;
                    new_node->prev = last_node;
                    tail = new_node;
                }
                size++;
            }

            void deleteAt(int index)
            {
                /*
                cases
                    - if first node (head)
                    - anything else (also if last node)
                */
                if (index < 0 || index >= size)
                    throw LinkedListError::OutOfRange;
                Node<T> *current = head;
                int i = 0;
                while (index != i)
                {
                    current = current->next;
                    i++;
                }
                if (current == head)
                {
                    Node<T> *right_node = current->next;
                    // |head| --> |right_node|
                    this->head = right_node;
                    right_node->prev = nullptr;
                    delete current;
                }
                else
                {
                    Node<T> *left_node = current->prev;
                    Node<T> *right_node = current->next;
                    // |left_node| <--> |right_node| <-- |tail| (if right is last)
                    left_node->next = right_node;
                    right_node->prev = left_node;
                    if (right_node->next == nullptr)
                    {
                        tail = right_node;
                    }
                }

                size--;
            }

            void forEach(void (*callback)(T))
            {
                Node<T> *current = head;
                while (current != nullptr)
                {
                    callback(current->value);
                    current = current->next;
                }
            }

            void forEach(void (*callback)(T, int))
            {
                Node<T> *current = head;
                int i = 0;
                while (current != nullptr)
                {
                    callback(current->value, i);
                    i++;
                    current = current->next;
                }
            }

            int length()
            {
                return this->size;
            }

            LinkedList<T> toSorted()
            {
                LinkedList<T> result = *this;
                bool swapped;
                for (int outer = 0; outer < size - 1; outer++)
                {
                    swapped = false;
                    for (int i = 0; i < size - outer - 1; i++)
                    {
                        Node<T> *left = result.node_at(i);
                        Node<T> *right = result.node_at(i + 1);
                        if (left->value > right->value)
                        {
                            result.swapNodes(left, right);
                            swapped = true;
                        }
                    }
                }
                return result;
            }

            //         // If no two elements were swapped, then break
            //         if (!swapped)
            //             break;
            //     }
            //     return result;
            // }

            void sort()
            {
                bool swapped;
                for (int outer = 0; outer < size - 1; outer++)
                {
                    swapped = false;
                    for (int i = 0; i < size - outer - 1; i++)
                    {
                        Node<T> *left = this->node_at(i);
                        Node<T> *right = this->node_at(i + 1);
                        if (left->value > right->value)
                        {
                            this->swapNodes(left, right);
                            swapped = true;
                        }
                    }
                }
            }

            LinkedList<T> &reverse()
            {
                LinkedList<T> *result = new LinkedList<T>;
                Node<int> *current = this->tail;
                while (current != nullptr)
                {
                    result->add(current->value);
                    current = current->prev;
                }
                return *result;
            }

            void insertAfter(T data, T after)
            {
                // https://stackoverflow.com/questions/1647895/what-does-static-assert-do-and-what-would-you-use-it-for
                // https://en.cppreference.com/w/cpp/types/is_integral
                static_assert(std::is_integral<T>::value,
                              "insertAfter method can only be used when T is integer");
                Node<T> *current = this->head;
                while (current != nullptr)
                {
                    if (current->value == after)
                    {
                        Node<T> *new_node = new Node<T>(data);
                        if (current->next == nullptr)
                        {
                            // last item, add and move tail
                            //  |current| <--> |new_node| <-- |tail|
                            current->next = new_node;
                            new_node->prev = current;
                            tail = new_node;
                            this->size++;
                        }
                        else
                        {
                            // middle element, do wiring
                            //  |current| <--> |new_node| <--> |right|
                            Node<T> *right = current->next;
                            current->next = new_node;
                            new_node->prev = current;
                            new_node->next = right;
                            right->prev = new_node;
                            this->size++;
                        }
                        return;
                    }

                    current = current->next;
                }
                throw "Cannon find item";
            }

            // template <typename = typename std::enable_if<std::is_integral<T>::value>::type>
            void insertBefore(T data, T before)
            {
                static_assert(std::is_integral<T>::value,
                              "insertBefore method can only be used when T is integer");
                Node<T> *current = this->head;
                while (current != nullptr)
                {
                    if (current->value == before)
                    {
                        Node<T> *new_node = new Node<T>(data);
                        /*
                        scenarios
                            -   if it's head
                            -   if it's middle
                        */
                        if (current == head)
                        {
                            // |head| --> |new_node| <--> |current|
                            head = new_node;
                            new_node->next = current;
                            current->prev = new_node;
                            size++;
                        }
                        else
                        {
                            // |left| <--> |new_node| <--> |current|
                            Node<T> *left = current->prev;
                            left->next = new_node;
                            new_node->prev = left;
                            new_node->next = current;
                            current->prev = new_node;
                            size++;
                        }
                    }
                    current = current->next;
                }
            }
        };
    }
}
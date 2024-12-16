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
            Node() {}
            ~Node() {}
            Node(T value) : value(value) {}
        };

        template <typename T>
        class LinkedList
        {
        protected:
            list::Node<T> *head = nullptr;
            list::Node<T> *tail = nullptr;
            int size = 0;

        public:
            LinkedList() {}
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
                    // |head| --> |new_node|
                    this->head = new_node;
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
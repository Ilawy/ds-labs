

namespace dst
{
    namespace linked_stack
    {
        #include <iostream>
        
        template<typename T>
        class LinkedStack;

        template<typename T>
        class Node{
            friend class LinkedStack<T>;
            Node<T>* prev = nullptr;
            T value;

            public:
                Node(T value){
                    this->value = value;
                }
        };

        template<typename T>
        class LinkedStack{
            private:
                Node<T>* tail = nullptr;
                int size = 0;
            public:
                void push(T value){
                    Node<T>* new_node = new Node<T>(value);
                    if(this->tail == nullptr){
                        this->tail = new_node;
                        return;
                    }
                    Node<T>* old_node = tail;
                    // |old_node| <-- |new_node| <-- tail
                    new_node->prev = old_node;
                    tail = new_node;
                }

                T pop(){
                    if(tail == nullptr){
                        throw "Stack is empty";
                    }
                    Node<T> *result = tail;
                    Node<T> *left_node = tail->prev;
                    // |left_node| <-- tail
                    tail = left_node;
                    T value = result->value;
                    delete result;
                    size--;
                    return value;
                }

                T peek(){
                    if(tail == nullptr){
                        throw "Stack is empty";
                    }
                    T value = tail->value;
                    return value;
                }

                void display(void (*callback)(T&)){
                    Node<T>* current = tail;
                    while(current != nullptr){
                        callback(current->value);
                        current = current->prev;
                    }
                }
        };
    } // namespace stack
    

    namespace array_stack{

        template<typename T>
        class ArrayStack{
            private:
                T* items;
                int size;
                int top = 0;
                bool is_empty(){
                    return top == 0;
                }
                bool is_full(){
                    return top >= size;
                }

            public:
                ArrayStack(int size = 5){
                    this->size = size;
                    this->items = new T[size];
                }
                
                ~ArrayStack(){
                    delete [] this->items;
                }

                void push(T value){
                    if(is_full()){
                        throw "Stack is full";
                    }
                    this->items[top++] = value;
                }

                T pop(){
                    if(is_empty()){
                        throw "Stack is empty";
                    }
                    return this->items[--top];
                }

                T peek(){
                    if(is_empty()){
                        throw "Stack is empty";
                    }
                    return this->items[top-1];
                }

                void display(void(*callback)(T&)){
                    for(int i = top-1; i >= 0; i--){
                        callback(items[i]);
                    }
                }
        };
    }
} // namespace dst

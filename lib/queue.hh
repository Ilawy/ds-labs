namespace dst
{
  namespace queue
  {
    template <typename T>
    class Queue
    {
    public:
      virtual bool is_empty() = 0;
      virtual T &get_front() = 0;
      virtual T &get_rear() = 0;
      virtual void enqueue(T) = 0;
      virtual T dequeue() = 0;
    };

  } // namespace queue

  namespace linked_queue
  {
    template <typename T>
    class LinkedQueue;

    template <typename T>
    class Node
    {
      friend class LinkedQueue<T>;
      T value;
      Node<T> *next;

    public:
      Node(T value) { this->value = value; }
    };

    template <typename T>
    class LinkedQueue : dst::queue::Queue<T>
    {
    private:
      int size = 0;
      Node<T> *head = nullptr;
      Node<T> *tail = nullptr;

    public:
      bool is_empty() { return head == nullptr; }

      void enqueue(T value)
      {
        if (is_empty())
        {
          Node<T> *new_node = new Node<T>(value);
          head = tail = new_node;
        }
        else
        {
          // |tail| <-- |new_node| <-- |old_tail|
          Node<T> *new_node = new Node<T>(value);
          Node<T> *old_tail = tail;
          tail = new_node;
          old_tail->next = new_node;
        }
        size++;
      }

      T dequeue()
      {
        if (is_empty())
        {
          throw "Queue is empty";
        }
        Node<T> *old_node = head;
        T value = old_node->value;
        head = head->next;
        size--;
        delete old_node;
        return value;
      }

      T &get_front()
      {
        if (is_empty())
        {
          throw "Queue is empty";
        }
        return head->value;
      }

      T &get_rear()
      {
        if (is_empty())
        {
          throw "Queue is empty";
        }
        return tail->value;
      }
    };
  } // namespace linked_queue

  namespace array_queue
  {
    template <typename T>
    class ArrayQueue : dst::queue::Queue<T>
    {
    private:
      int size;
      int front = -1;
      int rear = -1;
      T *items;

    public:
      ArrayQueue(int size = 5){
        this->size = size;
        this->items = new T[size];
        front = -1;
        rear = -1;
      }

      ~ArrayQueue() {
        delete[] items;
      }

      bool is_full()
      {
        return (rear + 1) % size == front;
      }
      bool is_empty()
      {
        // std::cout << (((rear + 1) % size) == front) << std::endl;
        return front == -1;
      }

      void enqueue(T value)
      {
        if (is_full())
        {
          throw "Queue is full";
        }
        rear = (rear + 1) % size;
        items[rear] = value;
        if (front == -1) {
          front = rear;
        }
      }

      T dequeue()
      {
        if (is_empty())
        {
          throw "Queue is empty";
        }
        T value = items[front];
        if (front == rear) {
          // Queue is now empty
          front = -1; 
          rear = -1;
        } else {
          front = (front + 1) % size;
        }
        return value;
      }

      T &get_front()
      {
        int index = front;
        return items[index];
      }

      T &get_rear()
      {
        int index = rear;
        return items[index];
      }

    };
  } // namespace array_queue

} // namespace dst

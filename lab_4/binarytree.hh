#include <cstring>
#include <iostream>
using namespace std;

namespace dst
{
  namespace binarytree
  {
    template <typename T>
    class Node
    {
    public:
      T data;
      Node *right;
      Node *left;
      Node(T _data)
      {
        data = _data;
        right = left = NULL;
      }
    };

    template <typename T>
    class Tree
    {
    private:
      Node<T> *root;
      Node<T> *getNodeByData(int data)
      {
        Node<T> *current = root;
        while (current != NULL)
        {
          if (data == current->data)
          {
            return current;
          }
          else if (data > current->data)
          {
            current = current->right;
          }
          else
          {
            current = current->left;
          }
        }
        return NULL;
      }
      Node<T> *getParent(Node<T> *node)
      {
        Node<T> *parent = root;
        while (parent != NULL)
        {
          if (node == parent->right || node == parent->left)
          {
            return parent;
          }
          else if (node->data > parent->data)
          {
            parent = parent->right;
          }
          else
          {
            parent = parent->left;
          }
        }
        return NULL;
      }
      Node<T> *getMaxRight(Node<T> *node)
      {
        Node<T> *current = node; // Start Point
        inspect(current);
        while (current->right != NULL)
        {
          current = current->right;
        }
        return current;
      }

      void display(Node<T> *node)
      {
        if (node == NULL)
        {
          return;
        }
        display(node->left);
        cout << node->data << "\t:\t";
        display(node->right);
      }

      int internal_min(Node<T> *node, int last_min)
      {
        if (node == NULL)
          return last_min;
        int self_min = node->data;
        int left_min = internal_min(node->left, self_min);
        int right_min = internal_min(node->right, self_min);
        if (left_min < self_min)
        {
          self_min = left_min;
        }
        if (right_min < self_min)
        {
          self_min = right_min;
        }
        return self_min;
      }

      int internal_max(Node<T> *node, int last_max)
      {
        if (node == NULL)
          return last_max;
        int self_min = node->data;
        int left_min = internal_min(node->left, self_min);
        int right_min = internal_min(node->right, self_min);
        if (left_min > self_min)
        {
          self_min = left_min;
        }
        if (right_min > self_min)
        {
          self_min = right_min;
        }
        return self_min;
      }

      void inspect(Node<T> *node)
      {
        if (node == nullptr)
        {
          printf("\tvalue <null>\n");
          return;
        }
        printf("\tvalue %d\n", node->data);
        std::string children = "\t";
        if (node->left != nullptr)
          children += std::to_string(node->left->data);
        else
          children += "X";
        if (node->right != nullptr)
          children += "\t" + to_string(node->right->data);
        else
          children += "\tX";
        printf("%s\n", children.c_str());
      }

    public:
      Tree() { root = NULL; }
      void add(T data)
      {
        // Create Node
        Node<T> *newNode = new Node(data);
        if (root == NULL)
        {
          root = newNode;
        }
        else
        {
          Node<T> *current = root;
          Node<T> *parent = NULL;
          while (current != NULL)
          {
            parent = current; // Before Current Jumping
            if (data > current->data)
            {
              /*if(current->right == NULL){
                  current->right=newNode;
                  return;
              }*/
              current = current->right; //
            }
            else
            {
              /*if(current->left == NULL){
                  current->left=newNode;
                  return;
              }*/
              current = current->left;
            }
          }
          if (data > parent->data)
          {
            parent->right = newNode;
          }
          else
          {
            parent->left = newNode;
          }
        }
      }
      int findDataInTree(int data)
      {
        if (getNodeByData(data) == NULL)
        {
          return 0;
        }
        return 1;
      }
      int getParentBydata(int data)
      {
        Node<T> *node = getNodeByData(data);
        if (node == root)
        {
          throw "The Node is Root Not Have Parent";
        }
        if (node != NULL)
        {
          Node<T> *parent = getParent(node);
          if (parent != NULL)
          {
            return parent->data;
          }
        }
        else
        {
          throw " Node Not Found , Not Have Parent";
        }
      }
      int getMaxRightByData(int data)
      {
        Node<T> *node = getNodeByData(data);
        if (node == NULL)
        {
          throw " Node Not Found";
        }
        Node<T> *maxR = getMaxRight(node);
        return maxR->data;
      }

      void printTree(Node<T> *node, int level)
      {
        if (node == nullptr)
        {
          if (level == 0)
          {
            cout << "x" << endl;
          }
          else
          {
            for (int i = 0; i < level - 1; i++)
            {
              cout << "  ";
            }
            cout << "x" << endl;
          }
          return;
        }

        printTree(node->right, level + 1);

        for (int i = 0; i < level; i++)
        {
          cout << "  ";
        }
        cout << node->data << endl;

        printTree(node->left, level + 1);
      }

      void displayAll()
      {
        display(root);
        cout << endl;
      }

      void Remove(int value)
      {
        Node<T> *node = getNodeByData(value);
        Node<T> *parent = getParent(node);

        // inspect(node);

        if (node == nullptr)
          return;
        if (node == root)
        // root
        {
          if (node->left == nullptr && node->right == nullptr)
          // single node tree
          {
            delete node;
            root = nullptr;
          }
          else if (node->left == nullptr && node->right != nullptr)
          // root with only one
          {
            this->root = node->right;
            delete node;
          }else if(node->right == nullptr && node->left != nullptr){
            this->root = node->left;
            delete node;
          }
          else
          // root with children
          {
            Node<T> *newRoot = getMaxRight(root->left);
            Node<T> *newRootParent = getParent(newRoot);
            if (newRootParent->right = newRoot)
              newRootParent->right = nullptr;
            else
              newRootParent->left = nullptr;
            root = newRoot;
            root->left = node->left;
            root->right = node->right;
            
            delete node;
            // printf("xx %d\n", node->data);
          }
          // TODO: handle root with one child only
        }
        else
        // non-root node
        {
          if (node->left == nullptr && node->right == nullptr)
          // exit node
          {
            if (parent->right == node)
              parent->right = nullptr;
            else
              parent->left = nullptr;
            delete node;
          }
          else
          // middle node
          {
            Node<T> *left = node->left; // GREEN
            if (left != nullptr)
            {
              Node<T> *mostRight = getMaxRight(left);     // BLUE
              Node<T> *liteParent = getParent(mostRight); // BLUE
              if (liteParent->left == mostRight)
                liteParent->left = nullptr;
              else
                liteParent->right = nullptr;

              if (parent->left == node)
                parent->left = mostRight;
              else
                parent->right = mostRight;

              mostRight->right = node->right;
              mostRight->left = node->left;
            }
            else
            // middle with one child
            {
              // |parent| --> |right|
              if (parent->right == node)
                parent->right = node->right;
              else
                parent->left = node->right;
            }
            delete node;
          }
        }
      }
      int min()
      {
        if (root == nullptr)
          throw "Tree is empty";
        return internal_min(root, root->data);
      }

      int max() { return internal_max(root, root == nullptr ? 0 : root->data); }
    };

  } // namespace binarytree
} // namespace dst

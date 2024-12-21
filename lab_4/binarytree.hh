#include <cstring>
#include <iostream>
using namespace std;

namespace dst {
namespace binarytree {
template <typename T> class Node {
public:
  T data;
  Node *Right;
  Node *Left;
  Node(T _data) {
    data = _data;
    Right = Left = NULL;
  }
};

template <typename T> class Tree {
private:
  Node<T> *root;
  Node<T> *getNodeByData(int data) {
    Node<T> *current = root;
    while (current != NULL) {
      if (data == current->data) {
        return current;
      } else if (data > current->data) {
        current = current->Right;
      } else {
        current = current->Left;
      }
    }
    return NULL;
  }
  Node<T> *getParent(Node<T> *node) {
    Node<T> *parent = root;
    while (parent != NULL) {
      if (node == parent->Right || node == parent->Left) {
        return parent;
      } else if (node->data > parent->data) {
        parent = parent->Right;
      } else {
        parent = parent->Left;
      }
    }
    return NULL;
  }
  Node<T> *getMaxRight(Node<T> *node) {
    Node<T> *current = node; // Start Point
    while (current->Right != NULL) {
      current = current->Right;
    }
    return current;
  }

  void display(Node<T> *node) {
    if (node == NULL) {
      return;
    }
    display(node->Left);
    cout << node->data << " : ";
    display(node->Right);
  }

  int internal_min(Node<T> *node, int last_min) {
    if (node == NULL)
      return last_min;
    int self_min = node->data;
    int left_min = internal_min(node->Left, self_min);
    int right_min = internal_min(node->Right, self_min);
    if (left_min < self_min) {
      self_min = left_min;
    }
    if (right_min < self_min) {
      self_min = right_min;
    }
    return self_min;
  }

  int internal_max(Node<T> *node, int last_max) {
    if (node == NULL)
      return last_max;
    int self_min = node->data;
    int left_min = internal_min(node->Left, self_min);
    int right_min = internal_min(node->Right, self_min);
    if (left_min > self_min) {
      self_min = left_min;
    }
    if (right_min > self_min) {
      self_min = right_min;
    }
    return self_min;
  }

  void inspect(Node<T> *node) {
    if (node == nullptr) {
      printf("\tvalue <null>\n");
      return;
    }
    printf("\tvalue %d\n", node->data);
    std::string children = "\t";
    if (node->Left != nullptr)
      children += std::to_string(node->Left->data);
    else
      children += "X";
    if (node->Right != nullptr)
      children += "\t" + to_string(node->Right->data);
    else
      children += "\tX";
    printf("%s\n", children.c_str());
  }

public:
  Tree() { root = NULL; }
  void add(T data) {
    // Create Node
    Node<T> *newNode = new Node(data);
    if (root == NULL) {
      root = newNode;
    } else {
      Node<T> *current = root;
      Node<T> *parent = NULL;
      while (current != NULL) {
        parent = current; // Before Current Jumping
        if (data > current->data) {
          /*if(current->Right == NULL){
              current->Right=newNode;
              return;
          }*/
          current = current->Right; //
        } else {
          /*if(current->Left == NULL){
              current->Left=newNode;
              return;
          }*/
          current = current->Left;
        }
      }
      if (data > parent->data) {
        parent->Right = newNode;
      } else {
        parent->Left = newNode;
      }
    }
  }
  int findDataInTree(int data) {
    if (getNodeByData(data) == NULL) {
      return 0;
    }
    return 1;
  }
  int getParentBydata(int data) {
    Node<T> *node = getNodeByData(data);
    if (node == root) {
      throw "The Node is Root Not Have Parent";
    }
    if (node != NULL) {
      Node<T> *parent = getParent(node);
      if (parent != NULL) {
        return parent->data;
      }
    } else {
      throw " Node Not Found , Not Have Parent";
    }
  }
  int getMaxRightByData(int data) {
    Node<T> *node = getNodeByData(data);
    if (node == NULL) {
      throw " Node Not Found";
    }
    Node<T> *maxR = getMaxRight(node);
    return maxR->data;
  }

  void printTree(Node<T> *node, int level) {
    if (node == nullptr) {
      if (level == 0) {
        cout << "x" << endl;
      } else {
        for (int i = 0; i < level - 1; i++) {
          cout << "  ";
        }
        cout << "x" << endl;
      }
      return;
    }

    printTree(node->Right, level + 1);

    for (int i = 0; i < level; i++) {
      cout << "  ";
    }
    cout << node->data << endl;

    printTree(node->Left, level + 1);
  }

  void displayAll() {
    display(root);
    cout << endl;
  }

  void Remove(int value) {
    Node<T> *node = getNodeByData(value);
    Node<T> *parent = getParent(node);

    // inspect(node);

    if (node == nullptr)
      return;
    if (node == root)
    // root
    {
      if (node->Left == nullptr && node->Right == nullptr)
      // single node tree
      {
        delete node;
        root = nullptr;
      } else
      // root with children
      {
        Node<T> *newRoot = getMaxRight(root->Left);
        Node<T> *newRootParent = getParent(newRoot);
        if (newRootParent->Right = newRoot)
          newRootParent->Right = nullptr;
        else
          newRootParent->Left = nullptr;
        root = newRoot;
        root->Left = node->Left;
        root->Right = node->Right;
        delete node;
        // printf("xx %d\n", node->data);
      }
      // TODO: handle root with one child only
    } else
    // non-root node
    {
      if (node->Left == nullptr && node->Right == nullptr)
      // exit node
      {
        if (parent->Right == node)
          parent->Right = nullptr;
        else
          parent->Left = nullptr;
        delete node;
      } else
      // middle node
      {
        Node<T> *left = node->Left; // GREEN
        if (left != nullptr) {
          Node<T> *mostRight = getMaxRight(left);     // BLUE
          Node<T> *liteParent = getParent(mostRight); // BLUE
          if (liteParent->Left == mostRight)
            liteParent->Left = nullptr;
          else
            liteParent->Right = nullptr;

          if (parent->Left == node)
            parent->Left = mostRight;
          else
            parent->Right = mostRight;

          mostRight->Right = node->Right;
          mostRight->Left = node->Left;
        } else
        // middle with one child
        {
          // |parent| --> |right|
          if (parent->Right == node)
            parent->Right = node->Right;
          else
            parent->Left = node->Right;
        }
        delete node;
      }
    }
  }
  int min() {
    if (root == nullptr)
      throw "Tree is empty";
    return internal_min(root, root->data);
  }

  int max() { return internal_max(root, root == nullptr ? 0 : root->data); }
};

} // namespace binarytree
} // namespace dst

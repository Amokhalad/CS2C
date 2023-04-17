#ifndef BST_H_
#define BST_H_
#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

template <typename Key, typename Value>
class BinarySearchTree {
  struct Node {
    Key key;
    int balance_factor
    Value value;
    Node *left, *right;
    Node(const Key& key) : key{ key }, balance_factor{ 0 }left{ nullptr }, right(nullptr) {}

    Node(const Key& key, const Value& value)
        : key(key), balance_factor{ 0 }, value(value), left(nullptr), right(nullptr) {}

    void print(int depth=0) const {
      if (left != nullptr) {
        left->print();
      }
      cout << key << ": " << value << " (bf: " << balance_factor<< ")";
      if (right != nullptr) {
        right->print();
      }
    }
    
    
    bool contains(const Key& k) const {
      if (k == key) {
        return true;
      } else if (k < key) {
        if (left == nullptr) {
          return false;
        } else {
          return left->contains(k);
        }
      } else { // if (k > key)
        if (right == nullptr) {
          return false;
        } else {
          return right->contains(k);
        }
      }
    }
    // TODO update balance factor as needed
    bool insert(const Key& new_key, const Value& new_value) {
      if (new_key == key) {
        return false;
      } else if (new_key < key) {  // Need to insert to the left
        if (left == nullptr) {
          --balance_factor;
          left = new Node(new_key, new_value);
          return true;
        } else {
          int prev_left_bf = left->balance_factor;
          bool result = left->insert( new_key, new_value );
          int cur_left_bf = left->balance_factor;
          // if the left subtree is bigger after the insert...
          if ( abs(cur_left_bf) > abs(prev_left_bf) ) {
                ++balance_factor;
           }
          return result;
        }
      } else { // if (new_key > key)  Need to insert to the right
        if (right == nullptr) {
            ++balance_factor;
          right = new Node(new_key, new_value);
          return true;
        } else {
          int prev_right_bf = right->balance_factor;
          bool result = right->insert( new_key, new_value );
          int cur_right_bf = right->balance_factor;
          // if the right subtree is bigger after the insert...
          if ( abs(cur_right_bf) > abs(prev_right_bf) ) {
                ++balance_factor;
           }
          return result;
        }
      }
    }
    // TODO update balance factor as needed
    Value& operator[](const Key& k) {
      if (k == key) {
        return value;
      } else if (k < key) {  // Need to insert to the left
        if (left == nullptr) {
          left = new Node(k);
          return left->value;
        } else {
          return (*left)[k];
        }
      } else { // if (k > key)  Need to insert to the right
        if (right == nullptr) {
          right = new Node(k);
          return right->value;
        } else {
          return (*right)[k];
        }
      }
    }
  };

  Node *root;

public:
  BinarySearchTree() : root(nullptr) {}

  ~BinarySearchTree() {
    delete root;
  }

  void print() {
    if (root != nullptr) {
      root->print();
    }
  }

  bool insert(const Key& key, const Value& value) {
    if (root == nullptr) {
      root = new Node(key, value);
      return true;
    } else {
      return root->insert(key, value);
    }
  }

  bool contains(const Key& key) {
    if (root == nullptr) {
      return false;
    } else {
      return root->contains(key);
    }
  }

  Value& operator[](const Key& key) {
    if (root == nullptr) {
      root = new Node(key);
      return root->value;
    } else {
      return (*root)[key];
    }
  }
};

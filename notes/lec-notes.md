# CS 2C: Advanced Data Struct/ Algorithm in C++
    Foothill College
    Instructor: Mikel Mcdaneil
    Office Hours: TBA
    Lecture: Asynchronous
    Author: Mokhalad Aljuboori
    Course Content: https://mikelmcdaniel.github.io/dsaa/#part1

## Table of Contents
- [CS 2C: Advanced Data Struct/ Algorithm in C++](#cs-2c-advanced-data-struct-algorithm-in-c)
  - [Table of Contents](#table-of-contents)
- [Part 3: Trees](#part-3-trees)
  - [Binary Search Trees](#binary-search-trees)
    - [Binary Search Tree: Insert and Contains Implementation](#binary-search-tree-insert-and-contains-implementation)


# Part 3: Trees

## Binary Search Trees

### Binary Search Tree: Insert and Contains Implementation

**Binary Search Tree**: smaller things to the left and larger things to the right, or oppsite/
**Balanced Binary Search tree**, where the left and right halfs are equal

```md
         m
      /     \
     /       \
    c         g
  /   \     /   \
 /     \   x     \
a       d         z
```

**Implementation of insert contains and printing the tree** 
```cpp
template <typename T>
class BinarySearchTree {
    struct Node {
        T value;
        Node *left, *right;
        Node(const T& value) : value(value), left(nullptr), right(nullptr) {}

        void print() {
            if (left != nullptr) {
                 left->print();
            }
            cout << value << endl;

            if (right != nullptr) {
                right->print();
            }
        }



        bool insert(const T& new_value) {
            if (new_value == value) {
                return false;
            } else if(new_value < value) { //Need to insert to the left
                if (left == nullptr) {
                    left = new Node(new_value);
                    return true;
                } else {
                    return left->insert(new_value);
                }
            }
            else if(new_value > value) { //Need to insert to the left
                if (right == nullptr) {
                    right = new Node(new_value);
                    return true;
                } else {
                    return right->insert(new_value);
                }
            }
        }

        bool contains(const T& v) {
            if (v == value) {
                return true;
            } else {
                if (v < value) {
                    if (left == nullptr) {
                        return false;
                    } else {
                        return left->contains(v);
                    }
                } else if(v > value) {
                    if (right == nullptr) {
                        return false;
                    } else {
                        return right->contains(v);
                    }
                }
            }
        }
    };

    Node *root;

public:
    BinarySearchTree() : root(nullptr) {}

    bool insert(const T& value) {
        if (root == nullptr) {
            root = new Node(value);
            return true;
        } else {
            return root->insert(value);
        }
    }
    
    bool contains(const T& value) {
        if (root == nullptr) {
            return false;
        } else {
            return root->contains(value);
        }
    }
    // would not implement this in a real BST class
    void print() {
        if (root != nullptr) {
            root->print();
        }
    }
};
```
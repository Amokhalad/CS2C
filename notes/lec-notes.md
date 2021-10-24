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
  - [AVL Trees](#avl-trees)
    - [All the possible cases where there is an imbalance.](#all-the-possible-cases-where-there-is-an-imbalance)
    - [AVL Tree Big-O](#avl-tree-big-o)


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

## AVL Trees
Example of a rotation where $<n>$ is a subtree.
- It does not matter what's inside the subtree. 
```
       c                b
      / \             /   \
     b  <3>    =>   a       c
    / \            / \     / \
   a  <3>        <1> <2> <3> <4>
  / \
<1> <2>
```

### All the possible cases where there is an imbalance.
2 Cases + the mirror cases drawing of each case. 
- Note: we must update the root to point to b instead of c.
```md
   Case 1:         Case 2:
   left-left       left-right

       c              c                    b
      / \            / \                 /   \
     b  <4>         a  <4>    =>       a       c
    / \            / \                / \     / \ 
   a  <3>        <1>  b             <1> <2> <3> <4>
  / \                / \        
<1> <2>            <2> <3>      
```

### AVL Tree Big-O
**Tricky Question:** Given an avl tree, what's the worst possible case for the height?\
**Alternative Question:** For some height, what is the smallest number of nodes that a tree with that height can have?

$N(h)=$ smallest number of nodes that a tree with height h.
$N(h)$ | h |
-------|---|
0 | 0
1 | 1
4 | 3
7 | 4
$1 + N(h - 1) + N(h - 2)$ | h
```md
h:  1    2        3          4

    O    O        0          0
          \      / \       /   \
           O    1   2     2     3
                     \     \   / \
                      2     2 3   3
                                   \
                                    3
```

$N(0) = 0$\
$N(1) = 1$\
$N(h) = 1 + N(h - 1) + N(h - 2)$

${0, 1, 2, 3, 4, 5, 6, 7, 8, ..., h}$\
${0, 1, 2, 4, 7, 12, 20, 33, 53, ..., N(h)}$\
${1, 2, 3, 5, 8, 13, 21, 34, 55, ... ,}$  `fib`(n)\
$\therefore \: N(b) =$ `fib(n)` $- 1$

`fib` $(n) = O(\phi^n)$\
$\therefore \: N(h) = O(\phi^h )$\
$h = O(log(N(h)) = O(log(n))$

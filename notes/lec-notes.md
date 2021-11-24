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
    - [Balance Factor](#balance-factor)
      - [What is a balance factor?](#what-is-a-balance-factor)
- [Part 5: Priority Queues and Sorting](#part-5-priority-queues-and-sorting)
  - [Min Heaps](#min-heaps)
  - [Heap Sort Idea](#heap-sort-idea)
    - [What is the big O](#what-is-the-big-o)
  - [Merge Sort Idea](#merge-sort-idea)
    - [Merging](#merging)
      - [Big O](#big-o)


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

<hr>

### Balance Factor
#### What is a balance factor?
The difference in height between the left and right subtrees can never be more than 1 or less than -1/
- **Balance Factor** =  height(rst) - height(lst)
- if I add to my height, that's when I update the balance factor
- I don't want to change the balance factor if the height doesn't change


# Part 5: Priority Queues and Sorting
## Min Heaps
When it's Use full:
- a representative of binary tree is useful when the binary tree is **full**
  - Full: every layer is full except for the last one.
    - The last one is filled from **left to right**
  
**Disadvantages of Binary Search Trees:**
- Node: contains the left and right pointer, but containing the left and right pointer is a lot of space. 
- Another disadvantage is when going from left to right node, it's a lot of jumps from memory to memory.

**Advantages of Array Tree**
- Save a lot of space, you are able to go left right or parent using math.
- memory in an array is organized well next to each other vs dynamic allocation.
```
    Tree:             Array:
      d:0
     /   \             0 : 1 : 2 : 3 : 4 : 5 : 6   
    b:1    f:2        | d | b | f | a | c | e | g |
   /  \   /  \
  a:3 c:4 e:5 g:6
  / \
-:7 -:8
```
|index| left| right| parent|
|-----|-----|------|-------|
|0    |  1  |   2  |   -   |
|1    |  3  |   4  |   0   |
|2    |  5  |   6  |   0   |
|3    |  7  |   8  |   1   |
|i    |$2i +1$| $2i +2$|$(i-1)/2$|

- the left most nodes seem to be increasing by a power of 2.

## Heap Sort Idea
- the first thing you have to do is build the max heap from a given vector or array that is in a random order.
- you pop whatever is at the front of the max heap, and you put it at the end.

**Step one: building the max heap**
```md
A random list:
  0   1   2   3   4
| m | i | k | e | l |

First step: Build the max heap by inserting from index 0 through 4
        
        m:0
       / \
     i:1  k:2         i and k are smaller than m so we are not going to swap.
     / \
   e:3 l:4            e is smaller than i, 
                      but l is bigger than i so we percolate it up

Step 1 done: built the max heap.
| 0   1   2   3   4 |
| m | l | k | e | i |
       m:0
       / \
     l:1  k:2         
     / \
   e:3 i:4           
```

**Step two: popping from the front of the max heap and put it at the end.**
- we still do the swap, but we aren't going to actually pop anythifgvgfng.
```
| 0   1   2   3   4 |
| m | l | k | e | i |

swap front and back and now m is no longer part of the tree.
| 0   1   2   3 |
| i | l | k | e |

percolate i down. Swap l and i because l is bigger of the two children, and l is bigger than i.
| 0   1   2   3 |
| l | i | k | e |

swap front and back. L is not longer part of our heap
| 0   1   2 |
| e | i | k |

percolate e down. K is the bigger of e's two children, and k is bigger than e.
| 0   1   2 |
| k | i | e | 

Swap front and back
| 0   1   2 |
| e | i |


now our list looks like this:
| e | i | k | l | m |
```

### What is the big O
**first phase: Building the max heap**\
$O(log(1) + log(2) + ... + log(n)) = O(n*log(n))$

**second phase: swap and pop**
- swap and top are $O(1)$
- the main thing that matters is pop from the max heap and that is $O(log(n))$

First phase + second phase = $O(n*log(n)) + O(log(n)) = O(n*log(n))$


## Merge Sort Idea
### Merging
Two sorted Lists:

- keeping track of the what next element is.
```
a, c, z  |    b, x, y

0 1 2 3 4 5
a b c x y z
```
#### Big O
list1.size() ==  m\
list2.size() ==  n
Merged List = m + n\
$O( m + n )$ or $O(n)$ where n is the size of the output.

if you have a list, break it up in half's until there is one item in the sub list, if there is return. Then Sort both half's, then merge it.
```
zbacxy

zba     cxy

z ba        c xy

Coming up from calls:

z ab    c xy

abz     cxy

abzcxy
```
The merge step is O(n)\
$T(0) = T(1) = O(1)$\
$T(n) = O(1) + 2T(n/2) + O(n)$\
T(n) = O(1) for checking base case + 2T(n/2) for recursing on left and right halves + O(n) for merge step

**Simplifying**\
$T(n) = 2T(n/2) + O(n)$\
$T(n)= 2(2T((n/2)/2) + O(n/2)) + O(n)$\
$= 4T(n/4) + 2O(n)$\
$T(n) = 8T(n/8) + 3O(n)$\
$k times = 2^kT(n/2^k) + kO(n)$\

**getting rid of $T(n/2^k)$**

$n / 2^k = 1$\
$k = log_2(n)$\
$k times = 2^{log_2(n)}T(n/2^{log_2(n)}) + log_2(n)O(n)$\
$=n + O(nlog(n))$\
**Big-O:**\
$=O(nlog(n))$

#### Down side of merge step:
For the merge step, often time syou need a buffer to store the sorted sub list. You cannot do it in place.

#### uses of merge sort
merge sort is very useful because often times you have two sorted lists, and you want to combine both of them. Merging is the way to go.
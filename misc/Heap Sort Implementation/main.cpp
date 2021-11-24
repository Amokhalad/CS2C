#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
using namespace std;


int parent_index(int index) { return (index - 1) / 2; }
int left_index(int index) { return 2 * index + 1; }
int right_index(int index) { return 2 * index + 2; }

bool has_left_child(int index, int heap_size) { return left_index(index) < heap_size; }
bool has_right_child(int index, int heap_size) { return right_index(index) < heap_size; }
bool has_child(int index, int heap_size) { return has_left_child(index, heap_size); }

template <typename RandomAccessIt>
RandomAccessIt largest_child(RandomAccessIt begin, int index, int heap_size) {
    if (has_right_child(index, heap_size)) {
        RandomAccessIt left = begin + left_index(index);
        RandomAccessIt right = begin + right_index(index);
        return *left > *right ? left : right;
    } else { // there is only a left child
        return begin + left_index(index);
    }
}

template <typename RandomAccessIt>
void percolate_up(RandomAccessIt begin, RandomAccessIt it) {
    RandomAccessIt parent = begin + parent_index(it - begin);
    // don't need to consider the condition when it != begin because if it doesn't, parent will be 0
    while (*it > *parent) {
        std::swap(*it, *parent);
        it = parent;
        parent = begin + parent_index(it - begin);
    }
}
template <typename RandomAccessIt>
void percolate_down(RandomAccessIt begin, RandomAccessIt end) {
    // while I might need to percolate down more...
    //  check if I need to swap with the larger child.
    //  else: break.
    RandomAccessIt it = begin;
    RandomAccessIt lc = largest_child(begin, it - begin, end - begin);
    while (has_child(it - begin, end - begin) &&  *it < *lc ) {
        std::swap(*it,  *lc);
        it = lc;
        lc = largest_child(begin, it - begin, end - begin);
    }
}

template <typename RandomAccessIt>
void heap_sort(RandomAccessIt begin, RandomAccessIt end) {
    // Phase 1: build max heap
    RandomAccessIt boundary = begin;
    for ( ;boundary != end; ++boundary) {
        // Push new element to the end of the max heap.
        percolate_up(begin, boundary);
    }
    // Phase 2: remove elements 1 at a time from max heap and put it in the output
    for (RandomAccessIt boundary = end - 1; boundary != begin; --boundary) {
        // swap the top of the max heap with the next position of the output.
        std::swap(*begin, *boundary);
        // Percolate down the small element at *begin
        percolate_down(begin, boundary);
    }

}

const int NUMS = 8;
const int MIN = 100;

int main() {


//    vector<string> letters = { "Z", "Y", "X","W", "V","U", "T", "S", "R", "Q", "P", "O", "N","M", "L", "K","J", "I", "H","G", "F", "E", "D","C", "B", "A"};
//    vector<string> sorted = { "Z", "Y", "X","W", "V","U", "T", "S", "R", "Q", "P", "O", "N","M", "L", "K","J", "I", "H","G", "F", "E", "D","C", "B", "A",};
    vector<char> letters = {'m','o','k','h','a','l','a','d','a','l','j','u','b','o','o','r','i','j','a','s','i','m','h','a','m','m','o','d','i', ' ',  '1',  'I',  ':',  ' ',  'H',  ',',  'N'};
    vector<char> sorted = {'m','o','k','h','a','l','a','d','a','l','j','u','b','o','o','r','i','j','a','s','i','m','h','a','m','m','o','d','i', ' ',  '1',  'I',  ':',  ' ',  'H',  ',',  'N'};

//    for (int i = 0; i < NUMS; ++i) {
//        int rand_num = rand() % MIN;
//        letters.push_back(rand_num);
//        sorted.push_back(rand_num);
//    }

    cout << endl << "Given list" << endl;
    for(const auto ch : letters) {
        cout << ch << " ";
    } cout << endl;
    for(const auto ch : sorted) {
        cout << ch << " ";
    }

    cout << endl << endl <<"Heap Sorted: " << endl;
    heap_sort(letters.begin(), letters.end());
    for(const auto ch : letters) {
        cout << ch << " ";
    }
    cout << endl << endl << "Sorted List: " << endl;
    std::sort(sorted.begin(), sorted.end());
    for(const auto w : sorted) {
        cout << w << " ";
    }
    cout << endl << endl;

    int i = 0;
    while (letters[i] == sorted[i] && i < sorted.size()) {
        ++i;
    }
    if (i != sorted.size()) {
        cout << "Issue at Index: " << i << endl;
        cout << letters[i] << " != " << sorted[i] << endl;
    } else {
        cout << "All Good" << endl;
    }

}


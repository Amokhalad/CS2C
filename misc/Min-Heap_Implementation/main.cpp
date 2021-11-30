#include <iostream>
#include <vector>
#include <utility> // std::swap
using namespace std;


class MinHeap {
	vector<char> heap;
	static int parent_index(int i) {
		// Why is the text book just i / 2?
		return (i - 1) / 2;
	}
	static int left_index(int i) {
		return (2 * i) + 1;
	}
	static int right_index(int i) {
		return (2 * i) + 2;
	}
	bool has_children(int index) const {
		return has_left_child(index);
	}
	bool has_left_child(int index) const {
		return left_index(index) < heap.size();
	}
	bool has_right_child(int index) const {
		return right_index(index) < heap.size();
	}
	int smallest_child_index(int index) const noexcept {
		if (has_right_child(index)) {
			int l = left_index(index);
			int r = l + 1;
			return heap[l] < heap[r] ? l : r;
		} else { // if (has_left_child(index)
			return left_index(index);
		}
	}
public:
	void push(char c) {
		// Start by putting it at the end of the heap, and then perculate it up until it gets to the right spot.
		int i = heap.size();
		heap.push_back(c);
		int pi = parent_index(i);
		// Note: We don't have to check if i != 0 because parent_index(0) == 0, and heap[0] is never less than heap[parent_index(0)]
		while (heap[i] < heap[pi]) {
			std::swap(heap[i], heap[pi]);
			i = parent_index(i);
			pi = parent_index(i);
		}
		
	}
	void pop() {
		std::swap(heap.front(), heap.back());
		heap.pop_back();
		
		int i = 0;
		while (has_children(i) && heap[i] > heap[smallest_child_index(i)]) {
			std::swap(heap[i], heap[smallest_child_index(i)]);
			i = smallest_child_index(i);
		}
	}
	char top() const {
		return heap.front();
	}
	bool emoty() const {
		return heap.empty();
	}
};

int main() {
	MinHeap h;
	h.push('a');
	h.push('b');
	h.push('x');
	h.push('y');
	return 0;
}
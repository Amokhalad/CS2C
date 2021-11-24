#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

vector<string> merge(const vector<string> & left, const vector<string>& right) {
    vector<string> result;
    auto l_pos_it = left.begin();
    auto r_pos_it = right.begin();

    while(l_pos_it != left.end() && r_pos_it != right.begin()) {
        if(*l_pos_it < *r_pos_it) {
            result.push_back(*l_pos_it);
            ++l_pos_it;
        } else if (*l_pos_it > *r_pos_it) {
            result.push_back(*r_pos_it);
            ++r_pos_it;
        }
    }
    while (l_pos_it != left.end()) {
        result.push_back(*l_pos_it);
        ++l_pos_it;
    }
    while (r_pos_it != right.end()) {
        result.push_back(*r_pos_it);
        ++r_pos_it;
    }
    return result;
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;

}

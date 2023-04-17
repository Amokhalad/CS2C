/*
 * Spell Checking Bloom Filter, if it's a valid word, it will be a 0 in our bitsit.
 * */
#include <iostream>
#include <bitset>
#include <string>
#include <utility> // std::hash
#include <vector>
using namespace std;

template<size_t NUM_BITS>
class StringBloomFilter {
    bitset<NUM_BITS> bits; //1024 is 1 kb
public:
    void insert(const string& value);
    bool maybe_contains(const string& value);

};
template<size_t NUM_BITS>
void StringBloomFilter<NUM_BITS>::insert(const string &value) {
    size_t h = hash<string>{}(value) % bits.size();
    bits[h] = 1;
}
template<size_t NUM_BITS>
bool StringBloomFilter<NUM_BITS>::maybe_contains(const string &value) {
    size_t h = hash<string>{}(value) % bits.size();
    return bits[h];
    // TODO Question, you return bits[h] == 1, can you return bits[h] instead?
}

int main() {
    vector<string> fruits = {"apple", "banana", "coconuts", "durian", "guanabana"};
    vector<string> vegetables = {"broccoli", "cauliflower", "eggplant", "carrot", "cucumber"};
    StringBloomFilter<16> fruit_filter;
    vector<string> definitly_not_fruits;
    vector<string> maybe_fruits;

    for (const string& x : fruits) {
        cout << x << ": " << hash<string>{}(x) % 16 << endl;
    }
    cout << endl;
    for (const string& x : vegetables) {
        cout << x << ": "  << hash<string>{}(x) % 16 << endl;
    }
    /*for (const string& f : fruits) {
        fruit_filter.insert(f);
        if (fruit_filter.maybe_contains(f)) {
            maybe_fruits.push_back(f);
        } else {
            definitly_not_fruits.push_back(f);
        }
    }


    for (const string& x : vegetables) {
        if (fruit_filter.maybe_contains(x)) {
            maybe_fruits.push_back(x);
        } else {
            definitly_not_fruits.push_back(x);
        }
    }
    cout << "Definitly Not Fruits: " << endl;
    cout << "{ ";
    for (const auto &x : definitly_not_fruits) {
        cout << x << ", ";
    }
    cout << "} " << endl << endl;

    cout << "Maybe Fruits: " << endl;
    cout << "{ ";
    for (const auto &x : maybe_fruits) {
        cout << x << ", ";
    }
    cout << "} " << endl;*/

}

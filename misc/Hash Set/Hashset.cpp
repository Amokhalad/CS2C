#include <iostream>
#include <vector>  // std::vector
#include <string>
#include <set>     // std::set
#include <utility> // std::move
using namespace std;
/*
 * basic idea:
 * always give out some new number some new data
 * for convinence it's unsigned, by what is that convinent?
 *
 * return the first character of the name is not good because there are many names that start with the same first letter*/

// I see you have this is unsigned int, and you say in the video it's because it's convienet. But why is it convienent?
// does hash<string>{}(name) this return an unsigned int?
//
unsigned int hash_function(const string& name) {
    return hash<string>{}(name);
}
// We assume no name is empty! (in other words, "" is not a valid name)
class NamesHashSet{
    vector< set<string> > names;
    // a bad max_load_factor here, we just used one to show the rehashing
    static constexpr double MAX_LOAD_FACTOR = 1;
    int size_;
public:
    /*if we use the resize method: names.resize(const), it will not really improve the big o because it's improving it by a constant
     * we want our number of buckets to scale with the number of items inserted.
     * any time I get above the load factor, I want to resize*/
    NamesHashSet() : size_(0) {
        names.resize(1);
    }

    bool contains(const string& name) {
        set<string>& subset = names[hash_function(name) % names.size()];
        return subset.find(name) != subset.end();
    }

    bool insert(const string& name) {
        ++size_;
        if (size_ > names.size() * MAX_LOAD_FACTOR) {
            // just randomly desided to increase the size by two, this is not necessary.
            rehash(2 * names.size());
        }
        return names[hash_function(name) % names.size()].insert(name).second;
    }
    /*
    */
    void rehash(int new_num_buckets) {
        vector< set<string> > new_names;
        new_names.resize(new_num_buckets);
        for (const set<string>& bucket : names) {
            for (const string& name : bucket) {
                new_names[hash_function(name) % new_names.size()].insert(name);
            }
        }
        names = std::move(new_names);
    }
    void print() {
        cout << "(" << endl;
        for (const auto& bucket : names) {
            cout << " [ ";
            for (const string& name : bucket) {
                cout << name << ", ";
            }
            cout << " ] " << endl;
        }
        cout << ")" << endl;
    }
};



int main() {
    NamesHashSet names;
    vector<string> in_list = {"Alice", "Brock", "Mikel", "Maya", "Nana"};

    for (const auto &x : in_list) {
        cout << "Inserting " << x << " with hash " << hash_function(x) << ":" << endl;
        cout << "name.insert(" << x << ") " << (names.insert(x) ? "inserted" : "not inserted") << endl;
        names.print();
    }
    cout << endl;
    for (const auto &x : in_list) {
        cout << "name.contains(" << x << ") " << (names.contains(x) ? "found" : "not found") << endl;
    }
    cout << endl;

    for (const auto &x : {"Not a name"})  {
        cout << "name.contains(" << x << ") " << (names.contains(x) ? "found" : "not found") << endl;
    }

}
#include <iostream>
#include <vector>
#include <cstddef>
#include <utility> // std::hash
#include <string>
#include <exception>

using namespace std;

unsigned int hash_function(char letter) {
    return hash<char>{}(letter);
}

template<typename Key, typename Value>
class ProbingHashTable {
    static constexpr double max_load_factor = 0.5;
    struct Bucket {
        Key key_;
        Value value_;
        bool empty;
        Bucket() : empty(true) {};
    };

    vector<Bucket> buckets;
    int size_;
    static bool _insert(const Key& key, const Value& value, vector<Bucket>* buckets) {
        size_t bucket_index = hash<Key>{}(key) % buckets->size();
        while (!(*buckets)[bucket_index].empty) {
            // to wrap around, we mode it by buckets.size()
            bucket_index = (bucket_index + 1) % buckets->size();
            if ((*buckets)[bucket_index].key_ == key) {
                return false;
            }
        }
        (*buckets)[bucket_indaex].key_ = key;
        (*buckets)[bucket_index].value_ = value;
        (*buckets)[bucket_index].empty = false;
        return true;
    }

public:
    ProbingHashTable() : buckets(10), size_(0) { }
    bool insert(const Key& key, const Value& value) {
        if (load_factor() >= max_load_factor) {
            rehash(buckets.size() * 2);
        }
        bool inserted = _insert(key, value, &buckets);
        if (inserted) {
            size_++;
        }
        return inserted;
    }

    bool contains(const Key& key) const {
        size_t hashed_index = hash<Key>{}(key) % buckets.size();

        while (!buckets[hashed_index].empty) {
            if (buckets[hashed_index].key_ == key) {
                return true;
            }
            hashed_index = (hashed_index + 1) % buckets.size();
        }
        return false;
    }
    void rehash(int new_num_buckets) {
        vector<Bucket> new_buckets(new_num_buckets);
        size_t hashed_index;
        for (const Bucket& bucket : buckets) {
            _insert(bucket.key_, bucket.value_, &new_buckets);
        }
        buckets = std::move(new_buckets);
    }
    const Value& get(const Key& key) const {
        size_t hashed_index = hash<Key>{}(key) % buckets.size();
        while (!buckets[hashed_index].empty) {
            if (buckets[hashed_index].key_ == key) {
                return true;
            }
            hashed_index = (hashed_index + 1) % buckets.size();
        }
        throw invalid_argument("Trying to get with a bad key.");
    }
    double load_factor() const {
        return static_cast<double>(size()) / buckets.size();
    }

    int size() const {
        return size_;
    }
    void print() {
        cout << "{";
        for (const auto & bucket : buckets) {
            (bucket.empty) ? cout << "_" : cout << bucket.key_;
            cout << ", ";

        }
        cout << "}" << endl;
    }
};


int main() {
    ProbingHashTable<string, int> table;
    for (int i = 0; i < 20; ++i) {
        string key = to_string(i);
        cout << "table.contains(" << key << ") == " << table.contains(key) << endl;
        table.insert(to_string(i), i*i);
        cout << "table.contains(" << key << ") == " << table.contains(key) << endl;
    }
}
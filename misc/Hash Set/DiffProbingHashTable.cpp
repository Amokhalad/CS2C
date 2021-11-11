#include <iostream>
#include <vector>
#include <cstddef>
#include <utility> // std::hash
#include <string>
#include <exception>

using namespace std;

template<typename Key, typename Value>
class ProbingHashTable {
    static constexpr double max_load_factor = 0.75;
    // TODO: add more primes to bucket_sizes[] to  avoid array out of bounds
    static constexpr size_t bucket_sizes[] = {2, 3, 7, 23, 41, 83, 163};
    struct Bucket {
        Key key_;
        Value value_;
        bool empty;
        Bucket() : empty(true) {};
    };

    vector<Bucket> buckets;
    int size_;
    int bucket_size_index;
    static bool _insert(const Key& key, const Value& value, vector<Bucket>* buckets) {

        const size_t h = hash<Key>{}(key);
        size_t i = 0;
        size_t bucket_index = h % buckets->size();
        while (!(*buckets)[bucket_index].empty) {
            if ((*buckets)[bucket_index].key_ == key) {
                return false;
            }
            ++i;
            bucket_index = (h + prob_amount(key, i)) % buckets->size();
        }
        (*buckets)[bucket_index].key_ = key;
        (*buckets)[bucket_index].value_ = value;
        (*buckets)[bucket_index].empty = false;
        return true;
    }

    static size_t prob_amount(const Key& k, const int i) {
        return i * i;
    }

public:
    ProbingHashTable() : buckets(1), size_(0), bucket_size_index(0) { }
    bool insert(const Key& key, const Value& value) {
        if (load_factor() >= max_load_factor) {
            rehash(bucket_sizes[bucket_size_index]);
        }
        bool inserted = _insert(key, value, &buckets);
        if (inserted) {
            size_++;
        }
        return inserted;
    }

    bool contains(const Key& key) const {
        const size_t h = hash<Key>{}(key);
        size_t i = 0;
        size_t bucket_index = h % buckets.size();
        while (!buckets[bucket_index].empty) {
            if (buckets[bucket_index].key_ == key) {
                return true;
            }
            ++i;
            bucket_index = (h + prob_amount(key, i)) % buckets.size();
        }
        return false;
    }
    void rehash(int new_num_buckets) {
        vector<Bucket> new_buckets(new_num_buckets);
        for (const Bucket& bucket : buckets) {
            ++bucket_size_index;
            _insert(bucket.key_, bucket.value_, &new_buckets);
        }
        buckets = std::move(new_buckets);
    }
    const Value& get(const Key& key) const {
        const size_t h = hash<Key>{}(key);
        size_t i = 0;
        size_t bucket_index = h % buckets.size();
        while (!buckets[bucket_index].empty) {
            if (buckets[bucket_index].key_ == key) {
                return buckets[bucket_index].value_;
            }
            ++i;
            bucket_index = (h + prob_amount(key, i)) % buckets.size();
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
        table.insert(to_string(i), i*i);
        table.print();
    }
}
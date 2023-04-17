# Simple Linear Probing

- Every bucket can only contain 1 or 0 items in there.

```Buckets: |___|___|____|___|____|...```
```cpp
/*
 * need to know when the bucket is empty or not.*/
struct Bucket {
    Key key;
    bool empty;
};
```
```
to hash a value, you use hash and mod it by the number of buckets.

Buckets:
|___|___|___|

hash('a') % 3 == 1
|___|_a_|___|

hash('b') % 3 == 1
    - spot is not empty, so we can just place it in the next place that is empty.
|___|_a_|_b_|

what if I have something that's not in my hash set and I want to search for it
hash('c') % 3 == 1
|_c_|_a_|_b_|
    - we got to the next spot, but the next spot is taken, so we can wrap back around to the beginning
    - we also know that c is not in our hash table because if was it would have been inserted somewhere
     before I got to an empty spot
```

- I don't want my hash table to be super full because if I insert something that happens to hash inside that clump, 
I would have to search the entire clump to find an empty spot which is not good.
- I want my hash table to have some amounts of empty spots in it.
  - To do this, we introduce a load_factor which is the number of of elements in hash table divided by number of buckets:
    - `load_factor = num_items/num_buckets` 
      - and then resize our hash table.

```
Rehashing:
|___|_a_|_b_|
|___|_b_|___|_a_|___|___|
    - a now rehashes to a different value instead of one, while b hashes to 1 in this case.
```

## Linear Probing
```
hash('a') % 10 == 2
hash('b') % 10 == 1
hash('c') % 10 == 1
  - index 1 has b in it, so we contiue down the list until there is an empty space.
|___|_b_|_a_|_c_|___|___| ... |___| [10]
```
### Finding Values in our table
 - if we want to find a, we just hash it, get the index and check if the table at that index is a.
 - if we want to find c, I hash it I see that it's suppose to be in bucket 1, but there is something else at index 1, so I check
the next bucket until I find c.
 - if I want to find a char that's not in our list, like d, suppose it hashes to 1.
I check the index at 1 to see if d is there, it's not so I continue down the list until I get to an empty list. If I get an empty list
then I know it's not in our list.

## Other types of probing

```
list = {a, b, c}
hash(a) = 1
hash(b) = 1
hash(c) = 2

|___|_a_|_b_|_c_|___|___| ...  |___|
  - continues down the buckets until it finds an empty list.
```

### Probing by a different constant
h(k) + ic where c is some constant can have issues. For example imagine c = 3, and you have a list of 3 items,
you will be in an infinite loop, checking the same bucket each time.
  - as long as c is co prime with the number of buckets, it's okay
    - co prime means they don't share any common factors 

```
list {0, 1, 2, 3}

h(k) + ic
 -  the bad c values for the list above are
  - 0, wont go anywhere
  - 4, will check the same bucket everytime
  - 2, will be in a infinite loop since 2 is a factor of 4.
```

### Quadratic Probing
$h(k) + i^2c_0 + ic_1$
in general:
    $h(k) + f(i)$, where f(i) is some quadratic function
- this method of probing prevents "clumps of data"
  - notice below, c is not clumped with a and b.
```
    hash(a) + i^2
hash(a) = 1   ->  1 + 0^2 = 1
hash(b) = 1   ->  1 + 1^2 = 2
hash(c) = 1   ->  1 + 2^2 = 5

|___|_a_|_b_|___|___|_c_|___| ... |___|
```

### Double Hashing
    - linear probing, but the amount you jump will be different depending on the que   
    - this method is good for reducing clumps.
$h(k) + ih_2(k)$

## Bloom Filters
### `std::bitset`
- kind of like a vector of bool
```
- bits are very cheap
say we want to prevent someone from going to websites, the idea: we hash the website and mod it by the bitset size and
we set the bitset at that index to 1, or true.
bitset:
|_0_|_0_|_0_|_0_|_0_|
    - by default they are 0.
    - hash(google.com) => 2, so we override bitset[2] to 1.
|_0_|_0_|_1_|_0_|_0_|

    - now say you want to check if a website is in the nogo zone. We hash that website, and check if the index at that
    at that location is a 0 or 1.
        - if it's a 0, then the website is definitly not in our no go zone
        - if it's a 1, then it's a maybe, maybe not. You don't know. So to check forsure, we have another data structure
        that does the more expensive search. 
```
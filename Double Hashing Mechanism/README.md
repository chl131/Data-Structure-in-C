# Double Hashing Mechanism

## Description
This program implements a double hash mechanism. Its hash function is (hash1(key) + i * hash2(key)) % TABLE_SIZE, in which hash1() and hash2() are two individual hash functions defined as follows.

- hash1(key) = key % TABLE_SIZE
- hash2(key) = PRIME – (key % PRIME)

TABLE_SIZE is the size of hash table which in this program is 13. In others word, each row of the hash table (i.e., each bucket) has a room for only one key. PRIME is a prime number smaller than TABLE_SIZE which in this program is 7.<br>

The program will hash the input keys into the hash table according to the order of the keys in the INPUT. In the beginning, i is set to 0. When a collision occurs during hashing a key, recalculate its hash value by i = i+1. If collision still occurs, then recalculate its hash value again by setting i = i+1. Repeat this process until no collision occurs (i.e., an empty bucket is found), and then put the key in that bucket. Then, continue to hash the next key. When hashing the next key, i is reset to 0 and the same hash process repeats for this new key. The hashing process will repeat until all keys in the INPUT are hashed into the hash table.

## Input - standard input
The INPUT will contain one and exactly only one row of keys separated with a space.
```
24 10 31 56 45 85 64 8 77 37 2 98 70
```

## Output - standard output
The hash table will be printed on the command line after the hashing process.
```
0->77
1->98
2->2
3->37
4->56
5->31
6->45
7->85
8->8
9->70
10->10
11->24
12->64
```
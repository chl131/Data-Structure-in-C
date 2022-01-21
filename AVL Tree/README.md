# AVL Tree Implementation

## Description
This program implements an AVL search tree for fast searching. In an AVL tree, the heights of the two child subtrees of any node differ by at most one; if at any time they differ by more than one, rebalancing is done to restore this property. Lookup, insertion, and deletion all take O(log n) time in both the average and worst cases, where n is the number of nodes in the tree prior to the operation. Insertions and deletions may require the tree to be rebalanced by one or more tree rotations.

## Input - standard input
The input will contain two parts, each part starting with one letter. The first part of the input, starting with “D”, is the data used to construct the AVL search tree. There will be N records in the data, and each record will contain a name and a phone number. Each node of the AVL tree will contain only one record. Hence, each node will contain only one name and one phone number. The insertion order will be the same as the order of names given in INPUT.<br>

The second part of the input, starting with “S”, is a series of searching requests. A letter “E” will be given at the end of the INPUT to indicate that it is the end of the INPUT. The input contains following sections of data:

- “D” indicates the start of a number of “ name” and “phone number” pairs which are separated by a “Blank”. Each such pair is ended by an “Enter”.
- “S” indicates the start of a number of searches, which are some given names separated by an “Enter”.
- “E” stands for “End of Input”.

```
D
Bob 0900000000
Alice 0900000001
Paul 0900000002
David 0900000003
Ruby 0900000004
Charlie 0900000005
S
Paul
Amy
Ruby
E
```

## Output - standard output
After the AVL search tree is constructed, it will be printed out on the command line in Pre-Order followed by the results of the searching requests. If a given search name does not exist in the tree, then a “null” string will be printed in the phone number field.

```
David Bob Alice Charlie Paul Ruby
Paul 0900000002
Amy null
Ruby 0900000004
```
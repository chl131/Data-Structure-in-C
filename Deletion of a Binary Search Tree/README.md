# Deletion of a Binary Search Tree

## Description
This program will build a binary search tree and delete nodes from the tree. After the deletion, it will print out the remaining nodes of the binary search tree in ```Level Order```.

## Input - standard input
Input the data with two lines. The numbers in the first line represent the keys that form a binary search tree. The binary search tree will be built according to the order of the keys given in the first line (from left to right). All the keys in the input will be between 1 and 100 (i.e., 1≤key≤100), and there will be no duplicate keys.<br><br>
The second line of the input gives the keys that are going to be deleted from the tree. The program will delete the keys in the binary search tree according to the order in the second line (from left to right). If a deleted key, say X, has two child nodes, then X will be replaced by the node having the smallest key value in X’s right subtree.
```
1 3 5 7 2 4
5 7
```

## Output - standard output
The remaining nodes (i.e., keys) of the binary search tree will be printed on the command line in Level Order after the deletion.
```
1
3
2
4
```
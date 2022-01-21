# Critical Paths of AOE Network

## Description
<p>This program will find all critical paths from a given AOE network. A critical path is determined by identifying the longest stretch of dependent activities and measuring the time required to complete them from start to finish.</p>

![](https://i.imgur.com/VtIlGm1.png)

## Input - standard input
The input which describes an AOE network, has the following data. The first line of the input contains an integer N (0 < N < 100), which indicates the number of activities (i.e., edges) of the network. The succeeding N lines of the input file are the information of the network activities (i.e., edges). Each of these N lines consists of four integers. They are respectively the activity ai, the starting vertex vj of ai, the ending vertex vk of ai , and the weight w of this activity, in which i, j, k, and w are all integers and 0 ≤ i, j, k, w < 100. Notice that i, j, k, and w in the input will be separated by ONE empty space. For example, the 5th line of the input is “3 1 4 1”, which means that the activity a3’s starting vertex is v1, its ending vertex is v4, and its weight is 1.

```
11
0 0 1 6
1 0 2 4
2 0 3 5
3 1 4 1
4 2 4 1
5 3 5 2
6 4 6 9
7 4 7 7
8 5 7 4
9 6 8 2
10 7 8 4
```

## Output - standard output
The output consists of two parts:

- Activity early-late time: The first part gives each activity’s index i, the earliest time e(i), and the latest time l(i), each separated by an empty space. For example, the 9th line of the output, which is 8 7 10, means that the activity a8’s earlies time is 7 and the latest time is 10. The activities will be printed in ASCENDING ORDER of the activity index.

- Critical paths: The activity indices of all the critical paths will be printed in the last line. The activity indices in this line will be printed in ASCENDING ORDER and each separated by ONE empty space. In this particular example (referring to the graph above), the critical paths contain activities a0, a3, a7, a6, a10, a9. Hence, the printout shown in the output (referring to the last line) is 0 3 6 7 9 10 (which indicate the critical activities a0, a3, a6, a7, a9, a10, respectively)

```
0 0 0
1 0 2
2 0 3
3 6 6
4 4 6
5 5 8
6 7 7
7 7 7
8 7 10
9 16 16
10 14 14
0 3 6 7 9 10
```

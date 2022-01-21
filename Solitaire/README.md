# Solitaire

## Description
There is a pile of cards from ```K,Q,J,10,9,8,7,6,5,4,3,2,A``` in random order and without repetition. The goal is to draw the card out follow the sequence from K to A. Note that you can only draw a card out from the top of the pile. If the card on the top of the pile is not the one to draw out, put it to the bottom of the pile. Stop until all the cards have been drawn out.

## Input - standard input
Input a pile of card in random order and without repetition. Each input of a card should be separated by EOL<br>
```
K
3
5
9
A
10
2
8
4
Q
6
7
J
```

## Output - standard output
The state of the pile each time a card is drawn out or put to the bottom of the pile will be printed on the command line.
```
K 3 5 9 A 10 2 8 4 Q 6 7 J (K will be drawn out)
3 5 9 A 10 2 8 4 Q 6 7 J
5 9 A 10 2 8 4 Q 6 7 J 3
9 A 10 2 8 4 Q 6 7 J 3 5
A 10 2 8 4 Q 6 7 J 3 5 9
10 2 8 4 Q 6 7 J 3 5 9 A
2 8 4 Q 6 7 J 3 5 9 A 10
8 4 Q 6 7 J 3 5 9 A 10 2
4 Q 6 7 J 3 5 9 A 10 2 8
Q 6 7 J 3 5 9 A 10 2 8 4   (Q will be drawn out)
6 7 J 3 5 9 A 10 2 8 4
…
…
2 A                        (2 will be drawn out)
A                          (A will be drawn out)
```
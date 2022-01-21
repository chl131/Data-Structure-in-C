# Queueing in Cafeteria

## Description
This cafeteria offers American and Mexican food. If a customer wants to get any food, he/she has to first pick up a plate and get in the line. Each plate is indexed by a random number. The staffs of the cafeteria refill the plate stack occasionally.<br><br>
There is a line for the American food and a line for the Mexican food in the cafeteria. A customer can choose a line and joins at the end of it. After finishing ordering, he/she will leave the line from the front to check out.

## Input - standard input
```PUSH N``` : indicates the staff refills a plate index N into the plate stack.<br>
```POP``` : indicates the customer takes a plate from the top of the plate stake.<br>
```ENQUEUE X``` : indicates a customer joins the end of the line X.<br>
```DEQUEUE X``` : indicates a customer at the front of the line X leaves the line to checkout.<br>
Input stops when EOF (ctrl+z on windows) is read.

```
PUSH 30
PUSH 98
PUSH 54
POP
ENQUEUE A
POP
ENQUEUE B
PUSH 1
PUSH 3
POP
ENQUEUE A
DEQUEUE A
DEQUEUE B
POP
ENQUEUE B
POP
ENQUEUE B
DEQUEUE A
DEQUEUE B
DEQUEUE B
```

## Output - standard output
The plate index of the customer who left after each DEQUEUE operation will be printed separately in the commend line.

```
54
98
3
1
30
```
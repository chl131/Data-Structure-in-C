#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node{
    int index;
    struct _node* next;
    struct _node* previous;
}node;

int main()
{
    node* stack_bot = NULL;
    node* stack_top = NULL;
    node* pop = NULL;
    node* Queue_A_front = NULL;
    node* Queue_A_end = NULL;
    node* Queue_B_front = NULL;
    node* Queue_B_end = NULL;
    FILE* fPointer;
    int index_plate = -1;
    char action[20];
    char student[10];
    int i = 0;

    /*Read the input file until the end*/
    while(scanf("%s", action) != EOF){

        if(i>0 && strcmp(action, "DEQUEUE")==0)printf("\n");

        /*end of file*/
        if (strcmp(action, "EOF(^Z)")==0 || strcmp(action, "EOF (^Z)")==0 || strcmp(action, "EOF")==0){
            break;
        }
        if (strcmp(action, "^Z(EOF)")==0 || strcmp(action, "^Z (EOF)")==0 || strcmp(action, "^Z")==0){
            break;
        }

        /*PUSH*/
        else if(strcmp(action, "PUSH")==0){
            scanf("%d", &index_plate);
            node* new_stack = malloc(sizeof(node));
            new_stack->index = index_plate;

            /*Initial PUSH*/
            if(stack_bot==NULL && stack_top==NULL){
                stack_bot = new_stack;
                stack_top = new_stack;
                stack_bot->next = NULL;
                stack_bot->previous = NULL;
                stack_top->next = NULL;
                stack_top->previous = NULL;
            }
            /*PUSHs after initial PUSH*/
            else{
                new_stack->previous = stack_top;
                new_stack->next = NULL;
                stack_top->next = new_stack;
                stack_top = new_stack;
            }
        }

        /*POP*/
        else if (strcmp(action, "POP")==0){
            if(stack_top == NULL){
                if(i>0)printf("\n");
                printf("The stack is empty !");
                i += 1;
            }
            else{
            pop = stack_top;
            stack_top = stack_top->previous;
            pop->next = NULL;
            pop->previous = NULL;
            }
        }

        /*ENQUEUE or DEQUEUE*/
        else if (strcmp(action, "ENQUEUE")==0 || strcmp(action, "DEQUEUE")==0){
            scanf("%s", student);
            /*ENQUEUE*/
            if(strcmp(action, "ENQUEUE")==0){
                /*ENQUEUE A*/
                if(strcmp(student, "A")==0){
                    if(pop == NULL){
                        if(i>0)printf("\n");
                        printf("Please POP a plate first.");
                        i += 1;
                    }
                    else if(Queue_A_front==NULL && Queue_A_end==NULL){
                        Queue_A_end = pop;
                        Queue_A_front = pop;
                        pop = NULL;
                    }
                    else{
                        pop->previous = Queue_A_end;
                        Queue_A_end->next = pop;
                        Queue_A_end = pop;
                        Queue_A_end->next = NULL;
                        pop = NULL;
                    }
                }
                /*ENQUEUE B*/
                else if(strcmp(student, "B")==0){
                    if(pop == NULL){
                        if(i>0)printf("\n");
                        printf("Please POP a plate first.");
                        i += 1;
                    }
                    else if(Queue_B_front==NULL && Queue_B_end==NULL){
                        Queue_B_end = pop;
                        Queue_B_front = pop;
                        pop = NULL;
                    }
                    else{
                        pop->previous = Queue_B_end;
                        Queue_B_end->next = pop;
                        Queue_B_end = pop;
                        Queue_B_end->next = NULL;
                        pop = NULL;
                    }
                }
                else{
                    if(i>0)printf("\n");
                    printf("Invalid enqueue !");
                    i += 1;
                }
            }
            /*DEQUEUE*/
            else{
                /*DEQUEUE A*/
                if(strcmp(student, "A")==0){
                    if(Queue_A_front==NULL && Queue_A_end==NULL){
                        printf("Queue A is empty !");
                        i += 1;
                    }
                    else if(Queue_A_front->next != NULL){
                        printf("%i", Queue_A_front->index);
                        node* temp = Queue_A_front->next;
                        free(Queue_A_front);
                        Queue_A_front = temp;
                        Queue_A_front->previous = NULL;
                        i += 1;
                    }
                    else{
                        printf("%i", Queue_A_front->index);
                        Queue_A_front = NULL;
                        Queue_A_end = NULL;
                        i += 1;
                    }
                }
                /*DEQUEUE B*/
                else if(strcmp(student, "B")==0){
                    if(Queue_B_front==NULL && Queue_B_end==NULL){
                        printf("Queue B is empty !");
                        i += 1;
                    }
                    else if(Queue_B_front->next != NULL){
                        printf("%i", Queue_B_front->index);
                        node* temp = Queue_B_front->next;
                        free(Queue_B_front);
                        Queue_B_front = temp;
                        Queue_B_front->previous = NULL;
                        i += 1;
                    }
                    else{
                        printf("%i", Queue_B_front->index);
                        Queue_B_front = NULL;
                        Queue_B_end = NULL;
                        i += 1;
                    }
                }
                else{
                    if(i>0)printf("\n");
                    printf("Invalid enqueue !");
                    i += 1;
                }
            }
        }
        else{
            printf(" %s is not a valid operation !", action);
        }

    }
   return 0;
}

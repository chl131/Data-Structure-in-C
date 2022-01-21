#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare( const void* a, const void* b)
{
     int int_a = * ( (int*) a );
     int int_b = * ( (int*) b );

     if ( int_a == int_b ) return 0;
     else if ( int_a < int_b ) return -1;
     else return 1;
}

typedef struct _node{
    char index[5];
    int index_out;
    struct _node* next;
    struct _node* previous;
}node;

int main()
{
    node* card = NULL;
    node* Queue_card_top = NULL;
    node* Queue_card_end = NULL;
    int number_of_cards = 0;
    char values[] = "KQJ98765432A";
    char value[10];
    char* inputstr;
    int Out_index[20000];
    int i = 0;  /*number of input*/
    int j;

    /*Read the input file until the end*/
    while(scanf("%s", value) != EOF){

        /*Invalid input*/
        if(strcmp(value, "10")!=0 && strchr(values,*value)==NULL){
            printf("%s", value);
            printf("Invalid input !\n");
        }

        /*PUT {K,Q,J,10,9,8,7,6,5,4,3,2,A} into linked list*/
        else{
            node* new_card = malloc(sizeof(node));
            strcpy(new_card->index, value);

            /*Initial the list of cards*/
            if(Queue_card_top==NULL && Queue_card_end==NULL){
                /*Record the "real value" of the card and make a output index list*/
                if(strcmp(value, "10")==0){
                    Out_index[i] = 3;
                    new_card->index_out = 3;
                }
                else if(strchr(values,*value)-values>=3){
                    Out_index[i] = strchr(values,*value)-values+1;
                    new_card->index_out = strchr(values,*value)-values+1;
                }
                else{
                    Out_index[i] = strchr(values,*value)-values;
                    new_card->index_out = strchr(values,*value)-values;
                }
                Queue_card_top = new_card;
                Queue_card_end = new_card;
                Queue_card_top->next = NULL;
                Queue_card_top->previous = NULL;
                Queue_card_end->next = NULL;
                Queue_card_end->previous = NULL;
            }
            /*Put the cards in the list after initial*/
            else{
                /*Record the "real value" of the card and make a output index list*/
                if(strcmp(value, "10")==0){
                    Out_index[i] = 3;
                    new_card->index_out = 3;
                }
                else if(strchr(values,*value)-values>=3){
                    Out_index[i] = strchr(values,*value)-values+1;
                    new_card->index_out = strchr(values,*value)-values+1;
                }
                else{
                    Out_index[i] = strchr(values,*value)-values;
                    new_card->index_out = strchr(values,*value)-values;
                }
                new_card->previous = Queue_card_top;
                new_card->next = NULL;
                Queue_card_top->next = new_card;
                Queue_card_top = new_card;
            }
        }
        i = i+1;
    }

    qsort(Out_index, i, sizeof(int), compare);

    /*This is how to take out all the cards from end to top*/
    /*while(Queue_card_end!=NULL){
        printf("%s - ", Queue_card_end->index);
        printf("%i\n", Queue_card_end->index_out);
        if(Queue_card_end->next==NULL && Queue_card_end->previous==NULL){
            Queue_card_end = NULL;
        }
        else{
            node* temp = Queue_card_end->next;
            free(Queue_card_end);
            Queue_card_end = temp;
            Queue_card_end->previous = NULL;
        }
    }*/

    node* temp;
    for(j=0; j<i;){
        if(j==i-1){
            printf("%s", Queue_card_end->index);
            j += 1;
        }
        else if(Out_index[j]!=Queue_card_end->index_out){
            temp = Queue_card_end;
            while(temp->next!=NULL){
                printf("%s ", temp->index);
                temp = temp->next;
                }
            printf("%s\n", temp->index);
            /*If it not the time for the card to get out, put it on the top of the queue*/
            Queue_card_top->next = Queue_card_end;
            Queue_card_end->previous = Queue_card_top;
            Queue_card_end = Queue_card_end->next;
            Queue_card_top = Queue_card_top->next;
            Queue_card_end->previous = NULL;
            Queue_card_top->next = NULL;
        }
        else{
            temp = Queue_card_end;
            while(temp->next!=NULL){
                printf("%s ", temp->index);
                temp = temp->next;
                }
            printf("%s", temp->index);
            /*Take the card out*/
            temp = Queue_card_end;
            Queue_card_end = Queue_card_end->next;
            Queue_card_end->previous = NULL;
            free(temp);
            j += 1;
            if(j<i){
                printf("\n");
            }
        }
    }

   return 0;
}

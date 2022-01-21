#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* A AOE network node has data, pointer to left child
   and a pointer to right child */
typedef struct _node{
    int vertex;
    int weight;
    struct _node* link;
}Node;

typedef struct _stack{
    int index;
    struct _stack* next;
    struct _stack* previous;
}stack;

// Helper function that allocates a new node with the
// given data and NULL left and right pointers.
Node* newNode(int input_vertex, int input_weight){
    Node* node = (Node*)malloc(sizeof(Node));

    node->vertex = input_vertex;
    node->weight = input_weight;
    node->link = NULL;

    return(node);
}



// Start of main
int main()
{
    int i;
    int j;
    int number_of_links = 0;
    int number_of_nodes = 0;
    int last_node = 0;
    int first_node = 100;

    // Start of loading inputs
    // Create a matrix that represent the inputs
    scanf("%d", &number_of_links);
    int input_matrix[number_of_links][4];

    for(i=0; i<number_of_links; i++){
        for(j=0; j<4; j++){
            scanf("%d", &input_matrix[i][j]);
        }
    }
    // End of loading inputs

    // Find the first and last node
    for(i=0; i<number_of_links; i++){
        for(j=1; j<3; j++){
            if(input_matrix[i][j] < first_node) first_node=input_matrix[i][j];
            if(input_matrix[i][j] > last_node) last_node=input_matrix[i][j];
        }
    }

    // Calculate the number of nodes
    number_of_nodes = last_node-first_node+1;

    // Create count array for early
    int count_arr_early[number_of_nodes];

    for(i=0; i<number_of_nodes; i++){
        count_arr_early[i] = 0;
    }

    for(i=0; i<number_of_links; i++){
        for(j=2; j<3; j++){
            count_arr_early[input_matrix[i][j]] += 1;
        }
    }

    // Create count array for late
    int count_arr_late[number_of_nodes];
    int count_arr_late_new[number_of_nodes];

    for(i=0; i<number_of_nodes; i++){
        count_arr_late[i] = 0;
    }

    for(i=0; i<number_of_links; i++){
        for(j=1; j<2; j++){
            count_arr_late[input_matrix[i][j]] += 1;
        }
    }

    /*for(i=0; i<number_of_nodes; i++){
        count_arr_late_new[i] = count_arr_late[i];
    }*/

    // Create matrix for counting the early
    // ( the matrix for counting the late will be create after filling the early_matrix )
    int early_matrix[number_of_nodes][number_of_nodes];
    for(j=0; j<number_of_nodes; j++){
        early_matrix[0][j] = 0;
    }

    // Create early linked list
    Node *early_list[number_of_nodes];
    for(i=0; i<number_of_nodes; i++){
        early_list[i] = NULL;
    }

    for(i=0; i<number_of_links; i++){
        int from_vertex;
        int temp_vertex;
        int temp_weight;
        from_vertex = input_matrix[i][1];
        temp_vertex = input_matrix[i][2];
        temp_weight = input_matrix[i][3];
        if(early_list[from_vertex] == NULL){
            early_list[from_vertex] = newNode(temp_vertex, temp_weight);
        }
        else{
            Node* temp_last_node = early_list[from_vertex];
            while(temp_last_node->link != NULL){
                temp_last_node = temp_last_node->link;
            }
            Node* temp_new_node = newNode(temp_vertex, temp_weight);
            temp_last_node->link = temp_new_node;
        }
    }// Note that the last position (pointer) of early list is NULL.

    // Create late linked list
    Node *late_list[number_of_nodes];
    for(i=0; i<number_of_nodes; i++){
        late_list[i] = NULL;
    }

    for(i=0; i<number_of_links; i++){
        int from_vertex;
        int temp_vertex;
        int temp_weight;
        from_vertex = input_matrix[i][2];
        temp_vertex = input_matrix[i][1];
        temp_weight = input_matrix[i][3];
        if(late_list[from_vertex] == NULL){
            late_list[from_vertex] = newNode(temp_vertex, temp_weight);
        }
        else{
            Node* temp_last_node = late_list[from_vertex];
            while(temp_last_node->link != NULL){
                temp_last_node = temp_last_node->link;
            }
            Node* temp_new_node = newNode(temp_vertex, temp_weight);
            temp_last_node->link = temp_new_node;
        }
    }// Note that the first position (pointer) of early list is NULL.


    // =========================
    // Complete the early matrix
    int early_matrix_row = 0;
    stack* early_stack_top = NULL;
    stack* early_stack_bot = NULL;
    stack* new_early_stack = malloc(sizeof(stack));
    new_early_stack->index = first_node;
    new_early_stack->next = NULL;
    new_early_stack->previous = NULL;
    early_stack_top = new_early_stack;
    early_stack_bot = new_early_stack;


    while(early_stack_top != early_stack_bot || early_matrix_row == 0){
        early_matrix_row += 1;
        for(i=0; i<number_of_nodes; i++){
            early_matrix[early_matrix_row][i] = early_matrix[early_matrix_row-1][i];
        }

        int push_number;
        int pop_number = early_stack_top->index;

        if(early_stack_top != early_stack_bot){
            early_stack_top = early_stack_top->previous;
        }

        Node* temp_node = early_list[pop_number];
        while(temp_node != NULL && pop_number != last_node){
            push_number = temp_node->vertex;
            count_arr_early[push_number] -= 1;

            int temp_check_max;
            temp_check_max = early_matrix[early_matrix_row-1][pop_number] + temp_node->weight;
            if(temp_check_max > early_matrix[early_matrix_row][push_number]){
                early_matrix[early_matrix_row][push_number] = early_matrix[early_matrix_row-1][pop_number] + temp_node->weight;
            }

            if(count_arr_early[push_number] <= 0){
                stack* push_stack = malloc(sizeof(stack));
                push_stack->index = push_number;
                push_stack->previous = early_stack_top;
                push_stack->next = NULL;
                early_stack_top->next = push_stack;
                early_stack_top = early_stack_top->next;
            }
            temp_node = temp_node->link;
        }
    }
    // End of completing the early matrix
    // ==================================

    // Create matrix for counting the late
    int temp_int = early_matrix[number_of_nodes-1][number_of_nodes-1];
    int late_matrix[number_of_nodes][number_of_nodes];
    for(j=0; j<number_of_nodes; j++){
        late_matrix[0][j] = temp_int;
    }

    // ========================
    // Complete the late matrix
    int late_matrix_row = 0;
    stack* late_stack_top = NULL;
    stack* late_stack_bot = NULL;
    stack* new_late_stack = malloc(sizeof(stack));
    new_late_stack->index = last_node;
    new_late_stack->next = NULL;
    new_late_stack->previous = NULL;
    late_stack_top = new_late_stack;
    late_stack_bot = new_late_stack;

    while(late_stack_top != late_stack_bot || late_matrix_row == 0){
        late_matrix_row += 1;
        for(i=0; i<number_of_nodes; i++){
            late_matrix[late_matrix_row][i] = late_matrix[late_matrix_row-1][i];
        }

        int push_number;
        int pop_number = late_stack_top->index;

        if(late_stack_top != late_stack_bot){
            late_stack_top = late_stack_top->previous;
        }

        Node* temp_node = late_list[pop_number];
        while(temp_node != NULL && pop_number != first_node){
            push_number = temp_node->vertex;
            count_arr_late[push_number] -= 1;

            int temp_check_min;
            temp_check_min = late_matrix[late_matrix_row-1][pop_number] - temp_node->weight;
            if(temp_check_min < late_matrix[late_matrix_row][push_number]){
                late_matrix[late_matrix_row][push_number] = late_matrix[late_matrix_row-1][pop_number] - temp_node->weight;
            }

            if(count_arr_late[push_number] <= 0){
                stack* push_stack = malloc(sizeof(stack));
                push_stack->index = push_number;
                push_stack->previous = late_stack_top;
                push_stack->next = NULL;
                late_stack_top->next = push_stack;
                late_stack_top = late_stack_top->next;
            }
            temp_node = temp_node->link;
        }
    }
    // End of completing the late matrix
    // =================================


    // Outputs
    int output_matrix[number_of_links][3];

    for(i=0; i<number_of_links; i++){
        output_matrix[i][0] = i;
        output_matrix[i][1] = early_matrix[number_of_nodes-1][input_matrix[i][1]];
        output_matrix[i][2] = late_matrix[number_of_nodes-1][input_matrix[i][2]] - input_matrix[i][3];
    }


    /*
    for(i=0; i<number_of_nodes; i++){
        printf("%d ", early_matrix[number_of_nodes-1][i]);
    }

    printf("\n");
    for(i=0; i<number_of_nodes; i++){
        printf("%d ", late_matrix[number_of_nodes-1][i]);
    }*/

    for(i=0; i<number_of_links; i++){
        printf("%d", output_matrix[i][0]);
        for(j=1; j<3; j++){
            printf(" %d", output_matrix[i][j]);
        }
        printf("\n");
    }

    int check_space = 0;

    for(i=0; i<number_of_links; i++){
        if(output_matrix[i][1] == output_matrix[i][2]){
            if(check_space == 0){
                check_space = 1;
                printf("%d", output_matrix[i][0]);
            }
            else{
                printf(" %d", output_matrix[i][0]);
            }
        }
    }


    return 0;
}

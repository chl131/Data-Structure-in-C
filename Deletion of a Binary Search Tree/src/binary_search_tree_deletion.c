#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _node{
    int node_value;
    struct _node* parent;
    struct _node* left;
    struct _node* right;
}node;


int main()
{
    int value;
    int i = 0; /*number of outputs*/
    int j;
    int num_of_input = 0; /*number of inputs*/
    int num_of_delete = 0;
    int inputs[200];
    int outputs[200];
    int* puts;
    int num;
    node* BST[200];

    /*Make a binary tree from first line of input*/
    puts = inputs;
    while(scanf("%d", &value) != EOF){
        puts[i] = value;
        i++;

        if(getchar() == '\n'){
            puts = outputs;
            num_of_input = i;
            i = 0;
        }
    }
    num_of_delete = i;
    i = 0;

    node* root = malloc(sizeof(node));
    root->node_value = inputs[0];
    root->left = NULL;
    root->right = NULL;
    root->parent = NULL;

    /*Create a BST*/
    for(j=1; j<num_of_input; j++){
        node* new_node = malloc(sizeof(node));
        node* temp_node = root;
        num = inputs[j];
        new_node->node_value = num;
        new_node->left = NULL;
        new_node->right = NULL;
        new_node->parent = NULL;
        while(new_node->parent == NULL){
            if(num > temp_node->node_value){
                if(temp_node->right == NULL){
                    new_node->parent = temp_node;
                    temp_node->right = new_node;
                }
                else{
                    temp_node = temp_node->right;
                }
            }
            else{
                if(temp_node->left == NULL){
                    new_node->parent = temp_node;
                    temp_node->left = new_node;
                }
                else{
                    temp_node = temp_node->left;
                }
            }
        }
    }
    /*End of create a BST*/


    /*Delete node*/
    for(i=0; i<num_of_delete; i++){
        node* delete_node = root;
        int delete_num = outputs[i];

        /*find the delete node*/
        while(delete_node->node_value != delete_num){
            if(delete_num > delete_node->node_value){
                delete_node = delete_node->right;
            }
            if(delete_num < delete_node->node_value){
                delete_node = delete_node->left;
            }
        }

        /*delete a node that is not the root*/
        if(delete_node->node_value != root->node_value){
            node* delete_node_parent = delete_node->parent;
            node* delete_node_right = delete_node->right;
            node* delete_node_left = delete_node->left;
            node* replace_node = NULL;
            node* replace_node_parent = NULL;
            /*case 1*/
            if(delete_node_left == NULL && delete_node_right == NULL){
                if(delete_node_parent->left == NULL){
                    delete_node_parent->right = NULL;
                }
                else if(delete_node_parent->right == NULL){
                    delete_node_parent->left = NULL;
                }
                else{
                    if(delete_node_parent->left->node_value == delete_num){
                        delete_node_parent->left = NULL;
                    }
                    else{
                        delete_node_parent->right = NULL;
                    }
                }
                delete_node = NULL;
            }
            /*case 2-1*/
            else if(delete_node_left != NULL && delete_node_right == NULL){
                if(delete_node_parent->left == NULL){
                    delete_node_parent->right = delete_node_left;
                    delete_node_left->parent = delete_node_parent;
                }
                else if(delete_node_parent->right == NULL){
                    delete_node_parent->left = delete_node_left;
                    delete_node_left->parent = delete_node_parent;
                }
                else{
                    if(delete_node_parent->left->node_value == delete_num){
                        delete_node_parent->left = delete_node_left;
                        delete_node_left->parent = delete_node_parent;
                    }
                    else{
                        delete_node_parent->right = delete_node_left;
                        delete_node_left->parent = delete_node_parent;
                    }
                }
            }
            /*case 2-2*/
            else if(delete_node_left == NULL && delete_node_right != NULL){
                if(delete_node_parent->left == NULL){
                    delete_node_parent->right = delete_node_right;
                    delete_node_right->parent = delete_node_parent;
                }
                else if(delete_node_parent->right == NULL){
                    delete_node_parent->left = delete_node_right;
                    delete_node_right->parent = delete_node_parent;
                }
                else{
                    if(delete_node_parent->left->node_value == delete_num){
                        delete_node_parent->left = delete_node_right;
                        delete_node_right->parent = delete_node_parent;
                    }
                    else{
                        delete_node_parent->right = delete_node_right;
                        delete_node_right->parent = delete_node_parent;
                    }
                }
            }
            /*case 3*/
            else{
                replace_node = delete_node_right;
                /*find the smallest value of the delete node right subtree*/
                while(replace_node->left != NULL){
                    replace_node = replace_node->left;
                }
                replace_node_parent = replace_node->parent;
                /*replace delete node with replace node*/
                if(replace_node_parent != delete_node){
                    if(replace_node->right != NULL){
                        if(replace_node_parent->left == NULL){
                            replace_node_parent->right = replace_node->right;
                            replace_node->right->parent = replace_node_parent;
                        }
                        else{
                            replace_node_parent->left = replace_node->right;
                            replace_node->right->parent = replace_node_parent;
                        }
                    }
                    else{
                        if(replace_node_parent->left != NULL){
                            if(replace_node_parent->left->node_value == replace_node->node_value){
                                replace_node_parent->left = NULL;
                            }
                            else{
                                replace_node_parent->right = NULL;
                            }
                        }
                        else{
                            replace_node_parent->right = NULL;
                        }
                    }
                }
                replace_node->left = delete_node->left;
                delete_node->left->parent = replace_node;
                if(replace_node->node_value != delete_node->right->node_value){
                    replace_node->right = delete_node->right;
                    delete_node->right->parent = replace_node;
                }

                /*link the replace node on the parent of delete node*/
                if(delete_node_parent->right == NULL){
                    delete_node_parent->left = replace_node;
                    replace_node->parent = delete_node_parent;
                }
                else if(delete_node_parent->left == NULL){
                    delete_node_parent->right = replace_node;
                    replace_node->parent = delete_node_parent;
                }
                else{
                    if(delete_node_parent->left->node_value == delete_num){
                        delete_node_parent->left = replace_node;
                        replace_node->parent = delete_node_parent;
                    }
                    else{
                        delete_node_parent->right = replace_node;
                        replace_node->parent = delete_node_parent;
                    }
                }
            }
        }
        else{ //delete root
            node* delete_node_parent = delete_node->parent;
            node* delete_node_right = delete_node->right;
            node* delete_node_left = delete_node->left;
            node* replace_node = NULL;
            node* replace_node_parent = NULL;
            /* delete root case 1 */
            if(delete_node_left == NULL && delete_node_right == NULL){
                root = NULL;
            }
            /* delete root case 2-1 */
            else if(delete_node_left != NULL && delete_node_right == NULL){
                root = delete_node_left;
                delete_node->left = NULL;
                delete_node->parent = NULL;
            }
            /* delete root case 2-2 */
            else if(delete_node_left == NULL && delete_node_right != NULL){
                root = delete_node_right;
                delete_node->right = NULL;
                delete_node->parent = NULL;
            }
            /* delete root case 3 */
            else{
                replace_node = delete_node_right;
                /*find the smallest value of the delete node right subtree*/
                while(replace_node->left != NULL){
                    replace_node = replace_node->left;
                }
                replace_node_parent = replace_node->parent;
                /*replace delete node with replace node*/
                if(replace_node_parent != delete_node){
                    if(replace_node->right != NULL){
                        if(replace_node_parent->left == NULL){
                            replace_node_parent->right = replace_node->right;
                            replace_node->right->parent = replace_node_parent;
                        }
                        else{
                            replace_node_parent->left = replace_node->right;
                            replace_node->right->parent = replace_node_parent;
                        }
                    }
                    else{
                        if(replace_node_parent->left != NULL){
                            if(replace_node_parent->left->node_value == replace_node->node_value){
                                replace_node_parent->left = NULL;
                            }
                            else{
                                replace_node_parent->right = NULL;
                            }
                        }
                        else{
                            replace_node_parent->right = NULL;
                        }
                    }
                }
                replace_node->left = delete_node->left;
                delete_node->left->parent = replace_node;
                if(replace_node->node_value != delete_node->right->node_value){
                    replace_node->right = delete_node->right;
                    delete_node->right->parent = replace_node;
                }

                /*link the replace node on the parent of delete node*/
                root = replace_node;
            }
        }
    }
    /*End of delete node*/


    /*Print BST*/
    int print_num = num_of_input - num_of_delete;
    BST[0] = root;
    i = 0; /*dequeue position*/
    j = 0; /*enqueue position*/
    if(root != NULL){
        while(i<print_num){
            if(BST[i]->left != NULL){
                j++;
                BST[j] = BST[i]->left;
            }
            if(BST[i]->right != NULL){
                j++;
                BST[j] = BST[i]->right;
            }
            i++;
        }
        printf("%d", BST[0]->node_value);
        for(i=1; i<print_num; i++){
            printf("\n");
            printf("%d", BST[i]->node_value);
        }
    }
    /*End of print BST*/

    return 0;
}

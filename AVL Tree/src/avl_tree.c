#include<stdio.h>
#include<stdlib.h>
#include <string.h>
// strcmp(), strcpy(), malloc(), scanf(), printf()

/* A binary tree node has data, pointer to left child
   and a pointer to right child */
typedef struct _node{
    char phone[12];
    char name[25];
    struct _node* parent;
    struct _node* left;
    struct _node* right;
}Node;

// Print pre-order
void preorder(Node* node){
    if(node){
        if(node->parent == NULL){
            printf("%s", node->name);
            preorder(node->left);
            preorder(node->right);
        }
        else{
            printf(" %s", node->name);
            preorder(node->left);
            preorder(node->right);
        }

    }
}


// Compute the "maxDepth" of a tree -- the number of
// nodes along the longest path from the root node
// down to the farthest leaf node.
int maxDepth(Node* node){
   if (node==NULL)
       return 0;
   else{
       // compute the depth of each subtree
       int lDepth = maxDepth(node->left);
       int rDepth = maxDepth(node->right);

       // use the larger one
       if (lDepth > rDepth)
           return(lDepth+1);
       else return(rDepth+1);
   }
}

int BalanceFactor(Node* node){
    Node* node_left = node->left;
    Node* node_right = node->right;
    return(maxDepth(node_left) - maxDepth(node_right));
}

// Helper function that allocates a new node with the
// given data and NULL left and right pointers.
Node* newNode(char* input_name, char* input_phone){
    Node* node = (Node*)malloc(sizeof(Node));

    memset(node->phone, '\0', sizeof(node->phone));
    memset(node->name, '\0', sizeof(node->name));
    strcpy(node->phone, input_phone);
    strcpy(node->name, input_name);
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    return(node);
}

// npp = strcmp(insert_name, node->parent->parent->name), npp<0 : go left, npp>0 : go right
// node = node with BF +1 or -1
void LL_rotation(Node* node, int npp){
    Node* node_parent = node->parent;
    Node* node_right_old = node->right;
    Node* node_grand_parent = node->parent->parent;

    node->parent = node_parent->parent;
    node_parent->parent = node;
    if(node->right != NULL){
        node->right->parent = node_parent;
    }
    node_parent->left = NULL; // !!! this move is important !!!

    node->right = node_parent;
    node_parent->left = node_right_old;
    if(node_grand_parent != NULL){
        if(npp<0){
            node_grand_parent->left = node;
        }
        else{
            node_grand_parent->right = node;
        }
    }
}

// npp = strcmp(insert_name, node->parent->parent->name), npp<0 : go left, npp>0 : go right
// node = node with BF +1 or -1
void RR_rotation(Node* node, int npp){
    Node* node_parent = node->parent;
    Node* node_left_old = node->left;
    Node* node_grand_parent = node->parent->parent;

    node->parent = node_parent->parent;
    node_parent->parent = node;
    if(node->left != NULL){
        node->left->parent = node_parent;
    }
    node_parent->right = NULL;

    node->left = node_parent;
    node_parent->right = node_left_old;
    if(node_grand_parent != NULL){
        if(npp<0){
            node_grand_parent->left = node;
        }
        else{
            node_grand_parent->right = node;
        }
    }
}

// mid_node = node between path L & R
void LR_rotation(Node* mid_node, int npp){
    Node* node = mid_node->right;
    Node* node_grand_grand_parent = node->parent->parent->parent;
    Node* node_grand_parent = node->parent->parent;
    Node* node_parent = node->parent;
    Node* node_left_old = node->left;
    Node* node_right_old = node->right;

    node->parent = node_grand_parent->parent;
    node_grand_parent->parent = node;
    node_parent->parent = node;
    if(node->left != NULL) node->left->parent = node_parent;
    if(node->right != NULL) node->right->parent = node_grand_parent;

    node->left = node_parent;
    node->left->right = node_left_old;
    node->right = node_grand_parent;
    node->right->left = node_right_old;
    if(node_grand_grand_parent != NULL){
        if(npp<0){
            node_grand_grand_parent->left = node;
        }
        else{
            node_grand_grand_parent->right = node;
        }
    }
}

// mid_node = node between path R & L
void RL_rotation(Node* mid_node, int npp){
    Node* node = mid_node->left;
    Node* node_grand_grand_parent = node->parent->parent->parent;
    Node* node_grand_parent = node->parent->parent;
    Node* node_parent = node->parent;
    Node* node_left_old = node->left;
    Node* node_right_old = node->right;

    node->parent = node_grand_parent->parent;
    node_grand_parent->parent = node;
    node_parent->parent = node;
    if(node->left != NULL) node->left->parent = node_grand_parent;
    if(node->right != NULL) node->right->parent = node_parent;

    node->left = node_grand_parent;
    node->left->right = node_left_old;
    node->right = node_parent;
    node->right->left = node_right_old;
    if(node_grand_grand_parent != NULL){
        if(npp<0){
            node_grand_grand_parent->left = node;
        }
        else{
            node_grand_grand_parent->right = node;
        }
    }
}

void Search_node(Node* root, char* name){
    Node* current_node = root;

    while(current_node != NULL){
        if(strcmp(current_node->name, name) == 0){
            printf("%s", current_node->phone);
            break;
        }
        else if(strcmp(name, current_node->name) < 0){
            current_node = current_node->left;
        }
        else{
            current_node = current_node->right;
        }
    }

    if(current_node == NULL){
        printf("null");
    }
}



// Start of main
int main()
{
    int i;
    int j;
    char name[25];
    char phone[12];
    Node* root = NULL;
    Node* backward_node = NULL;

    // Start of D ... to ... S
    scanf("%s", &name);
    while(strcmp(name, "S") != 0){
        scanf("%s", &name);
        if(strcmp(name, "S") == 0){
            break;
        }
        scanf("%s\n", &phone);

        if(root == NULL){
            root = newNode(name, phone);
        }
        else{
            Node* new_node = newNode(name, phone);
            Node* compare_node = root;
            // Put new node in AVL tree
            while(new_node->parent == NULL){
                if(strcmp(new_node->name, compare_node->name) < 0){
                    if(compare_node->left == NULL){
                        new_node->parent = compare_node;
                        compare_node->left = new_node;
                    }
                    else{
                        compare_node = compare_node->left;
                    }
                }
                else{
                    if(compare_node->right == NULL){
                        new_node->parent = compare_node;
                        compare_node->right = new_node;
                    }
                    else{
                        compare_node = compare_node->right;
                    }
                }
            }

            // Check and keep the AVL tree balance
            Node* new_root = NULL;
            backward_node = new_node;
            while(backward_node->parent != NULL){
                if(BalanceFactor(backward_node->parent) * BalanceFactor(backward_node->parent) == 4){
                    int npp = 0;
                    if(backward_node->parent->parent != NULL) npp = strcmp(name, backward_node->parent->parent->name);

                    // RR
                    if(BalanceFactor(backward_node->parent) == -2 && BalanceFactor(backward_node) == -1){
                        if(backward_node->parent->parent == NULL){
                            new_root = backward_node;
                        }
                        RR_rotation(backward_node, npp);
                        if(new_root != NULL){
                            root = new_root;
                        }
                        break;
                    }
                    // LL
                    else if(BalanceFactor(backward_node->parent) == 2 && BalanceFactor(backward_node) == 1){
                        if(backward_node->parent->parent == NULL) new_root = backward_node;
                        LL_rotation(backward_node, npp);
                        if(new_root != NULL) root = new_root;
                        break;
                    }
                    // RL
                    else if(BalanceFactor(backward_node->parent) == -2 && BalanceFactor(backward_node) == 1){
                        if(backward_node->parent->parent == NULL) new_root = backward_node->left;
                        RL_rotation(backward_node, npp);
                        if(new_root != NULL) root = new_root;
                        break;
                    }
                    // LR
                    else{
                        if(backward_node->parent->parent == NULL) new_root = backward_node->right;
                        LR_rotation(backward_node, npp);
                        if(new_root != NULL) root = new_root;
                        break;
                    }
                }
                else{
                    backward_node = backward_node->parent;
                }
            } // End of checking AVL tree balance
        }
    }

    preorder(root);
    printf("\n");

    // searching requests
    int first_search = 1;
    while(strcmp(name, "E") != 0){
        scanf("%s", &name);
        if(strcmp(name, "E") == 0){
            break;
        }
        else{
            //printf("%s\n", name);
            if(root == NULL){
                if(first_search == 1){
                    printf("%s ", name);
                    printf("null");
                    first_search = 0;
                }
                else{
                    printf("\n");
                    printf("%s ", name);
                    printf("null");
                }
            }
            else{
                if(first_search == 1){
                    printf("%s ", name);
                    Search_node(root, name);;
                    first_search = 0;
                } // End of first_search
                else{
                    printf("\n");
                    printf("%s ", name);
                    Search_node(root, name);;
                } // End of else_search
            }
        }
    }
    return 0;
}

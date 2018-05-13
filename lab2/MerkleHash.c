// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>


// #define TREE_HEIGHT 4
// #define BLOCK_SIZE 5
// #define DATA_BLOCKS 8 


// typedef struct { 
//     char *hash;
//     char *data;
//     struct node *parent;
//     struct node *left;
//     struct node *right;
// } node;

// typedef struct {
//     long n;
//     long tree_height;
//     long data_block_size;
//     long data_blocks;
//     //long hash;

//     node *nodes;
// } merkle_tree;



// int build_tree(merkle_tree *tree, char **data);
// void print_tree(merkle_tree *tree);



// int main(){
//     node *one = {"hash", "data", NULL, NULL, NULL };
//     node *two = {"hash", "data", &one, NULL, NULL};
//     one->left = two;


//     int i;
//     char *data[DATA_BLOCKS];
//     char *data_copy[DATA_BLOCKS];
//     char buffer[BLOCK_SIZE];
//     merkle_tree tree = {0, TREE_HEIGHT, BLOCK_SIZE, DATA_BLOCKS, NULL};

//     for (i=0; i<BLOCK_SIZE; i++){
//         buffer[i] = "A";
//     }


//     for (i=0; i<DATA_BLOCKS; i++) {
//         data[i] = (char *)malloc(sizeof(char) * BLOCK_SIZE);
//         data_copy[i] = (char *)malloc(sizeof(char) * BLOCK_SIZE);
//         memcpy(data[i], buffer, BLOCK_SIZE);
//         memcpy(data_copy[i], buffer, BLOCK_SIZE);
//     }

//     build_tree(&tree, data);
//     print_tree(&tree);

//     return 0;
// }


// int build_tree(merkle_tree *tree, char **data) {

//     if (tree->data_blocks > (1 << (tree->tree_height - 1))){
//         return -1;
//     }
//     int i, leaf_start;
//     leaf_start = (1 << (tree->tree_height - 1));
//     tree->n = leaf_start + tree->data_blocks - 1;
//     tree->nodes = (node *)malloc(sizeof(node) * (tree->n + 1));
//     for (i = leaf_start; i <= tree->n; i++) {
//         tree->nodes[i].data = data[i-leaf_start];
//         tree->nodes[i].hash = NULL;
        
//     }
//     for (i = leaf_start - 1; i > 0; i--) {
//         tree->nodes[i].hash = NULL;
       
//     }
//     return 0;
// }



// void print_tree(merkle_tree *tree) {

//     for(int i=1; i <= tree->n; i++){
        
//         // if (! tree->nodes ) {
//         //     printf("<empty hash>\n");
//         //     break;
//         // }
//         for(int j = 0; j < BLOCK_SIZE; j++){
//             printf("%02x\t", tree->nodes[j]);
//             if ((j%5) == 0){
//                 printf("\n");
//             }
//         }
//         printf("\n");
//     }
//     return;
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COUNT 10
#define TREE_HEIGHT 3;

typedef struct node 
{
	int data;
    int hash;

	struct node *left;
	struct node *right;
    struct node *parent;
}node;

struct stack
{
    int data;
    struct stack* next;
};
 

 


struct node* new_node(int data);
int isEmpty(struct stack *stack_head);
void push(struct stack** stack_head, int data);
int pop(struct stack** stack_head);
int peek(struct stack* stack_head);
void print2DUtil(node *root, int space);
void print2D(node *root);
int hash(int data);
int get_root_hash(node *root);
void authentication_values(node*root, node *leaf, struct stack** stack_head);
void pop_stack(struct stack** stack_head);
struct stack* newNode(int data);
int siblings_hash[2];





int main(){
/*create root*/
    node *root   = new_node(1);
    root->left   = new_node(2);
    root->left->parent = root;
    root->right  = new_node(3);
    root->right->parent = root;
    struct stack* stack = NULL;


    root->left->left  = new_node(4);
    root->left->left->parent = root->left;
    root->left->right = new_node(5);
    root->left->right->parent = root->left;
    root->right->left  = new_node(6);
    root->right->left->parent = root->right;
    root->right->right = new_node(7);
    root->right->right->parent = root->right;


    // root->left->left->left  = new_node(8);
    // root->left->left->right  = new_node(9);
    // root->left->right->left  = new_node(10);
    // root->left->right->right  = new_node(11);
    // root->right->left->left  = new_node(12);
    // root->right->left->right  = new_node(13);
    // root->right->right->left  = new_node(14);
    // root->right->right->right  = new_node(15); 
    hash_tree(root);
    print2D(root);
    
    
    /////// STACK IS CURRENTLY OUT OF SCOPE WHEN BEING PUSHED TO... MAKE IT GLOBAL? ///////



    printf("leaf is %d\nAuthentication hashes are:\n", root->right->left->hash);
    authentication_values(root, root->right->left, stack);
    push(&stack, 10);
    printf("popped: %d\n", pop(&stack));
    pop_stack(stack);
 
    return 0;
}


void authentication_values(node* root, node *leaf, struct stack** stack_head){

    if(leaf->hash == root->hash){
        return;
    }
    if(leaf->parent->left->hash == leaf->hash){
        printf("\t\t%d\n",leaf->parent->right->hash);
        push(&stack_head, leaf->parent->right->hash);
    }
    else if (leaf->parent->right->hash == leaf->hash){
        printf("\t\t%d\n",leaf->parent->left->hash);
        push(&stack_head, leaf->parent->left->hash);
    }
    authentication_values(root, leaf->parent, stack_head);

}




int get_root_hash(node *root){
    return root->hash;
}






struct node* new_node(int data){
    // Allocate memory for new node 
    struct node* node = (struct node*)malloc(sizeof(struct node));

    // Assign data to this node
    node->data = data;
    node->hash = hash(data);
    // Initialize left and right children as NULL
    node->left = NULL;
    node->right = NULL;
    return(node);
}



void hash_tree(node *root)
{
    // Base case
    if (root == NULL)
        return;
    if (root->right == NULL && root->left == NULL){
        return;
    }
    if (root->right == NULL && root->left != NULL){
        hash_tree(root->left);
        root->hash = hash(root->left->hash);
        return;
    }
    else if (root->left == NULL && root->right != NULL){
        hash_tree(root->right);
        root->hash = hash(root->right->hash);
        return;
    }
    else{
        hash_tree(root->right);
        hash_tree(root->left);
        root->hash = hash(root->left->hash + root->right->hash);
    }
    
}


int hash(int data){
    return data + 10;
}


void pop_stack(struct stack** stack_head){
    
        printf("popped: %d\n", pop(&stack_head));
    
}


//https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
void print2DUtil(node *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->hash);
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(node *root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}





// Source: https://www.geeksforgeeks.org/stack-data-structure-introduction-program/

int isEmpty(struct stack *stack_head)
{
    return !stack_head;
}
 
void push(struct stack** stack_head, int data)
{
    struct stack* stack_node = newNode(data);
    stack_node->next = *stack_head;
    *stack_head = stack_node;
    printf("%d pushed to stack\n", data);
}
 
int pop(struct stack** stack_head)
{
    if (isEmpty(*stack_head))
        return -1;
    struct stack* temp = *stack_head;
    *stack_head = (*stack_head)->next;
    int popped = temp->data;
    free(temp);
 
    return popped;
}
 
int peek(struct stack* stack_head)
{
    if (isEmpty(stack_head))
        return -1;
    return stack_head->data;
}

struct stack* newNode(int data)
{
    struct stack* stack_node =
              (struct stack*) malloc(sizeof(struct stack));
    stack_node->data = data;
    stack_node->next = NULL;
    return stack_node;
}
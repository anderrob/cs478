

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <limits.h>
#define COUNT 10
#define TREE_HEIGHT 3;

typedef struct node 
{
	char* data;
    char* hash;

	struct node *left;
	struct node *right;
    struct node *parent;
}node;

// typedef struct stack
// {
//     char* data;
//     struct stack* next;
// }stack;
 
struct stack
{
    int top;
    unsigned capacity;
    char** array;
};
 
 
char global_hash[SHA_DIGEST_LENGTH*2] = {0};

struct node* new_node(char* data);
// int isEmpty(struct stack *stack_head);
// void push(struct stack** stack_head, char* data);
// char* pop(struct stack** stack_head);
// int peek(struct stack* stack_head);
void print2DUtil(node *root, int space);
void print2D(node *root);
char* hash(char* data);
char* get_root_hash(node *root);

void pop_stack(struct stack* stack_head);
// struct stack* newNode(char* data);
int siblings_hash[2];


char* pop(struct stack* stack);
void push(struct stack* stack, int item);
int isEmpty(struct stack* stack);
int isFull(struct stack* stack);
struct stack* createStack(unsigned capacity);

void authentication_values(node* root, node *leaf, struct stack* stack);


int main(){
/*create root*/
    node *root   = new_node("root");
    root->left   = new_node("node 2");
    root->left->parent = root;
    root->right  = new_node("node 3");
    root->right->parent = root;
    struct stack* stack = createStack(5);


    root->left->left  = new_node("node 4");
    root->left->left->parent = root->left;
    root->left->right = new_node("node 5");
    root->left->right->parent = root->left;
    root->right->left  = new_node("node 6");
    root->right->left->parent = root->right;
    root->right->right = new_node("node 7");
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
    

    printf("leaf is %s\nAuthentication hashes are:\n", root->right->left->hash);
    authentication_values(root, root->right->left, stack);
    printf("Hashes needed to verify leaf %s are:\n", root->right->left->data);
    pop_stack(stack);
 
    return 0;
}


void authentication_values(node* root, node *leaf, struct stack* stack){

    if(leaf->hash == root->hash){
        return;
    }
    if(leaf->parent->left->hash == leaf->hash){
        //printf("\t\t%d\n",leaf->parent->right->hash);
        //push(&*stack_head, leaf->parent->right->hash);
        push(stack, leaf->parent->right->hash);
    }
    else if (leaf->parent->right->hash == leaf->hash){
        //printf("\t\t%d\n",leaf->parent->left->hash);
        //push(&*stack_head, leaf->parent->left->hash);
        push(stack, leaf->parent->left->hash);
    }
    authentication_values(root, leaf->parent, stack);

}




char* get_root_hash(node *root){
    return root->hash;
}






struct node* new_node(char* data){
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
        //strcpy(root->hash, hash(strcat(root->left->hash, root->right->hash)));
    }
    
}


char* hash(char* data){
    // char temp[1024];
    // strcpy(temp, data);
    // return strcat(temp, "hashed" );
    return data;
}


void pop_stack(struct stack* stack_head){
    
    while (stack_head->top != -1  ){
        printf("\t\t\t%s\n", pop(stack_head));
    }
    
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
    for (int i = COUNT; i < space; i++){
        printf(" ");
    }   
    printf("%s\n", root->hash);
 
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

// function to create a stack of given capacity. It initializes size of
// stack as 0
struct stack* createStack(unsigned capacity)
{
    struct stack* stack = (struct stack*) malloc(sizeof(struct stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char**) malloc(stack->capacity * sizeof(int));
    return stack;
}
 
// Stack is full when top is equal to the last index
int isFull(struct stack* stack)
{   return stack->top == stack->capacity - 1; }
 
// Stack is empty when top is equal to -1
int isEmpty(struct stack* stack)
{   return stack->top == INT_MIN;  }
 
// Function to add an item to stack.  It increases top by 1
void push(struct stack* stack, int item)
{
    if (isFull(stack))
        return;
    stack->array[++stack->top] = item;
    printf("\t\t\t%s\n", item);
}
 
// Function to remove an item from stack.  It decreases top by 1
char* pop(struct stack* stack)
{
    if (isEmpty(stack))
        return -1;
    return stack->array[stack->top--];
}


// int isEmpty(struct stack *stack_head)
// {
//     return !stack_head;
// }
 
// void push(struct stack** stack_head, char* data)
// {
//     struct stack* stack_node = newNode(data);
//     stack_node->next = *stack_head;
//     *stack_head = stack_node;
//     printf("\t\t%s\n", data);
// }
 
// char* pop(struct stack** stack_head)
// {
//     if (isEmpty(*stack_head))
//         return NULL;
//     struct stack* temp = *stack_head;
//     *stack_head = (*stack_head)->next;
//     char popped[1024];
//     printf("in pop, temp->data: %s\n", temp->data);
//     strcpy(popped, temp->data);
//     printf("in pop after strcpy, popped: %s\n", popped);

//     free(temp);
//     printf("in pop after strcpy, popped after free temp: %s\n", popped);
//     return popped;
// }
 
// int peek(struct stack* stack_head)
// {
//     if (isEmpty(stack_head))
//         return -1;
//     return stack_head->data;
// }

// struct stack* newNode(char* data)
// {
//     struct stack* stack_node =
//               (struct stack*) malloc(sizeof(struct stack));
//     stack_node->data = data;
//     stack_node->next = NULL;
//     return stack_node;
// }

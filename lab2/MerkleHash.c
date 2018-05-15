#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEAVES 16
#define COUNT 3

typedef struct node
{
    char* hash;
    int num;
    struct node* left;
    struct node* right;
}node;
 
typedef struct link_node
{
    int num;
    struct node* node;
    struct link_node* next;
}link_node;


node* newNode(int num);
link_node* newlink_node(int num);
int isEmpty(node *root);
void push(node** root, int num);
int pop(link_node** root);
int peek(link_node* root);

int main(){
    /*create root*/
    int num_nodes = (LEAVES*2)-1;
    printf("num_nodes: %d\n", num_nodes);


    node* root[num_nodes];

    for ( int i=0; i< num_nodes; i++){
        root[i] = newNode(i);
    }

    for( int i = 0; i <((num_nodes-1)/2); i++ ){
        root[i]->left = root[(i+i+1)];
        root[i]->right = root[(i+i+2)];
    }
    for( int i = num_nodes; i >((num_nodes-1)/2); i-- ){
        strcpy(root[i]->hash, "hash");
    }


    
    print2D(root[0]);
 
 
    return 0;
}





 
node* newNode(int num)
{
    node* node =
              (struct node*) malloc(sizeof(node));
    node->num = num;
    node->left = NULL;
    node->right = NULL;
    return node;
}
 
int isEmpty(node *root)
{
    return !root;
}
 
// void push(node** root, int num)
// {
//     node* node = newNode(num);
//     node->next = *root;
//     *root = node;
//     printf("%d pushed to stack\n", num);
// }
 
int pop(link_node** root)
{
    if (isEmpty(*root))
        return -1;
    link_node* temp = *root;
    *root = (*root)->next;
    int popped = temp->num;
    free(temp);
 
    return popped;
}
 
int peek(link_node* root)
{
    if (isEmpty(root))
        return -1;
    return root->num;
}
 

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
    printf("%d\n", root->num);
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(node *root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}

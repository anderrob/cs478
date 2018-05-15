#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <openssl/sha.h>
#define LEAVES 1024
#define COUNT 3

typedef struct node
{
    char hash[(SHA_DIGEST_LENGTH*2)+1]; //8 bytes
    //int num; // 4 bytes
    struct node* left; //8 bytes
    struct node* right; //8 bytes
}node;
 
typedef struct link_node
{
    int num;
    struct node* node;
    struct link_node* next;
}link_node;


node* newNode(char* input);
link_node* newlink_node(char* input);
int isEmpty(node *root);
void push(node** root, char* input);
// int pop(link_node** root);
// int peek(link_node* root);
void print2DUtil(node *root, int space);
void print2D(node *root);

int main(){
    /*create root*/
    int num_nodes = (LEAVES*2)-1;
    printf("num_nodes: %d\n", num_nodes);


    node* root[num_nodes];

    for ( int i=0; i< num_nodes; i++){
        root[i] = newNode("hashhashhashhashhashhashhashhashhashhash");
    }

    for( int i = 0; i <((num_nodes-1)/2); i++ ){
        root[i]->left = root[(i+i+1)];
        root[i]->right = root[(i+i+2)];
    }
    for( int i = num_nodes; i >((num_nodes-1)/2); i-- ){
        //strcpy(root[i]->hash, "has");
    }


    
    print2D(root[0]);
 
 
    return 0;
}





 
node* newNode(char* input)
{
    node* node =
              (struct node*) malloc(0xfffff);
    //node->num = num;
    node->left = NULL;
    node->right = NULL;
    strcpy(node->hash, input);
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
 
// int pop(node** root)
// {
//     if (isEmpty(*root))
//         return -1;
//     node* temp = *root;
//     *root = (*root)->next;
//     int popped = temp->num;
//     free(temp);
 
//     return popped;
// }
 
// int peek(node* root)
// {
//     if (isEmpty(root))
//         return -1;
//     return root->num;
// }
 

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

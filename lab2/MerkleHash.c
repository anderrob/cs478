#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEAVES 16


typedef struct node
{
    int hash;
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
 



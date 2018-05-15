#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <openssl/sha.h>
#define LEAVES 32
#define COUNT 3
#define PARENT ((int)floor(((i-1)/2)))
#define LEAF 28
#define LEAF_TO_VERIFY 28

typedef struct node
{
    char hash[(SHA_DIGEST_LENGTH*2)+1]; //8 bytes
    char data[(SHA_DIGEST_LENGTH*2)+1];; // 4 bytes
    struct node* left; //8 bytes
    struct node* right; //8 bytes
}node;
 
typedef struct link_node
{
    int num;
    struct node* node;
    struct link_node* next;
}link_node;

char global_hash[SHA_DIGEST_LENGTH*2] = {0};
node* newNode(char* input);
link_node* newlink_node(char* input);
int isEmpty(node *root);
void push(node** root, char* input);
// int pop(link_node** root);
// int peek(link_node* root);
void print2DUtil(node *root, int space);
void print2D(node *root);
char* get_root_hash(node *root);

int main(){
    /*create root*/
    int num_nodes = (LEAVES*2)-1;
    printf("num_nodes: %d\n", num_nodes);


    node* root[num_nodes];

    for ( int i=0; i< num_nodes; i++){
        root[i] = newNode("data");
    }

    for( int i = 0; i <((num_nodes-1)/2); i++ ){
        root[i]->left = root[(i+i+1)];
        root[i]->right = root[(i+i+2)];
    }
    for( int i = ((num_nodes-1)/2); i <num_nodes; i++ ){
        strcpy(root[i]->data, "leaf");
    }
    for( int i = ((num_nodes-1)/2); i <num_nodes; i++ ){
        memset(&global_hash[0], '\0', sizeof(global_hash));
        unsigned char temp[SHA_DIGEST_LENGTH] = {'0'};
        unsigned char catted[41] = {'0'};

        SHA1((unsigned char*)root[i]->data, strlen(root[i]->data), temp);
        for(int j=0; j<SHA_DIGEST_LENGTH; j++){
            sprintf((char*)&(catted[j*2]), "%02x", temp[j]);
        }
        strcpy(root[i]->hash, catted);
        //strcpy(root[i]->hash, "leaf");
    }
    for (int i = (((num_nodes-1)/2)-1); i >= 0; i--){
        memset(&global_hash[0], '\0', sizeof(global_hash));
        unsigned char temp[SHA_DIGEST_LENGTH] = {'0'};
        unsigned char catted[82] = {'0'};
        strcpy(catted, root[i]->left->hash);
        strcat(catted, root[i]->right->hash);
        SHA1((unsigned char*)root[i]->left->hash, strlen(root[i]->left->hash), temp);
        for(int j=0; j<SHA_DIGEST_LENGTH; j++){
            sprintf((char*)&(catted[j*2]), "%02x", temp[j]);
        }
        strcpy(root[i]->hash, catted);
    }



    
    
    print2D(root[0]);
    
    printf("root hash is %s\n\n", get_root_hash(root[0]));
    
    char auth[20][41] = {"\0"};
   
    
    int counter = 0;
    int i = LEAF;
    //strcpy(auth[counter], root[4]->left->hash);
    printf("leaf is %s\nAuthentication hashes are:\n", root[LEAF]);
    while(i != 0){
        if(root[PARENT]->left->hash == root[i]->hash){
            strcpy(auth[counter], root[PARENT]->right->hash);
            counter++;
        }
        else if(root[PARENT]->right->hash == root[i]->hash){
            strcpy(auth[counter], root[PARENT]->left->hash);
            counter++;
        }
        i = PARENT;
    }
    // printf("%s", *auth[0]);
    for(int i = 1; strcmp(auth[i], "\0"); i++){
        printf("%s\n", auth[i]);
    }

    //printf("Is the leaf,%s, part of the tree?\t", root[LEAF_TO_VERIFY]);







    return 0;
}






char* get_root_hash(node *root){
    return root->hash;
}




 
node* newNode(char* input)
{
    node* node =
              (struct node*) malloc(0xfffff);
    //node->num = num;
    node->left = NULL;
    node->right = NULL;
    //node->hash = NULL;
    //strcpy(node->hash, input);
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

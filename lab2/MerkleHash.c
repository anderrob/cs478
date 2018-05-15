#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <openssl/sha.h>
#define LEAVES 32
#define COUNT 10
#define PARENT ((int)floor(((i-1)/2)))
#define LEAF 60
#define LEAF_TO_VERIFY 60

typedef struct node
{
    char hash[(SHA_DIGEST_LENGTH*2)+1]; //8 bytes
    char data[(SHA_DIGEST_LENGTH*2)+1];; // 4 bytes
    struct node* left; //8 bytes
    struct node* right; //8 bytes
}node;



char concat_hash[(SHA_DIGEST_LENGTH*4)+1] = {'\0'};
char global_hash[(SHA_DIGEST_LENGTH*2)+1] = {'\0'};
node* newNode(char* input);

int isEmpty(node *root);
void push(node** root, char* input);

void print2DUtil(node *root, int space);
void print2D(node *root);
char* get_root_hash(node *root);
void hash_tree(node* parent_node);
void hash_leaves(node* leaf);
void hash_string(char* s);

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
      hash_leaf(root[i]);


    }
    for (int i = (((num_nodes-1)/2)-1); i >= 0; i--){
        hash_tree(root[i]);

    }




    //print tree
    print2D(root[0]);

    //get authentication hashes
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




    // print authentication hashes
    for(int i = 0; strcmp(auth[i], "\0"); i++){
        printf("%s\n", auth[i]);
    }

    printf("Is the leaf, %s, part of the tree?\t", root[LEAF_TO_VERIFY]);
    unsigned char catted[82] = {'0'};
    // Verify (requires to get the authentication hashes first in order to fill auth)
    for(int i = 0; i < 3; i++){
        memset(&global_hash[0], '\0', sizeof(global_hash));
        unsigned char temp[SHA_DIGEST_LENGTH] = {'0'};

        strcpy(catted, auth[i]);
        strcat(catted, auth[i+1]);
        SHA1((unsigned char*)catted, strlen(catted), temp);
        for(int j=0; j<SHA_DIGEST_LENGTH; j++){
            sprintf((char*)&(catted[j*2]), "%02x", temp[j]);
        }
        //strcpy(root[i]->hash, catted);
    }
    if (strcmp(catted, get_root_hash(root[0])) == 0){
        printf("yes\n");
    }
    else{
        printf("no\n");
    }

    printf("\ncatted: %s\nroot:%s\n", catted, get_root_hash(root[0]));





    return 0;
}



void hash_tree(node* parent_node) {
  memset (&concat_hash[0], '\0', sizeof(concat_hash));
  strcpy(concat_hash, parent_node->left->hash);
  strcat(concat_hash, parent_node->right->hash);
  hash_string(concat_hash);
  strcpy(parent_node->hash, global_hash);
}

void hash_leaf(node* leaf) {
  hash_string(leaf->data);
  strcpy(leaf->hash, global_hash);
}

void hash_string(char* s) {
  memset(&global_hash[0], '\0', sizeof(global_hash));
  unsigned char temp[SHA_DIGEST_LENGTH] = {'\0'};
  SHA1((unsigned char*)s, strlen(s), temp);
  for(int i=0; i<SHA_DIGEST_LENGTH; i++){
    sprintf((char*)&(global_hash[i*2]), "%02x", temp[i]);
  }
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

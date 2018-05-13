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

typedef struct node 
{
	int data;
    int hash;

	struct node *left;
	struct node *right;
    struct node *parent;
}node;


struct node* new_node(int data);
void print2DUtil(node *root, int space);
void print2D(node *root);
int hash(int data);
int get_root_hash(node *root);
int* authentication_values(node*root, node *leaf);



int main(){
/*create root*/
    node *root   = new_node(1);
    root->left   = new_node(2);
    root->left->parent = root;
    root->right  = new_node(3);
    root->right->parent = root;


    root->left->left  = new_node(4);
    root->left->left->parent = root;
    root->left->right = new_node(5);
    root->left->right->parent = root;
    root->right->left  = new_node(6);
    root->right->left->parent = root;
    root->right->right = new_node(7);
    root->right->right->parent = root;


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
 
    return 0;

getchar();
return 0;
}


int* authentication_values(node*root, node *leaf){




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
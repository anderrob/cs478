#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TREE_HEIGHT 4 
#define BLOCK_SIZE 1024
#define DATA_BLOCKS 8 


typedef struct { 
    char *hash;
    char *data;
} node;

typedef struct {
    long n;
    long tree_height;
    long data_block_size;
    long data_blocks;
    //long hash;

    node *nodes;
} merkle_tree;



int build_tree(merkle_tree *tree, char **data);
void print_tree(merkle_tree *tree);



int main()
{
    int i;
    char *data[DATA_BLOCKS];
    char *data_copy[DATA_BLOCKS];
    char buffer[BLOCK_SIZE];
    merkle_tree tree = {0, TREE_HEIGHT, BLOCK_SIZE, DATA_BLOCKS, NULL};

    for (i=0; i<BLOCK_SIZE; i++)
        buffer[i] = "A";

    for (i=0; i<DATA_BLOCKS; i++) {
        data[i] = (char *)malloc(sizeof(char) * BLOCK_SIZE);
        data_copy[i] = (char *)malloc(sizeof(char) * BLOCK_SIZE);
        memcpy(data[i], buffer, BLOCK_SIZE);
        memcpy(data_copy[i], buffer, BLOCK_SIZE);
    }

    build_tree(&tree, data);
    
    print_tree(&tree);

    return 0;
}


int build_tree(merkle_tree *tree, char **data) {

    if (tree->data_blocks > (1 << (tree->tree_height - 1)))
        return -1;
    int i, leaf_start;
    leaf_start = (1 << (tree->tree_height - 1));
    tree->n = leaf_start + tree->data_blocks - 1;
    tree->nodes = (node *)malloc(sizeof(node) * (tree->n + 1));
    for (i = leaf_start; i <= tree->n; i++) {
        tree->nodes[i].data = data[i-leaf_start];
        tree->nodes[i].hash = NULL;
        
    }
    for (i = leaf_start - 1; i > 0; i--) {
        tree->nodes[i].hash = NULL;
       
    }
    return 0;
}



void print_tree(merkle_tree *tree) {

    for(int i=1; i <= tree->n; i++){
        
        // if (! tree->nodes ) {
        //     printf("<empty hash>\n");
        //     break;
        // }
        for(i = 0; i < BLOCK_SIZE; i++){
            printf("%02x", tree->nodes[i]);
        }
        printf("\n");
    }
    return;
}
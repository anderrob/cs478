#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <openssl/sha.h>


void key_gen(int t, int k, int l);
void sign(char* m, int t, int k);
int verify(char* m, int t, int k);
char* random_string(int length);
void hash_string(char* s);
char* string_to_binary(char* s);
void fill_T();
void S(int m, int k, int t, int subset[]);
int t_choose_k();
void init_t_array(int*, int t);
char public_key[1024][SHA_DIGEST_LENGTH*2+1] = {'/0'};
char signature[32][129] = {'\0'};
char ver[32][SHA_DIGEST_LENGTH*2+1] = {'\0'};
char** secret_key = NULL;
char** split = NULL;
char hash[SHA_DIGEST_LENGTH*2] = {0};
int* sign_indices = NULL;
int* ver_indices = NULL;
int count = 0;

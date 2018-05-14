#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <openssl/sha.h>

void key_gen(int t, int k, int l);
void sign(char* m, int t, int k);
void verify();
char* random_string(int length);
void hash_string(char* s);
char* string_to_binary(char* s);
void fill_T();
void S(int m, int k, int t, int subset[]);
int t_choose_k();
void init_t_array(int*, int t);
char public_key[1024][SHA_DIGEST_LENGTH*2+1] = {'/0'};
char signature[32][5] = {'\0'};
char** secret_key = NULL;
char** split = NULL;
char hash[SHA_DIGEST_LENGTH*2] = {0};
int* indices = NULL;
int count = 0;

int main() {
  int l = 4;
  int t = 1024;
  int k = 32;
  int b = 4;
  int m = 30;
  int t_array[t];
  int subset[k];
  srand(time(NULL));
  init_t_array(t_array, t);
  int choose = t_choose_k();
  S(m, k, t, subset);
  key_gen(t, k, l);
  sign("hfeiowaburiaoieyabu", t, k);
  return 0;
}

int t_choose_k(int t, int k) {
  int result = 1;
  for(int i=1; i<=k; i++){
    result *= t - (k-i);
    result /= i;
  }
  return result;
}

void S(int m, int k, int t, int subset[]){
  int pre_compute = t_choose_k(t-1, k-1);
  if(k == 0){
    return;
  }
  if(m < pre_compute){
    subset[count] = t;
    count++;
    S(m, k-1, t-1, subset);
  } else {
    S(m-pre_compute, k, t-1, subset);

  }
}

void init_t_array(int t_array[], int t) {
  for(int i=1; i<=t; i++){
    t_array[i-1] = i;
  }
}

char* random_string(int length){
  static char charset[] = "10";
  char* random_string = NULL;

  if(length){
    random_string = malloc(sizeof(char)*(length+1));

    if(random_string) {
      for(int i=0; i<length; i++){
        int key = rand() % (int)(sizeof(charset)-1);
        random_string[i] = charset[key];
      }
      random_string[length] = '\0';
    }
  }
  return random_string;
}

void key_gen(int t, int k, int l){
  secret_key = malloc(sizeof(char*)*(t));
  for(int i=0; i<t; i++){
    secret_key[i] = random_string(l);
    hash_string(secret_key[i]);
    strcpy(public_key[i], hash);
    memset(&hash, '\0', sizeof(hash));
  }
}

void divide_string(char* s, int size) {
  int str_size = strlen(s);
  int count = 0;
  int index = 0;
  char* temp;

  split = malloc(sizeof(char*)*(str_size / size));
  for(int i=0; i<str_size+1; i++){
    if(i == 0){
      temp = malloc(sizeof(char)*(size+1));
    }
    if(i % size == 0 && i != 0){
      split[index] = temp;
      index++;
      count = 0;
      temp = malloc(sizeof(char)*(size+1));
    }
    temp[count] = s[i];
    count++;
  }
}

char* string_to_binary(char* s){
  if(s == NULL) return 0;
    size_t len = strlen(s);
    char *binary = malloc(len*8 + 1);
    binary[0] = '\0';
    for(size_t i = 0; i < len; ++i) {
        char ch = s[i];
        for(int j = 7; j >= 0; --j){
            if(ch & (1 << j)) {
                strcat(binary,"1");
            } else {
                strcat(binary,"0");
            }
        }
    }
    return binary;
}

int btoi(char* s){
  register unsigned char *p = s;
  register unsigned int r = 0;

  while(p && *p){
    r <<=1;
    r += (unsigned int)((*p++)& 0x01);
  }
  return (int)r;
}

void sign(char* m, int t, int k) {
  char* binary;
  int size = log2(t);
  hash_string(m);
  binary = string_to_binary(hash);
  divide_string(binary, size);
  indices = malloc(sizeof(int)*sizeof(split));
  for(int i=0; i<k; i++){
    indices[i] = btoi(split[i]);
    strcpy(signature[i], secret_key[indices[i]]);
  }
}

void verify() {

}

void hash_string(char* s){
  unsigned char temp[SHA_DIGEST_LENGTH] = {'\0'};
  SHA1((unsigned char*)s, strlen(s), temp);
  for(int i=0; i<SHA_DIGEST_LENGTH; i++){
    sprintf((char*)&(hash[i*2]), "%02x", temp[i]);
  }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <openssl/sha.h>

void key_gen();
void sign(char* m);
void verify();
char* random_string(int length);
void hash_string(char* s);
char* string_to_binary(char* s);
char** public_key = NULL;
char** secret_key = NULL;
char** split = NULL;
char* k = NULL;
int t = 32;
int l = 4;
char hash[SHA_DIGEST_LENGTH*2] = {0};

int main() {
  k = random_string(4);
  key_gen(4, k, 2);
  for(int i=0; i<2; i++){
    printf("KEY: %s\n", secret_key[i]);
  }
  sign(k);
  return 0;
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

void key_gen(){
  public_key = malloc(sizeof(char*)*(t+2));
  secret_key = malloc(sizeof(char*)*(t+2));
  secret_key[0] = k;
  for(int i=1; i<t+1; i++){
    secret_key[i] = random_string(l);
  }
}

void divide_string(char* s, int t) {
  int str_size = strlen(s);
  int i;
  int part_size;
  int count = 0;

  part_size = str_size / t;
  split = malloc(sizeof(char*)*(str_size/part_size));
  char* temp = malloc(sizeof(char)*(part_size+1));
  memset(temp, '\0', sizeof(temp));
  for(int i=0; i<str_size+1; i++){
    if(i % part_size == 0){
      count = 0;
      split[i] = temp;
    } else{
      temp[count] = s[i];
      count++;
    }
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

void sign(char* m) {
  char* binary;
  double size = log2(t);
  hash_string(m);
  binary = string_to_binary(hash);
  divide_string(binary, (int)size);
}

void hash_string(char* s){
  unsigned char temp[SHA_DIGEST_LENGTH] = {'\0'};
  SHA1((unsigned char*)s, strlen(s), temp);
  for(int i=0; i<SHA_DIGEST_LENGTH; i++){
    sprintf((char*)&(hash[i*2]), "%02x", temp[i]);
  }
}

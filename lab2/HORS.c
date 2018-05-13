#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

void key_gen(int l, char* k, int t);
void sign(char* m, char** secret_key);
void verify();
char* random_string(int length);
char** public_key = NULL;
char** secret_key = NULL;
char* k = NULL;

int main() {
  k = random_string(4);
  key_gen(4, k, 2);
  for(int i=0; i<2; i++){
    printf("KEY: %s\n", secret_key[i]);
  }
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

void key_gen(int l, char* k, int t){
  public_key = malloc(sizeof(char*)*(t+2));
  secret_key = malloc(sizeof(char*)*(t+2));
  secret_key[0] = k;
  for(int i=1; i<t+1; i++){
    secret_key[i] = random_string(l);
  }
}

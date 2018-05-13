#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

void key_gen(int l, int k, int t);
void sign(char* m, char** secret_key);
void verify();
char* random_string(int length);
char** public_key = NULL;
char** secret_key = NULL;

int main() {
  key_gen(4, 4, 2);
  for(int i=0; i<2; i++){
    printf("KEY: %s\n", secret_key[i]);
  }
  return 0;
}

char* random_string(int length){
  static char charset[] = "10";
  char* random_string = NULL;

  if(length){
    printf("allocating memory\n");
    random_string = malloc(sizeof(char)*(length+1));

    if(random_string) {
      for(int i=0; i<length; i++){
        int key = rand() % (int)(sizeof(charset)-1);
        random_string[i] = charset[key];
      }
      random_string[length] = '\0';
    }
  }
  printf("RANDOM: %s\n", random_string);
  return random_string;
}

void key_gen(int l, int k, int t){
  public_key = malloc(sizeof(char*)*(t+1));
  secret_key = malloc(sizeof(char*)*(t+1));
  for(int i=0; i<t; i++){
    secret_key[i] = random_string(l);
  }
}

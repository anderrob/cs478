#include "./HORS.h"
#include "./merkle_hash.h"

typedef struct {
  char* z;
  int st;
} sk;

typedef struct {
  char R[SHA_DIGEST_LENGTH*2+1];
  int d;
} pk;

char* itob(int i);
void pq_key_gen(int l, int k, int t, sk secret, pk public);
void pq_sign (int k, int t, char* m, sk secret);
void pq_ver(int k, int t, char* m, pk public, int st);
int h[33] = {0};

sk secret;
pk public;
char* concat[1153] = {'\0'};
char s[1024][SHA_DIGEST_LENGTH*2+1] = {'\0'};
char v[1024][SHA_DIGEST_LENGTH*2+1] = {'\0'};

char sign_s[1024][SHA_DIGEST_LENGTH*2+1] = {'\0'};
char sign_v[1024][SHA_DIGEST_LENGTH*2+1] = {'\0'};
char ver_v[1024][SHA_DIGEST_LENGTH*2+1] = {'\0'};

int main() {
  int t = 1024;
  int k = 32;
  int l = 128;
  sk secret;
  pk public;
  pq_key_gen(l, k, t, secret, public);
  pq_sign(k, t, "hello", secret);
  pq_ver(k, t, "hello", public, secret.st);

  return 0;
}

void pq_key_gen(int l, int k, int t, sk secret, pk public) {
  public.d = 1;
  secret.st = 1;
  secret.z = random_string(128);
  for(int i=0; i<public.d*t; i++){
    memset(concat, '\0', sizeof(concat));
    strcpy(concat, secret.z);
    strcat(concat, itob(i));
    hash_string(concat);
    strcpy(s[i], hash);
    hash_string(s[i]);
    strcpy(v[i], hash);
  }
  strcpy(public.R, form(v));
}

void pq_sign (int k, int t, char* m, sk secret) {
  char* binary;
  int size = log2(t);
  if(secret.st > public.d){
    exit(0);
  } else {
    hash_string(m);
    binary = string_to_binary(hash);
    divide_string(binary, size);
    for(int i=0; i<k; i++){
      h[i] = btoi(split[i]);
    }
    for(int j=0; j<k; j++){
      int temp = (secret.st-1)+h[j];

      memset(concat, '\0', sizeof(concat));
      strcpy(concat, secret.z);
      strcat(concat, itob(temp));
      hash_string(concat);
      strcpy(sign_s[temp], hash);
      hash_string(sign_s[temp]);
      strcpy(sign_v[temp], hash);
      // get path for leaf
      // assign things to signature
      secret.st++;
    }
  }
  secret.st = 1;
}

void pq_ver(int k, int t, char* m, pk public, int st) {
  char* binary;
  int size = log2(t);
  if(secret.st > public.d){
    exit(0);
  } else {
    hash_string(m);
    binary = string_to_binary(hash);
    divide_string(binary, size);
    for(int i=0; i<k; i++){
      h[i] = btoi(split[i]);
    }
    for(int j=0; j<k; j++){
      int temp = (st-1)+h[j];
      hash_string(sign_s[temp]);
      strcpy(ver_v[temp], hash);
      //call verify
      int b = 1;
      if(b == 0){
        printf("Failed\n");
        exit(1);
      }
    }
  }
  printf("Success\n");
}

char* itob(int i) {
   static char bits[10] = {'0'};
   for(int i=0; i<10; i++){
     bits[i] = '0';
   }
   int bits_index = 9;
   while ( i > 0 ) {
      bits[bits_index--] = (i & 1) + '0';
      i = ( i >> 1);
   }
   return bits;
}

#include "./HORS.h"

typedef struct {
  char* z;
  int st;
} sk;

typedef struct {

  int d;
} pk;

char* itob(int i);
void key(int l, int k, int t);

sk secret;
pk public;
char* concat[1153] = {'\0'};
char s[1024][SHA_DIGEST_LENGTH*2+1] = {'\0'};
char v[1024][SHA_DIGEST_LENGTH*2+1] = {'\0'};

int main() {
  int t = 1024;
  int k = 32;
  int l = 128;
  key(l, k, t);

  //TODO: Form the merkle tree using v

  return 0;
}

void key(int l, int k, int t) {
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

#include "./HORS.h"

int main() {
  int l = 128;
  int t = 1024;
  int k = 32;
  int b = 8;
  int m = 30;
  int t_array[t];
  int subset[k];
  srand(time(NULL));
  init_t_array(t_array, t);
  int choose = t_choose_k(t,k);
  S(m, k, t, subset);
  key_gen(t, k, l);
  sign("hfeiowaieyabu", t, k);
  if(verify("hfeiowaburiaoieyabu", t, k) == 1){
    printf("Accepted\n");
  } else{
    printf("Rejected\n");
  }
  sign("fneuiabrhbauosefhau", t, k);
  if(verify("fneuiabrhbauosefhau", t, k) == 1){
    printf("Accepted\n");
  } else {
    printf("Rejected\n");
  }
  sign("fneuiabrhbauosefhau", t, k);
  if(verify("hello", t, k) == 1){
    printf("Accepted\n");
  } else {
    printf("Rejected\n");
  }
  return 0;
}

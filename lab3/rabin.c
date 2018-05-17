#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "./vandermonde.h"

void compute_matrix(char* F, int N, int m);
void divide_string(char* F, int size);
int **array2_create(int N, int m);
void createVandermonde(int nx);
void construct_vander_matrix(int N, int m);
char** split = NULL;
char** S = NULL;
char*** M = NULL;
double* A = NULL;
int* input_array = NULL;
int* temp = NULL;


int main() {
  char* F = "testing string for rabin";
  int m = 3;
  int N = strlen(F);
  int nx = N;
  compute_matrix(F, N, m);
  construct_vander_matrix(N, m);
  return 0;
}

void construct_vander_matrix(int N, int m){
  double temp[N];
  double temp2[N];
  for(int i=0; i<N; i++){
    temp[i] = i+1;
    temp2[i] = (i+1)*10;
  }
  A = bivand1(N, temp, temp2);
}

void compute_matrix(char *F, int N, int m) {
  divide_string(F, m);
  S = malloc(sizeof(char*)*(N/m));
  for(int i=1; i<=N/m; i++){
    S[i-1] = malloc(sizeof(char)*m+1);
    strcpy(S[i-1], split[i-1]);
  }
  M = malloc(sizeof(char**)*N/m);
  for(int i=0; i<N/m; i++){
    M[i] = S[i];
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

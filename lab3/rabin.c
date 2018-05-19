#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define M 4
#define N 8
#define L 32

void divide_string(int* s, int size);
void init_F(int F[L]);
void init_mat(int mat[M][L/M], int F[L]);
void print_mat(int mat[M][L/M]);
void init_A(int A[N][M]);
void print_A(int A[N][M]);

int main() {
  int F[L];
  int mat[M][L/M];   //this is a m x n matrix
  int A[N][M];
  int Mult[N][N];
  //inital F values
  disperse(F, A, mat, Mult);
  init_F(F);
  print_F(F);

  //initial matrix
  init_mat(mat, F);
  print_mat(mat);

  //Vandermonde matrix
  init_A(A);
  print_A(A);

  multiply_matrices(A, mat, Mult);
  print_Mult(Mult);


}

void disperse(int F[L], int A[N][M], int mat[M][N], int Mult[N][N]){
  init_F(F);
  init_mat(mat, F);
  init_A(A);
  multiply_matrices(A, mat, Mult);
}

void print_Mult(int Mult[N][N]){
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      printf("%d  ", Mult[i][j]);
    }
    printf("\n");
  }
}

void multiply_matrices(int A[N][M], int mat[M][N], int Mult[N][N]){
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      Mult[i][j] = 0;
      for(int k=0; k<M; k++){
        for(int l=0; l<M; l++){
          Mult[i][j] = A[i][k]*mat[l][j]+Mult[i][j];
        }
      }
    }
  }
}

void init_A(int A[N][M]){
  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      if(j==0){
        A[i][j] = 1;
      } else {
        A[i][j] = pow(i+1, j+1);
      }
    }
  }
}

void print_A(int A[N][M]){
  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      printf("%d  ", A[i][j]);
    }
    printf("\n");
  }
}

void init_F(int F[L]){
  for(int i=0; i<L; i++){
    F[i] = i;
  }
}

void init_mat(int mat[M][L/M], int F[L]){
  for(int i=0; i<M; i++){
    for(int j=0; j<L/M; j++){
      mat[i][j] = F[i*N + j];
    }
  }
}

void print_F(int F[L]){
  for(int i=0; i<L; i++){
    printf("%d ", F[i]);
  }
  printf("\n");
}

void print_mat(int mat[M][L/M]){
  for(int i=0; i<M; i++){
    for(int j=0; j<L/M; j++){
      printf("%d  ", mat[i][j]);
    }
    printf("\n");
  }
}

#ifndef __LIB_DETERMINANT_
#define __LIB_DETERMINANT_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define SIZE 8
//int SIZE = 4;




void find_cofactor(long matrix[SIZE][SIZE], long submatrix[SIZE][SIZE], long subrow, long subcol, long subsize){
    long i = 0;
    long j = 0;
 

    for (long row = 0; row < subsize; row++){
        for (long col = 0; col < subsize; col++){

            if (row != subrow && col != subcol){
                submatrix[i][j++] = matrix[row][col];

                if (j == subsize - 1){
                    j = 0;
                    i++;
                }
            }
        }
    }
}
 

double get_determinant(long matrix[SIZE][SIZE], long subsize){
    double total = 0; 
 

    if (subsize == 1)
        return matrix[0][0];
 
    long submatrix[SIZE][SIZE]; 
 
    long cofactor = 1; 
 

    for (long f = 0; f < subsize; f++){

        find_cofactor(matrix, submatrix, 0, f, subsize);
        total += cofactor * matrix[0][f] * get_determinant(submatrix, subsize - 1);
 

        cofactor *= -1;
    }
 
    return total;
}
 


void print_table(long matrix[SIZE][SIZE]){
    for (long i = 0; i < SIZE; i++){
        for (long j = 0; j < SIZE; j++)
            printf("%ld\t", matrix[i][j]);
        printf("\n");
    }
}


#endif

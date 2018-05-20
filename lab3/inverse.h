#include<stdio.h>
#include "./determinant.h"

 int SIZEMAT = 8;

// matrix is the one that you will give to it, which shouldn't have anything in it, but declared before calling it, so you use the pass by reference to get inverted matrix
void inverseFunc(long mat[SIZEMAT][SIZEMAT], double matrix[SIZEMAT][SIZEMAT]){
    double determinant = 0;
    determinant = get_determinant(mat, SIZEMAT);
    for(int i = 0; i < SIZEMAT; i++){
        for(int j = 0; j < SIZEMAT; j++)
            matrix[j][i] = ((mat[(j+1)%SIZEMAT][(i+1)%SIZEMAT] * mat[(j+2)%SIZEMAT][(i+2)%SIZEMAT]) - (mat[(j+1)%SIZEMAT][(i+2)%SIZEMAT] * mat[(j+2)%SIZEMAT][(i+1)%SIZEMAT]))/ determinant;
    }
}

#include<stdio.h>
#include "./inverse.h"
 // source: https://www.thecrazyprogrammer.com/2017/02/c-c-program-find-inverse-matrix.html
/*double firstHalfDet(long matrix[SIZEMAT][SIZEMAT], int i){
	double firstHalf = 1;
	for(int j=0; j<SIZEMAT; j++){
	firstHalf *= matrix[j][(i+j)%SIZEMAT];
	}
	return firstHalf;
}

double secondHalfDet(long matrix[SIZEMAT][SIZEMAT], int i){
	double secondHalf = 1;
	for(int j=1; j<SIZEMAT; j++){
	secondHalf *= matrix[j][(i+((j*2)%SIZEMAT))%SIZEMAT];
	}
	return secondHalf;
}*/

int main(){
    long mat[SIZEMAT][SIZEMAT], i, j;
    double determinant = 0;
    double matrix[SIZEMAT][SIZEMAT];
    //printf("Enter elements of matrix row wise:\n");
    int counter = 1;
    for(i = 0; i < SIZEMAT; i++){
        for(j = 0; j < SIZEMAT; j++){
	//scanf("%ld", &mat[i][j]);
	mat[i][j] = counter;
	if(i%2 == 0 || j%2==1){
		counter *= 3;
		counter *= -1;
	}
	else if(j%3 == 0 || j%5 == 0){
		counter /= 2;
		counter *= -1;
	}
	else if(j%4 ==0){
		counter *= -1;
		counter -= 1;
	}
	else
		counter += -1;

	}
	if(counter>100000 || counter < -80000){
		counter = counter/13;
	}
}
    
    printf("\nGiven matrix is:");
    for(i = 0; i < SIZEMAT; i++){
        printf("\n");
        
        for(j = 0; j < SIZEMAT; j++)
            printf("%ld\t", mat[i][j]);
    }
    printf("\n");
    //finding determinant
    /*for(i = 0; i < SIZEMAT; i++)
         determinant = determinant + (firstHalfDet(mat, i) - secondHalfDet(mat, i));*/

    //printf("determinant without function: %.10f\n", determinant);
    determinant = get_determinant(mat, SIZEMAT);
    
    printf("\n\ndeterminant: %0.10f\n", determinant);
    inverseFunc(mat, matrix);
    printf("\nInverse of matrix is: \n");
    for(i = 0; i < SIZEMAT; i++){
        for(j = 0; j < SIZEMAT; j++){
            //printf("%.10f\t",((mat[(j+1)%SIZEMAT][(i+1)%SIZEMAT] * mat[(j+2)%SIZEMAT][(i+2)%SIZEMAT]) - (mat[(j+1)%SIZEMAT][(i+2)%SIZEMAT] * mat[(j+2)%SIZEMAT][(i+1)%SIZEMAT]))/ determinant);
		printf("%.10f\t", matrix[i][j]);
        }
        printf("\n");
    }
 
   return 0;
}

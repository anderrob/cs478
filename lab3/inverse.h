#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./determinant.h"

#define SIZE 4 


int i , j , n = SIZE  , row , column ;
double num , det=0 , inverse_matrix[SIZE][SIZE] , matrix[SIZE][SIZE] , new_mat[SIZE][SIZE] , m_minor[SIZE][SIZE] , m_Transpose[SIZE][SIZE];



double Transpose(double input[SIZE][SIZE]);

void invert(double input[SIZE][SIZE], double output[SIZE][SIZE]){   
    double num , det=0 , inverse_matrix[SIZE][SIZE] , matrix[SIZE][SIZE] , new_mat[SIZE][SIZE] , m_minor[SIZE][SIZE] , m_Transpose[SIZE][SIZE];



      det=get_determinant(input, SIZE);
      printf("\nDETERMINANT: %.0f\n", det);

      if( det == 0)
      {
          printf("\n* * * * * * * * * * * * * * * * * * * * * * * *\nINVERSE DOESN'T EXIST\n");
         
          return 0;
      }
      else
      {
          num=1/det;
          m_Transpose[n][n]=Transpose(input);
          printf("\n* * * * * * * * * * * * * * * * * * * * * * * *\nMATRIX INVERSE IS:\n\n");
          /*complex of determinant with Transpose*/
          for(i=1; i<=n; i++)
          {
               for(j=1; j<=n; j++)
               {
                    output[i][j]=num*m_Transpose[i][j];
                    if(output[i][j]>=0)
                        printf("%.10f\t",output[i][j]);
                    else
                        printf("%.10f\t",output[i][j]);
               }
               printf("\n");
          }
      }


}





/*calculate Transpose*/
double Transpose(double input[SIZE][SIZE])
{
    for(int i=1;i<=n;i++)
       for(j=1;j<=n;j++)
          m_Transpose[i][j]=input[j][i];
    return m_Transpose[n][n];
}
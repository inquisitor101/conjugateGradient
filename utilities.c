#include "header.h"
#include "utilities.h"


void printMatrix(numType *A, int m, int n)
{
  printf("\nmatrix: \n" );
  for (int i=0; i<m; i++){
    for (int j=0; j<n; j++){
      printf("%2.2f ", A[i*m+j]);
    }
    printf("\n" );
  }
}


void printVector(numType *x, int n)
{
  printf("\nvector: \n" );
  for (int i=0; i<n; i++){
    printf("%2.2f\n", x[i]);
  }
}

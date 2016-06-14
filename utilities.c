#include "header.h"
#include "utilities.h"


void printMatrix(numType *A, int n)
{
  printf("\nmatrix: \n" );
  for (int i=0; i<n; i++){
    for (int j=0; j<n; j++){
      printf("%2.2f ", A[i*n+j]);
    }
    printf("\n" );
  }
}


void printVector(numType *x, int n)
{
  printf("\nvector: \n" );
  for (int i=0; i<n; i++){
    printf("%e\n", x[i]);
  }
}

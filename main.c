#include "header.h"
#include "funcs.h"
#include "utilities.h"


int main(int argc, char **argv){

  // get dimensions
  int m = atoi(argv[1]); // row size
  int n = atoi(argv[2]); // col size

  // allocate memory
  A  = (numType *)calloc(m*n, sizeof(numType));
  b  = (numType *)calloc(n  , sizeof(numType));
  x  = (numType *)calloc(n  , sizeof(numType));

  // TODO matrix and vector generation
  initialize(A, b, x, m, n);

  // print resulting matrix
  printMatrix(A, m, n);
  // print resulting vector
  printVector(b, n);

  // TODO solve using CG
  // CG(A, b);

  // TODO validate results - residual
  // residualCheck();

  free(A);
  free(b);
  free(x);
  printf("\n");
  return 0;
}

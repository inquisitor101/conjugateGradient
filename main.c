#include "header.h"
#include "funcs.h"
#include "utilities.h"

/* In order to use, compile via make and specify
   the following options for execution:
        ./CG  <n>  <i>  <e>
              where:
                     <n> : dimention number (n-by-n)
                     <i> : maximum iterations
                     <e> : error tolerance

                                                        */

int main(int argc, char **argv){

  // get parameters
  int n = atoi(argv[1]); // row/col size
  int maxIter = atoi(argv[2]);
  double TOL  = atof(argv[3]);

  // allocate memory
  A  = (numType *)calloc(n*n, sizeof(numType)); assert(A != NULL);
  b  = (numType *)calloc(n  , sizeof(numType)); assert(b != NULL);
  x  = (numType *)calloc(n  , sizeof(numType)); assert(x != NULL);
  r  = (numType *)calloc(n  , sizeof(numType)); assert(r != NULL);

  // TODO matrix and vector generation
  initialize(A, b, x, n);

  // TODO solve using steepest descent
  // steepestDescent(A, b, x, r, n, maxIter, TOL);

  // TODO solve using conjugate gradient
  conjGradient(A, b, x, r, n, maxIter, TOL);
  
  // print result
  printVector(x, n);


  free(A);
  free(b);
  free(x);
  free(r);
  printf("\n");
  return 0;
}

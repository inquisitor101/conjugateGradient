#include "header.h"
#include "funcs.h"

void initialize(numType *A, numType *b, numType *x0,
                int m, int n)
{
  /*
    matrix: (m-by-n)             vector: (n-by-1)
                         (n)                         #
                       # # # #                       #
                   (m) # # # #                   (n) #
                       # # # #                       #
                                                    (1)
                                                            */

  // generate data
  for (int i=0; i<m; i++){
    for (int j=0; j<n; j++){
      // range: [-5, +5]
      A[i*m+j] = 10.0*(numType)rand()/RAND_MAX - 5.0;
    }
    // enforce positive definite
    A[i*m+i] += 10.1; // diagonal element dominant
  }
  for (int j=0; j<n; j++){
    // range [0, +5]
    b[j] = 5.0*(numType)rand()/RAND_MAX;
    x0[j] = 1; // starting condition
  }


}

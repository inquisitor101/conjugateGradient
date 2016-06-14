#include "header.h"
#include "funcs.h"

void initialize(numType *A, numType *b, numType *x0,
                int n)
{
  /*
    matrix: (n-by-n)             vector: (n-by-1)
                         (n)                         #
                       # # # #                       #
                   (n) # # # #                   (n) #
                       # # # #                       #
                       # # # #                      (1)
                                                            */

  // generate data
  for (int i=0; i<n; i++){
    for (int j=0; j<n; j++){
      A[i*n+j] = (numType)(i+1)*(numType)(j+1);   // non-diagonal element
    }
    A[i*n+i] += n*n; // diagonal element dominant
    b[i]  = (numType)i+1.0;
    x0[i] = 0.0;
  }

}


void steepestDescent(numType *A, numType *b, numType *x,
                     double *r,
                     int n, int maxIter, double TOL)
{
  residualExact(A, b, x, r, n);
  numType delta = 0.0;

  int i, j, iter = 0;
  double err = 1.0, maxErr;
  numType temp, alpha;
  numType *q = (numType *)calloc(n, sizeof(numType));

  for (i=0; i<n; i++){
    delta += r[i]*r[i];
  }
  maxErr = sqrt(delta)*TOL;

  while (err > maxErr && iter < maxIter){

    for (i=0; i<n; i++){
      temp = 0.0;
      for (j=0; j<n; j++){
        temp += A[i*n+j]*r[j];
      }
      q[i] = temp;
    }

    temp = 0.0;
    for (i=0; i<n; i++){
      temp += r[i]*q[i];
    }

    alpha = delta/temp;
    for (i=0; i<n; i++){
      x[i] = x[i] + alpha*r[i];
    }

    if (iter%50 == 0){
      residualExact(A, b, x, r, n);
    }
    else {
      residualApprox(r, q, alpha, n);
    }

    delta = 0.0;
    for (i=0; i<n; i++){
      delta += r[i]*r[i];
    }
    err = sqrt(alpha);

    // monitor progress
    printf("iteration: %d  \t out of %d, err: %e \t maxErr: %e\n", iter, maxIter, err, maxErr);

    iter++;
  }

}


void residualExact(numType *A, numType *b, numType *x,
                     double *r,
                     int n)
{
  double temp;
  // residual:  r = b - A.x
  for (int i=0; i<n; i++){
    temp = 0.0;
    for (int j=0; j<n; j++){
      temp += A[i*n+j]*x[j];
    }
    r[i] = b[i] - temp;
  }

}

void residualApprox(numType *r, numType *q,
                    numType alpha, int n)
{
  for (int i=0; i<n; i++){
    r[i] = r[i] - alpha*q[i];
  }

}

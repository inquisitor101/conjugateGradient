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
    A[i*n+i] += (n+1)*(n+1); // diagonal element dominant
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
  double maxErr;
  numType temp, alpha;
  numType *q = (numType *)calloc(n, sizeof(numType));
  // calculate the residual
  for (i=0; i<n; i++){
    delta += r[i]*r[i];
  }
  maxErr = TOL*TOL*delta; // residual norm_2

  // iterate until convergence or threshold met
  while (delta > maxErr && iter < maxIter){
    // get q = A*r
    for (i=0; i<n; i++){
      temp = 0.0;
      for (j=0; j<n; j++){
        temp += A[i*n+j]*r[j];
      }
      q[i] = temp;
    }
    // get alpha = delta / (r' * q)
    temp = 0.0;
    for (i=0; i<n; i++){
      temp += r[i]*q[i];
    }
    alpha = delta/temp;
    // get solution x = x + alpha*r
    for (i=0; i<n; i++){
      x[i] += alpha*r[i];
    }
    // residual computation, approx or exact..,
    if (iter%50 == 0){
      residualExact(A, b, x, r, n);
    }
    else {
      residualApprox(r, q, alpha, n);
    }
    // update delta = r' * r
    delta = 0.0;
    for (i=0; i<n; i++){
      delta += r[i]*r[i];
    }

    // monitor progress
    printf("iteration: %d  \t out of %d, err: %e \t maxErr: %e\n", iter, maxIter, delta, maxErr);

    iter++;
  }
  // free memory
  free(q);
}


void conjGradient(numType *A, numType *b, numType *x,
                  double *r,
                  int n, int maxIter, double TOL)
{
  residualExact(A, b, x, r, n);
  numType delta_new = 0.0, delta_old = 0.0;

  int i, j, iter = 0;
  double maxErr;
  numType temp, alpha, beta;
  numType *q = (numType *)calloc(n, sizeof(numType));
  numType *d = (numType *)calloc(n, sizeof(numType));
  // calculate the residual
  for (i=0; i<n; i++){
    delta_new += r[i]*r[i];
  }
  maxErr = TOL*TOL*delta_new; // residual norm_2

  // copy r to d
  memcpy(d, r, n*sizeof(numType));

  // iterate until convergence or threshold met
  while (delta_new > maxErr && iter < maxIter){

    // get q = A*d
    for (i=0; i<n; i++){
      temp = 0.0;
      for (j=0; j<n; j++){
        temp += A[i*n+j]*d[j];
      }
      q[i] = temp;
    }

    // compute alpha = delta_new / ( d' * q )
    temp = 0.0;
    for (i=0; i<n; i++){
      temp += d[i]*q[i];
    }
    alpha = delta_new/temp;

    // update solution x = x + alpha*d
    for (i=0; i<n; i++){
      x[i] += alpha*d[i];
    }

    // residual computation, approx or exact..,
    if (iter%50 == 0){
      residualExact(A, b, x, r, n);
    }
    else {
      residualApprox(r, q, alpha, n);
    }

    // update delta_old
    delta_old = delta_new;

    // update delta_new
    delta_new = 0.0;
    for (i=0; i<n; i++){
      delta_new += r[i]*r[i];
    }

    // get beta = delta_new/delta_old
    beta = delta_new/delta_old;

    // update d = r + beta*d
    for (i=0; i<n; i++){
      d[i] = r[i] + beta*d[i];
    }

    // monitor progress
    printf("iteration: %d  \t out of %d, err: %e \t maxErr: %e\n", iter, maxIter, delta_new, maxErr);

    iter++;
  }

  free(q);
  free(d);
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

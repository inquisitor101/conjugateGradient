#ifndef _FUNCS_H
#define _FUNCS_H


void initialize(numType *A, numType *b, numType *x0,
                int n);

void steepestDescent(numType *A, numType *b, numType *x,
                     double *r,
                     int n, int maxIter, double TOL);

void residualExact(numType *A, numType *b, numType *x,
                   double *r,
                   int n);

void residualApprox(numType *r, numType *q,
                    numType alpha, int n);


#endif

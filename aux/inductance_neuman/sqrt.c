/*
 * File: sqrt.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 15-May-2017 14:17:50
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "inductance_neuman.h"
#include "sqrt.h"

/* Function Definitions */

/*
 * Arguments    : double x[1000]
 * Return Type  : void
 */
void b_sqrt(double x[1000])
{
  int k;
  for (k = 0; k < 1000; k++) {
    x[k] = sqrt(x[k]);
  }
}

/*
 * Arguments    : emxArray_real_T *x
 * Return Type  : void
 */
void c_sqrt(emxArray_real_T *x)
{
  int nx;
  int k;
  nx = x->size[1];
  for (k = 0; k + 1 <= nx; k++) {
    x->data[k] = sqrt(x->data[k]);
  }
}

/*
 * File trailer for sqrt.c
 *
 * [EOF]
 */

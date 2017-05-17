/*
 * File: sum.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 17-May-2017 11:29:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "inductance_neuman.h"
#include "sum.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 * Return Type  : double
 */
double sum(const emxArray_real_T *x)
{
  double y;
  int k;
  if (x->size[1] == 0) {
    y = 0.0;
  } else {
    y = x->data[0];
    for (k = 2; k <= x->size[1]; k++) {
      y += x->data[k - 1];
    }
  }

  return y;
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */

/*
 * File: power.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 15-May-2017 14:17:50
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "inductance_neuman.h"
#include "power.h"
#include "inductance_neuman_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *a
 *                emxArray_real_T *y
 * Return Type  : void
 */
void b_power(const emxArray_real_T *a, emxArray_real_T *y)
{
  int k;
  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = a->size[1];
  emxEnsureCapacity((emxArray__common *)y, k, (int)sizeof(double));
  for (k = 0; k + 1 <= a->size[1]; k++) {
    y->data[k] = a->data[k] * a->data[k];
  }
}

/*
 * Arguments    : const double a[1000]
 *                double y[1000]
 * Return Type  : void
 */
void power(const double a[1000], double y[1000])
{
  int k;
  for (k = 0; k < 1000; k++) {
    y[k] = a[k] * a[k];
  }
}

/*
 * File trailer for power.c
 *
 * [EOF]
 */

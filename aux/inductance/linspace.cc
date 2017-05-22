/*
 * File: linspace.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 17-May-2017 11:29:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "inductance_neuman.h"
#include "linspace.h"
#include "inductance_neuman_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : double d2
 *                double n1
 *                emxArray_real_T *y
 * Return Type  : void
 */
void linspace(double d2, double n1, emxArray_real_T *y)
{
  int i1;
  double delta1;
  int k;
  if (n1 < 0.0) {
    n1 = 0.0;
  }

  i1 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = (int)floor(n1);
  emxEnsureCapacity((emxArray__common *)y, i1, (int)sizeof(double));
  if (y->size[1] >= 1) {
    y->data[y->size[1] - 1] = d2;
    if (y->size[1] >= 2) {
      y->data[0] = 0.0;
      if (y->size[1] >= 3) {
        if ((d2 < 0.0) && (fabs(d2) > 8.9884656743115785E+307)) {
          delta1 = d2 / ((double)y->size[1] - 1.0);
          i1 = y->size[1];
          for (k = 0; k <= i1 - 3; k++) {
            y->data[1 + k] = delta1 * (1.0 + (double)k);
          }
        } else {
          delta1 = d2 / ((double)y->size[1] - 1.0);
          i1 = y->size[1];
          for (k = 0; k <= i1 - 3; k++) {
            y->data[1 + k] = (1.0 + (double)k) * delta1;
          }
        }
      }
    }
  }
}

/*
 * File trailer for linspace.c
 *
 * [EOF]
 */

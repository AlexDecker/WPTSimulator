/*
 * File: rdivide.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 15-May-2017 14:17:50
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "inductance_neuman.h"
#include "rdivide.h"
#include "inductance_neuman_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                const emxArray_real_T *y
 *                emxArray_real_T *z
 * Return Type  : void
 */
void rdivide(const emxArray_real_T *x, const emxArray_real_T *y, emxArray_real_T
             *z)
{
  int i1;
  int loop_ub;
  i1 = z->size[0] * z->size[1];
  z->size[0] = 1;
  z->size[1] = x->size[1];
  emxEnsureCapacity((emxArray__common *)z, i1, (int)sizeof(double));
  loop_ub = x->size[0] * x->size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    z->data[i1] = x->data[i1] / y->data[i1];
  }
}

/*
 * File trailer for rdivide.c
 *
 * [EOF]
 */

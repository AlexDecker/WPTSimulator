/*
 * File: diff.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 15-May-2017 14:17:50
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "inductance_neuman.h"
#include "diff.h"
#include "inductance_neuman_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void b_diff(const emxArray_real_T *x, emxArray_real_T *y)
{
  int iyLead;
  int orderForDim;
  double work_data_idx_0;
  int m;
  double tmp1;
  double tmp2;
  if (x->size[1] == 0) {
    iyLead = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 0;
    emxEnsureCapacity((emxArray__common *)y, iyLead, (int)sizeof(double));
  } else {
    if (x->size[1] - 1 <= 1) {
      orderForDim = x->size[1] - 1;
    } else {
      orderForDim = 1;
    }

    if (orderForDim < 1) {
      iyLead = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = 0;
      emxEnsureCapacity((emxArray__common *)y, iyLead, (int)sizeof(double));
    } else {
      orderForDim = x->size[1] - 1;
      iyLead = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = orderForDim;
      emxEnsureCapacity((emxArray__common *)y, iyLead, (int)sizeof(double));
      if (!(y->size[1] == 0)) {
        orderForDim = 1;
        iyLead = 0;
        work_data_idx_0 = x->data[0];
        for (m = 2; m <= x->size[1]; m++) {
          tmp1 = x->data[orderForDim];
          tmp2 = work_data_idx_0;
          work_data_idx_0 = tmp1;
          tmp1 -= tmp2;
          orderForDim++;
          y->data[iyLead] = tmp1;
          iyLead++;
        }
      }
    }
  }
}

/*
 * Arguments    : const double x[1001]
 *                double y[1000]
 * Return Type  : void
 */
void diff(const double x[1001], double y[1000])
{
  int ixLead;
  int iyLead;
  double work;
  int m;
  double tmp2;
  ixLead = 1;
  iyLead = 0;
  work = x[0];
  for (m = 0; m < 1000; m++) {
    tmp2 = work;
    work = x[ixLead];
    tmp2 = x[ixLead] - tmp2;
    ixLead++;
    y[iyLead] = tmp2;
    iyLead++;
  }
}

/*
 * File trailer for diff.c
 *
 * [EOF]
 */

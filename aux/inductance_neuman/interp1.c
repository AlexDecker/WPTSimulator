/*
 * File: interp1.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 15-May-2017 14:17:50
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "inductance_neuman.h"
#include "interp1.h"
#include "inductance_neuman_emxutil.h"

/* Function Definitions */

/*
 * Arguments    : const double varargin_1[1001]
 *                const double varargin_2[1001]
 *                const emxArray_real_T *varargin_3
 *                emxArray_real_T *Vq
 * Return Type  : void
 */
void interp1(const double varargin_1[1001], const double varargin_2[1001], const
             emxArray_real_T *varargin_3, emxArray_real_T *Vq)
{
  double y[1001];
  double x[1001];
  unsigned int outsize[2];
  int k;
  int low_i;
  int exitg1;
  double r;
  int low_ip1;
  int high_i;
  int mid_i;
  memcpy(&y[0], &varargin_2[0], 1001U * sizeof(double));
  memcpy(&x[0], &varargin_1[0], 1001U * sizeof(double));
  for (k = 0; k < 2; k++) {
    outsize[k] = (unsigned int)varargin_3->size[k];
  }

  k = Vq->size[0] * Vq->size[1];
  Vq->size[0] = 1;
  Vq->size[1] = (int)outsize[1];
  emxEnsureCapacity((emxArray__common *)Vq, k, (int)sizeof(double));
  low_i = (int)outsize[1];
  for (k = 0; k < low_i; k++) {
    Vq->data[k] = rtNaN;
  }

  if (varargin_3->size[1] == 0) {
  } else {
    k = 1;
    do {
      exitg1 = 0;
      if (k < 1002) {
        if (rtIsNaN(varargin_1[k - 1])) {
          exitg1 = 1;
        } else {
          k++;
        }
      } else {
        if (varargin_1[1] < varargin_1[0]) {
          for (k = 0; k < 500; k++) {
            r = x[k];
            x[k] = x[1000 - k];
            x[1000 - k] = r;
            r = y[k];
            y[k] = y[1000 - k];
            y[1000 - k] = r;
          }
        }

        for (k = 0; k + 1 <= varargin_3->size[1]; k++) {
          r = Vq->data[k];
          if (rtIsNaN(varargin_3->data[k])) {
            r = rtNaN;
          } else if ((varargin_3->data[k] > x[1000]) || (varargin_3->data[k] <
                      x[0])) {
          } else {
            low_i = 1;
            low_ip1 = 2;
            high_i = 1001;
            while (high_i > low_ip1) {
              mid_i = (low_i + high_i) >> 1;
              if (varargin_3->data[k] >= x[mid_i - 1]) {
                low_i = mid_i;
                low_ip1 = mid_i + 1;
              } else {
                high_i = mid_i;
              }
            }

            r = (varargin_3->data[k] - x[low_i - 1]) / (x[low_i] - x[low_i - 1]);
            if (r == 0.0) {
              r = y[low_i - 1];
            } else if (r == 1.0) {
              r = y[low_i];
            } else if (y[low_i - 1] == y[low_i]) {
              r = y[low_i - 1];
            } else {
              r = (1.0 - r) * y[low_i - 1] + r * y[low_i];
            }
          }

          Vq->data[k] = r;
        }

        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
}

/*
 * File trailer for interp1.c
 *
 * [EOF]
 */

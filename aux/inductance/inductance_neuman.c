/*
 * File: inductance_neuman.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 17-May-2017 11:29:01
 * Mutual coupling without permeability and 1/4pi factors
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "inductance_neuman.h"
#include "inductance_neuman_emxutil.h"
#include "rdivide.h"
#include "sqrt.h"
#include "power.h"
#include "sum.h"
#include "diff.h"
#include "interp1.h"
#include "linspace.h"

/* Function Declarations */
static double rt_roundd_snf(double u);

/* Function Definitions */

/*
 * Arguments    : double u
 * Return Type  : double
 */
static double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/*
 * mutual inductance of two contours
 *  conturs are polygones in 3d
 *  contour 1 vertecies: x1 y1 z1
 *  contour 2 vertecies: x1 y1 z1
 *  Neuman formaula was used:
 *  http://en.wikipedia.org/wiki/Inductance#Mutual_inductance_of_two_wire_loops
 * Arguments    : const emxArray_real_T *x1
 *                const emxArray_real_T *b_y1
 *                const emxArray_real_T *z1
 *                const emxArray_real_T *x2
 *                const emxArray_real_T *y2
 *                const emxArray_real_T *z2
 * Return Type  : double
 */
double inductance_neuman(const emxArray_real_T *x1, const emxArray_real_T *b_y1,
  const emxArray_real_T *z1, const emxArray_real_T *x2, const emxArray_real_T
  *y2, const emxArray_real_T *z2)
{
  double L;
  int ixstart;
  int n;
  double mtmp;
  int ix;
  boolean_T exitg14;
  double b_mtmp;
  boolean_T exitg13;
  double c_mtmp;
  boolean_T exitg12;
  double d_mtmp;
  boolean_T exitg11;
  double e_mtmp;
  boolean_T exitg10;
  double f_mtmp;
  boolean_T exitg9;
  double g_mtmp;
  boolean_T exitg8;
  double h_mtmp;
  boolean_T exitg7;
  double i_mtmp;
  boolean_T exitg6;
  double j_mtmp;
  boolean_T exitg5;
  double k_mtmp;
  boolean_T exitg4;
  double l_mtmp;
  double varargin_1[3];
  boolean_T exitg3;
  boolean_T exitg2;
  boolean_T exitg1;
  emxArray_real_T *xe;
  emxArray_real_T *ye;
  emxArray_real_T *ze;
  emxArray_real_T *dx;
  emxArray_real_T *dy;
  emxArray_real_T *dz;
  emxArray_real_T *dL;
  emxArray_real_T *r0;
  emxArray_real_T *r1;
  emxArray_real_T *dxi;
  emxArray_real_T *dyi;
  emxArray_real_T *dzi;
  emxArray_real_T *xim;
  emxArray_real_T *yim;
  emxArray_real_T *zim;
  emxArray_real_T *yi2;
  emxArray_real_T *zi2;
  emxArray_real_T *dzi2;
  int cc;
  emxArray_real_T *b_dxi;
  emxArray_real_T *b_zim;
  emxArray_real_T *b_yim;
  emxArray_real_T *b_xim;

  /*  high scale factor, dge*hsf is step in current discretization */
  /*  limits: */
  ixstart = 1;
  n = x1->size[1];
  mtmp = x1->data[0];
  if (x1->size[1] > 1) {
    if (rtIsNaN(x1->data[0])) {
      ix = 2;
      exitg14 = false;
      while ((!exitg14) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(x1->data[ix - 1])) {
          mtmp = x1->data[ix - 1];
          exitg14 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < x1->size[1]) {
      while (ixstart + 1 <= n) {
        if (x1->data[ixstart] < mtmp) {
          mtmp = x1->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  ixstart = 1;
  n = x1->size[1];
  b_mtmp = x1->data[0];
  if (x1->size[1] > 1) {
    if (rtIsNaN(x1->data[0])) {
      ix = 2;
      exitg13 = false;
      while ((!exitg13) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(x1->data[ix - 1])) {
          b_mtmp = x1->data[ix - 1];
          exitg13 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < x1->size[1]) {
      while (ixstart + 1 <= n) {
        if (x1->data[ixstart] > b_mtmp) {
          b_mtmp = x1->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  ixstart = 1;
  n = b_y1->size[1];
  c_mtmp = b_y1->data[0];
  if (b_y1->size[1] > 1) {
    if (rtIsNaN(b_y1->data[0])) {
      ix = 2;
      exitg12 = false;
      while ((!exitg12) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(b_y1->data[ix - 1])) {
          c_mtmp = b_y1->data[ix - 1];
          exitg12 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < b_y1->size[1]) {
      while (ixstart + 1 <= n) {
        if (b_y1->data[ixstart] < c_mtmp) {
          c_mtmp = b_y1->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  ixstart = 1;
  n = b_y1->size[1];
  d_mtmp = b_y1->data[0];
  if (b_y1->size[1] > 1) {
    if (rtIsNaN(b_y1->data[0])) {
      ix = 2;
      exitg11 = false;
      while ((!exitg11) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(b_y1->data[ix - 1])) {
          d_mtmp = b_y1->data[ix - 1];
          exitg11 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < b_y1->size[1]) {
      while (ixstart + 1 <= n) {
        if (b_y1->data[ixstart] > d_mtmp) {
          d_mtmp = b_y1->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  ixstart = 1;
  n = z1->size[1];
  e_mtmp = z1->data[0];
  if (z1->size[1] > 1) {
    if (rtIsNaN(z1->data[0])) {
      ix = 2;
      exitg10 = false;
      while ((!exitg10) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(z1->data[ix - 1])) {
          e_mtmp = z1->data[ix - 1];
          exitg10 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < z1->size[1]) {
      while (ixstart + 1 <= n) {
        if (z1->data[ixstart] < e_mtmp) {
          e_mtmp = z1->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  ixstart = 1;
  n = z1->size[1];
  f_mtmp = z1->data[0];
  if (z1->size[1] > 1) {
    if (rtIsNaN(z1->data[0])) {
      ix = 2;
      exitg9 = false;
      while ((!exitg9) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(z1->data[ix - 1])) {
          f_mtmp = z1->data[ix - 1];
          exitg9 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < z1->size[1]) {
      while (ixstart + 1 <= n) {
        if (z1->data[ixstart] > f_mtmp) {
          f_mtmp = z1->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  ixstart = 1;
  n = x2->size[1];
  g_mtmp = x2->data[0];
  if (x2->size[1] > 1) {
    if (rtIsNaN(x2->data[0])) {
      ix = 2;
      exitg8 = false;
      while ((!exitg8) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(x2->data[ix - 1])) {
          g_mtmp = x2->data[ix - 1];
          exitg8 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < x2->size[1]) {
      while (ixstart + 1 <= n) {
        if (x2->data[ixstart] < g_mtmp) {
          g_mtmp = x2->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  ixstart = 1;
  n = x2->size[1];
  h_mtmp = x2->data[0];
  if (x2->size[1] > 1) {
    if (rtIsNaN(x2->data[0])) {
      ix = 2;
      exitg7 = false;
      while ((!exitg7) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(x2->data[ix - 1])) {
          h_mtmp = x2->data[ix - 1];
          exitg7 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < x2->size[1]) {
      while (ixstart + 1 <= n) {
        if (x2->data[ixstart] > h_mtmp) {
          h_mtmp = x2->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  ixstart = 1;
  n = y2->size[1];
  i_mtmp = y2->data[0];
  if (y2->size[1] > 1) {
    if (rtIsNaN(y2->data[0])) {
      ix = 2;
      exitg6 = false;
      while ((!exitg6) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(y2->data[ix - 1])) {
          i_mtmp = y2->data[ix - 1];
          exitg6 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < y2->size[1]) {
      while (ixstart + 1 <= n) {
        if (y2->data[ixstart] < i_mtmp) {
          i_mtmp = y2->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  ixstart = 1;
  n = y2->size[1];
  j_mtmp = y2->data[0];
  if (y2->size[1] > 1) {
    if (rtIsNaN(y2->data[0])) {
      ix = 2;
      exitg5 = false;
      while ((!exitg5) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(y2->data[ix - 1])) {
          j_mtmp = y2->data[ix - 1];
          exitg5 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < y2->size[1]) {
      while (ixstart + 1 <= n) {
        if (y2->data[ixstart] > j_mtmp) {
          j_mtmp = y2->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  ixstart = 1;
  n = z2->size[1];
  k_mtmp = z2->data[0];
  if (z2->size[1] > 1) {
    if (rtIsNaN(z2->data[0])) {
      ix = 2;
      exitg4 = false;
      while ((!exitg4) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(z2->data[ix - 1])) {
          k_mtmp = z2->data[ix - 1];
          exitg4 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < z2->size[1]) {
      while (ixstart + 1 <= n) {
        if (z2->data[ixstart] < k_mtmp) {
          k_mtmp = z2->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  ixstart = 1;
  n = z2->size[1];
  l_mtmp = z2->data[0];
  if (z2->size[1] > 1) {
    if (rtIsNaN(z2->data[0])) {
      ix = 2;
      exitg3 = false;
      while ((!exitg3) && (ix <= n)) {
        ixstart = ix;
        if (!rtIsNaN(z2->data[ix - 1])) {
          l_mtmp = z2->data[ix - 1];
          exitg3 = true;
        } else {
          ix++;
        }
      }
    }

    if (ixstart < z2->size[1]) {
      while (ixstart + 1 <= n) {
        if (z2->data[ixstart] > l_mtmp) {
          l_mtmp = z2->data[ixstart];
        }

        ixstart++;
      }
    }
  }

  varargin_1[0] = b_mtmp - mtmp;
  varargin_1[1] = d_mtmp - c_mtmp;
  varargin_1[2] = f_mtmp - e_mtmp;
  ixstart = 1;
  mtmp = varargin_1[0];
  if (rtIsNaN(varargin_1[0])) {
    ix = 2;
    exitg2 = false;
    while ((!exitg2) && (ix < 4)) {
      ixstart = ix;
      if (!rtIsNaN(varargin_1[ix - 1])) {
        mtmp = varargin_1[ix - 1];
        exitg2 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 3) {
    while (ixstart + 1 < 4) {
      if (varargin_1[ixstart] > mtmp) {
        mtmp = varargin_1[ixstart];
      }

      ixstart++;
    }
  }

  /*  maximal size of first contour */
  varargin_1[0] = h_mtmp - g_mtmp;
  varargin_1[1] = j_mtmp - i_mtmp;
  varargin_1[2] = l_mtmp - k_mtmp;
  ixstart = 1;
  b_mtmp = varargin_1[0];
  if (rtIsNaN(varargin_1[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 4)) {
      ixstart = ix;
      if (!rtIsNaN(varargin_1[ix - 1])) {
        b_mtmp = varargin_1[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 3) {
    while (ixstart + 1 < 4) {
      if (varargin_1[ixstart] > b_mtmp) {
        b_mtmp = varargin_1[ixstart];
      }

      ixstart++;
    }
  }

  emxInit_real_T(&xe, 2);

  /*  maximal size of second contour */
  /*  discretization of first contour: */
  n = xe->size[0] * xe->size[1];
  xe->size[0] = 1;
  xe->size[1] = x1->size[1] + 1;
  emxEnsureCapacity((emxArray__common *)xe, n, (int)sizeof(double));
  ix = x1->size[1];
  for (n = 0; n < ix; n++) {
    xe->data[xe->size[0] * n] = x1->data[x1->size[0] * n];
  }

  emxInit_real_T(&ye, 2);
  xe->data[xe->size[0] * x1->size[1]] = x1->data[0];
  n = ye->size[0] * ye->size[1];
  ye->size[0] = 1;
  ye->size[1] = b_y1->size[1] + 1;
  emxEnsureCapacity((emxArray__common *)ye, n, (int)sizeof(double));
  ix = b_y1->size[1];
  for (n = 0; n < ix; n++) {
    ye->data[ye->size[0] * n] = b_y1->data[b_y1->size[0] * n];
  }

  emxInit_real_T(&ze, 2);
  ye->data[ye->size[0] * b_y1->size[1]] = b_y1->data[0];
  n = ze->size[0] * ze->size[1];
  ze->size[0] = 1;
  ze->size[1] = z1->size[1] + 1;
  emxEnsureCapacity((emxArray__common *)ze, n, (int)sizeof(double));
  ix = z1->size[1];
  for (n = 0; n < ix; n++) {
    ze->data[ze->size[0] * n] = z1->data[z1->size[0] * n];
  }

  emxInit_real_T(&dx, 2);
  emxInit_real_T(&dy, 2);
  emxInit_real_T(&dz, 2);
  emxInit_real_T(&dL, 2);
  emxInit_real_T(&r0, 2);
  emxInit_real_T(&r1, 2);
  ze->data[ze->size[0] * z1->size[1]] = z1->data[0];
  diff(xe, dx);
  diff(ye, dy);
  diff(ze, dz);
  power(dx, dL);
  power(dy, r0);
  power(dz, r1);
  n = dL->size[0] * dL->size[1];
  dL->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)dL, n, (int)sizeof(double));
  ixstart = dL->size[0];
  n = dL->size[1];
  ix = ixstart * n;
  for (n = 0; n < ix; n++) {
    dL->data[n] = (dL->data[n] + r0->data[n]) + r1->data[n];
  }

  b_sqrt(dL);
  n = dz->size[0] * dz->size[1];
  dz->size[0] = 1;
  dz->size[1] = dL->size[1];
  emxEnsureCapacity((emxArray__common *)dz, n, (int)sizeof(double));
  ix = dL->size[0] * dL->size[1];
  for (n = 0; n < ix; n++) {
    dz->data[n] = dL->data[n];
  }

  if ((!(dL->size[1] == 0)) && (dL->size[1] > 1)) {
    for (ixstart = 1; ixstart < dL->size[1]; ixstart++) {
      dz->data[ixstart] += dz->data[ixstart - 1];
    }
  }

  /*  total length */
  n = dx->size[0] * dx->size[1];
  dx->size[0] = 1;
  dx->size[1] = 1 + dz->size[1];
  emxEnsureCapacity((emxArray__common *)dx, n, (int)sizeof(double));
  dx->data[0] = 0.0;
  ix = dz->size[1];
  for (n = 0; n < ix; n++) {
    dx->data[dx->size[0] * (n + 1)] = dz->data[dz->size[0] * n];
  }

  emxInit_real_T(&dxi, 2);
  emxInit_real_T(&dyi, 2);
  emxInit_real_T(&dzi, 2);

  /* t=0:dt:cLend; */
  linspace(dz->data[dz->size[1] - 1], rt_roundd_snf(dz->data[dz->size[1] - 1] /
            (0.002 * mtmp)), dy);

  /*  closed */
  interp1(dx, xe, dy, dz);
  interp1(dx, ye, dy, dL);

  /*  current discretization points */
  interp1(dx, ze, dy, xe);

  /*  current discretization points */
  diff(dz, dxi);
  diff(dL, dyi);
  diff(xe, dzi);
  power(dxi, dx);
  power(dyi, r0);
  power(dzi, r1);
  n = dx->size[0] * dx->size[1];
  dx->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)dx, n, (int)sizeof(double));
  ixstart = dx->size[0];
  n = dx->size[1];
  ix = ixstart * n;
  for (n = 0; n < ix; n++) {
    dx->data[n] = (dx->data[n] + r0->data[n]) + r1->data[n];
  }

  b_sqrt(dx);

  /*  mean points: */
  if (1 > dz->size[1] - 1) {
    ix = 0;
  } else {
    ix = dz->size[1] - 1;
  }

  if (2 > dz->size[1]) {
    n = 0;
  } else {
    n = 1;
  }

  emxInit_real_T(&xim, 2);
  ixstart = xim->size[0] * xim->size[1];
  xim->size[0] = 1;
  xim->size[1] = ix;
  emxEnsureCapacity((emxArray__common *)xim, ixstart, (int)sizeof(double));
  for (ixstart = 0; ixstart < ix; ixstart++) {
    xim->data[xim->size[0] * ixstart] = (dz->data[ixstart] + dz->data[n +
      ixstart]) / 2.0;
  }

  if (1 > dL->size[1] - 1) {
    ix = 0;
  } else {
    ix = dL->size[1] - 1;
  }

  if (2 > dL->size[1]) {
    n = 0;
  } else {
    n = 1;
  }

  emxInit_real_T(&yim, 2);
  ixstart = yim->size[0] * yim->size[1];
  yim->size[0] = 1;
  yim->size[1] = ix;
  emxEnsureCapacity((emxArray__common *)yim, ixstart, (int)sizeof(double));
  for (ixstart = 0; ixstart < ix; ixstart++) {
    yim->data[yim->size[0] * ixstart] = (dL->data[ixstart] + dL->data[n +
      ixstart]) / 2.0;
  }

  if (1 > xe->size[1] - 1) {
    ix = 0;
  } else {
    ix = xe->size[1] - 1;
  }

  if (2 > xe->size[1]) {
    n = 0;
  } else {
    n = 1;
  }

  emxInit_real_T(&zim, 2);
  ixstart = zim->size[0] * zim->size[1];
  zim->size[0] = 1;
  zim->size[1] = ix;
  emxEnsureCapacity((emxArray__common *)zim, ixstart, (int)sizeof(double));
  for (ixstart = 0; ixstart < ix; ixstart++) {
    zim->data[zim->size[0] * ixstart] = (xe->data[ixstart] + xe->data[n +
      ixstart]) / 2.0;
  }

  /*  discretization of second contour: */
  n = xe->size[0] * xe->size[1];
  xe->size[0] = 1;
  xe->size[1] = x2->size[1] + 1;
  emxEnsureCapacity((emxArray__common *)xe, n, (int)sizeof(double));
  ix = x2->size[1];
  for (n = 0; n < ix; n++) {
    xe->data[xe->size[0] * n] = x2->data[x2->size[0] * n];
  }

  xe->data[xe->size[0] * x2->size[1]] = x2->data[0];
  n = ye->size[0] * ye->size[1];
  ye->size[0] = 1;
  ye->size[1] = y2->size[1] + 1;
  emxEnsureCapacity((emxArray__common *)ye, n, (int)sizeof(double));
  ix = y2->size[1];
  for (n = 0; n < ix; n++) {
    ye->data[ye->size[0] * n] = y2->data[y2->size[0] * n];
  }

  ye->data[ye->size[0] * y2->size[1]] = y2->data[0];
  n = ze->size[0] * ze->size[1];
  ze->size[0] = 1;
  ze->size[1] = z2->size[1] + 1;
  emxEnsureCapacity((emxArray__common *)ze, n, (int)sizeof(double));
  ix = z2->size[1];
  for (n = 0; n < ix; n++) {
    ze->data[ze->size[0] * n] = z2->data[z2->size[0] * n];
  }

  ze->data[ze->size[0] * z2->size[1]] = z2->data[0];
  diff(xe, dx);
  diff(ye, dy);
  diff(ze, dz);
  power(dx, dL);
  power(dy, r0);
  power(dz, r1);
  n = dL->size[0] * dL->size[1];
  dL->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)dL, n, (int)sizeof(double));
  ixstart = dL->size[0];
  n = dL->size[1];
  ix = ixstart * n;
  for (n = 0; n < ix; n++) {
    dL->data[n] = (dL->data[n] + r0->data[n]) + r1->data[n];
  }

  b_sqrt(dL);
  n = dz->size[0] * dz->size[1];
  dz->size[0] = 1;
  dz->size[1] = dL->size[1];
  emxEnsureCapacity((emxArray__common *)dz, n, (int)sizeof(double));
  ix = dL->size[0] * dL->size[1];
  for (n = 0; n < ix; n++) {
    dz->data[n] = dL->data[n];
  }

  if ((!(dL->size[1] == 0)) && (dL->size[1] > 1)) {
    for (ixstart = 1; ixstart < dL->size[1]; ixstart++) {
      dz->data[ixstart] += dz->data[ixstart - 1];
    }
  }

  /*  total length */
  n = dx->size[0] * dx->size[1];
  dx->size[0] = 1;
  dx->size[1] = 1 + dz->size[1];
  emxEnsureCapacity((emxArray__common *)dx, n, (int)sizeof(double));
  dx->data[0] = 0.0;
  ix = dz->size[1];
  for (n = 0; n < ix; n++) {
    dx->data[dx->size[0] * (n + 1)] = dz->data[dz->size[0] * n];
  }

  emxInit_real_T(&yi2, 2);
  emxInit_real_T(&zi2, 2);
  emxInit_real_T(&dzi2, 2);

  /* t=0:dt:cLend; */
  linspace(dz->data[dz->size[1] - 1], rt_roundd_snf(dz->data[dz->size[1] - 1] /
            (0.002 * b_mtmp)), dy);

  /*  closed */
  interp1(dx, xe, dy, dz);
  interp1(dx, ye, dy, yi2);

  /*  current discretization points */
  interp1(dx, ze, dy, zi2);

  /*  current discretization points */
  diff(dz, ye);
  diff(yi2, ze);
  diff(zi2, dzi2);
  power(ye, dx);
  power(ze, r0);
  power(dzi2, r1);
  n = dx->size[0] * dx->size[1];
  dx->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)dx, n, (int)sizeof(double));
  ixstart = dx->size[0];
  n = dx->size[1];
  ix = ixstart * n;
  for (n = 0; n < ix; n++) {
    dx->data[n] = (dx->data[n] + r0->data[n]) + r1->data[n];
  }

  b_sqrt(dx);

  /*  mean points: */
  if (1 > dz->size[1] - 1) {
    ix = 0;
  } else {
    ix = dz->size[1] - 1;
  }

  if (2 > dz->size[1]) {
    n = 0;
  } else {
    n = 1;
  }

  ixstart = xe->size[0] * xe->size[1];
  xe->size[0] = 1;
  xe->size[1] = ix;
  emxEnsureCapacity((emxArray__common *)xe, ixstart, (int)sizeof(double));
  for (ixstart = 0; ixstart < ix; ixstart++) {
    xe->data[xe->size[0] * ixstart] = (dz->data[ixstart] + dz->data[n + ixstart])
      / 2.0;
  }

  if (1 > yi2->size[1] - 1) {
    ix = 0;
  } else {
    ix = yi2->size[1] - 1;
  }

  if (2 > yi2->size[1]) {
    n = 0;
  } else {
    n = 1;
  }

  ixstart = dL->size[0] * dL->size[1];
  dL->size[0] = 1;
  dL->size[1] = ix;
  emxEnsureCapacity((emxArray__common *)dL, ixstart, (int)sizeof(double));
  for (ixstart = 0; ixstart < ix; ixstart++) {
    dL->data[dL->size[0] * ixstart] = (yi2->data[ixstart] + yi2->data[n +
      ixstart]) / 2.0;
  }

  emxFree_real_T(&yi2);
  if (1 > zi2->size[1] - 1) {
    ix = 0;
  } else {
    ix = zi2->size[1] - 1;
  }

  if (2 > zi2->size[1]) {
    n = 0;
  } else {
    n = 1;
  }

  ixstart = dz->size[0] * dz->size[1];
  dz->size[0] = 1;
  dz->size[1] = ix;
  emxEnsureCapacity((emxArray__common *)dz, ixstart, (int)sizeof(double));
  for (ixstart = 0; ixstart < ix; ixstart++) {
    dz->data[dz->size[0] * ixstart] = (zi2->data[ixstart] + zi2->data[n +
      ixstart]) / 2.0;
  }

  emxFree_real_T(&zi2);
  n = dx->size[0] * dx->size[1];
  dx->size[0] = 1;
  dx->size[1] = xe->size[1];
  emxEnsureCapacity((emxArray__common *)dx, n, (int)sizeof(double));
  ix = xe->size[1];
  for (n = 0; n < ix; n++) {
    dx->data[n] = 0.0;
  }

  /*  sumation for integral from curent first's contour piece to all pieces of second contour */
  cc = 0;
  emxInit_real_T(&b_dxi, 2);
  emxInit_real_T(&b_zim, 2);
  emxInit_real_T(&b_yim, 2);
  emxInit_real_T(&b_xim, 2);
  while (cc <= xim->size[1] - 1) {
    /*  current pieces counting in first contour */
    /*  curent element of current */
    n = b_xim->size[0] * b_xim->size[1];
    b_xim->size[0] = 1;
    b_xim->size[1] = xe->size[1];
    emxEnsureCapacity((emxArray__common *)b_xim, n, (int)sizeof(double));
    mtmp = xim->data[cc];
    ix = xe->size[0] * xe->size[1];
    for (n = 0; n < ix; n++) {
      b_xim->data[n] = mtmp - xe->data[n];
    }

    power(b_xim, dy);
    n = b_yim->size[0] * b_yim->size[1];
    b_yim->size[0] = 1;
    b_yim->size[1] = dL->size[1];
    emxEnsureCapacity((emxArray__common *)b_yim, n, (int)sizeof(double));
    mtmp = yim->data[cc];
    ix = dL->size[0] * dL->size[1];
    for (n = 0; n < ix; n++) {
      b_yim->data[n] = mtmp - dL->data[n];
    }

    power(b_yim, r0);
    n = b_zim->size[0] * b_zim->size[1];
    b_zim->size[0] = 1;
    b_zim->size[1] = dz->size[1];
    emxEnsureCapacity((emxArray__common *)b_zim, n, (int)sizeof(double));
    mtmp = zim->data[cc];
    ix = dz->size[0] * dz->size[1];
    for (n = 0; n < ix; n++) {
      b_zim->data[n] = mtmp - dz->data[n];
    }

    power(b_zim, r1);
    n = dy->size[0] * dy->size[1];
    dy->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)dy, n, (int)sizeof(double));
    ixstart = dy->size[0];
    n = dy->size[1];
    ix = ixstart * n;
    for (n = 0; n < ix; n++) {
      dy->data[n] = (dy->data[n] + r0->data[n]) + r1->data[n];
    }

    b_sqrt(dy);

    /*  dot product */
    n = b_dxi->size[0] * b_dxi->size[1];
    b_dxi->size[0] = 1;
    b_dxi->size[1] = ye->size[1];
    emxEnsureCapacity((emxArray__common *)b_dxi, n, (int)sizeof(double));
    mtmp = dxi->data[cc];
    b_mtmp = dyi->data[cc];
    c_mtmp = dzi->data[cc];
    ix = ye->size[0] * ye->size[1];
    for (n = 0; n < ix; n++) {
      b_dxi->data[n] = (mtmp * ye->data[n] + b_mtmp * ze->data[n]) + c_mtmp *
        dzi2->data[n];
    }

    rdivide(b_dxi, dy, r0);
    n = dx->size[0] * dx->size[1];
    dx->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)dx, n, (int)sizeof(double));
    ixstart = dx->size[0];
    n = dx->size[1];
    ix = ixstart * n;
    for (n = 0; n < ix; n++) {
      dx->data[n] += r0->data[n];
    }

    cc++;
  }

  emxFree_real_T(&b_xim);
  emxFree_real_T(&b_yim);
  emxFree_real_T(&b_zim);
  emxFree_real_T(&b_dxi);
  emxFree_real_T(&r1);
  emxFree_real_T(&r0);
  emxFree_real_T(&dzi2);
  emxFree_real_T(&zim);
  emxFree_real_T(&yim);
  emxFree_real_T(&xim);
  emxFree_real_T(&dzi);
  emxFree_real_T(&dyi);
  emxFree_real_T(&dxi);
  emxFree_real_T(&dL);
  emxFree_real_T(&dz);
  emxFree_real_T(&dy);
  emxFree_real_T(&ze);
  emxFree_real_T(&ye);
  emxFree_real_T(&xe);
  mtmp = sum(dx);
  //L = 1.0000000000000001E-7 * fabs(mtmp);
  L = fabs(mtmp);//Mutual coupling without permeability and 1/4pi factor
  emxFree_real_T(&dx);
  return L;
}

/*
 * File trailer for inductance_neuman.c
 *
 * [EOF]
 */

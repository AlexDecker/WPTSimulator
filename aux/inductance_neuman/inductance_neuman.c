/*
Calculates de Mutual Inductance *4pi/m0 between two coils
defined by three vectors (X,Y,Z)
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
 * Arguments    : const double x1[1000]
 *                const double b_y1[1000]
 *                const double z1[1000]
 *                const double x2[1000]
 *                const double y2[1000]
 *                const double z2[1000]
 * Return Type  : double
 */
double inductance_neuman(const double x1[1000], const double b_y1[1000], const
  double z1[1000], const double x2[1000], const double y2[1000], const double
  z2[1000])
{
  double L;
  int ixstart;
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
  boolean_T exitg3;
  double varargin_1[3];
  boolean_T exitg2;
  boolean_T exitg1;
  double xe[1001];
  double ye[1001];
  double ze[1001];
  double dv0[1000];
  double x[1000];
  double dv1[1000];
  double dv2[1000];
  double dv3[1000];
  double dx[1000];
  double cLee[1001];
  emxArray_real_T *t;
  emxArray_real_T *xi;
  emxArray_real_T *yi;
  emxArray_real_T *zi;
  emxArray_real_T *dxi;
  emxArray_real_T *dyi;
  emxArray_real_T *dzi;
  emxArray_real_T *r0;
  emxArray_real_T *r1;
  int loop_ub;
  emxArray_real_T *xim;
  emxArray_real_T *yim;
  emxArray_real_T *zim;
  double dv4[1000];
  double dv5[1000];
  double dv6[1000];
  emxArray_real_T *zi2;
  emxArray_real_T *dxi2;
  emxArray_real_T *dyi2;
  emxArray_real_T *dzi2;
  emxArray_real_T *xim2;
  int cc;
  emxArray_real_T *b_dxi;
  emxArray_real_T *b_zim;
  emxArray_real_T *b_yim;
  emxArray_real_T *b_xim;

  /*  high scale factor, dge*hsf is step in current discretization */
  /*  limits: */
  ixstart = 1;
  mtmp = x1[0];
  if (rtIsNaN(x1[0])) {
    ix = 2;
    exitg14 = false;
    while ((!exitg14) && (ix < 1001)) {
      ixstart = ix;
      if (!rtIsNaN(x1[ix - 1])) {
        mtmp = x1[ix - 1];
        exitg14 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 1000) {
    while (ixstart + 1 < 1001) {
      if (x1[ixstart] < mtmp) {
        mtmp = x1[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  b_mtmp = x1[0];
  if (rtIsNaN(x1[0])) {
    ix = 2;
    exitg13 = false;
    while ((!exitg13) && (ix < 1001)) {
      ixstart = ix;
      if (!rtIsNaN(x1[ix - 1])) {
        b_mtmp = x1[ix - 1];
        exitg13 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 1000) {
    while (ixstart + 1 < 1001) {
      if (x1[ixstart] > b_mtmp) {
        b_mtmp = x1[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  c_mtmp = b_y1[0];
  if (rtIsNaN(b_y1[0])) {
    ix = 2;
    exitg12 = false;
    while ((!exitg12) && (ix < 1001)) {
      ixstart = ix;
      if (!rtIsNaN(b_y1[ix - 1])) {
        c_mtmp = b_y1[ix - 1];
        exitg12 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 1000) {
    while (ixstart + 1 < 1001) {
      if (b_y1[ixstart] < c_mtmp) {
        c_mtmp = b_y1[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  d_mtmp = b_y1[0];
  if (rtIsNaN(b_y1[0])) {
    ix = 2;
    exitg11 = false;
    while ((!exitg11) && (ix < 1001)) {
      ixstart = ix;
      if (!rtIsNaN(b_y1[ix - 1])) {
        d_mtmp = b_y1[ix - 1];
        exitg11 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 1000) {
    while (ixstart + 1 < 1001) {
      if (b_y1[ixstart] > d_mtmp) {
        d_mtmp = b_y1[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  e_mtmp = z1[0];
  if (rtIsNaN(z1[0])) {
    ix = 2;
    exitg10 = false;
    while ((!exitg10) && (ix < 1001)) {
      ixstart = ix;
      if (!rtIsNaN(z1[ix - 1])) {
        e_mtmp = z1[ix - 1];
        exitg10 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 1000) {
    while (ixstart + 1 < 1001) {
      if (z1[ixstart] < e_mtmp) {
        e_mtmp = z1[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  f_mtmp = z1[0];
  if (rtIsNaN(z1[0])) {
    ix = 2;
    exitg9 = false;
    while ((!exitg9) && (ix < 1001)) {
      ixstart = ix;
      if (!rtIsNaN(z1[ix - 1])) {
        f_mtmp = z1[ix - 1];
        exitg9 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 1000) {
    while (ixstart + 1 < 1001) {
      if (z1[ixstart] > f_mtmp) {
        f_mtmp = z1[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  g_mtmp = x2[0];
  if (rtIsNaN(x2[0])) {
    ix = 2;
    exitg8 = false;
    while ((!exitg8) && (ix < 1001)) {
      ixstart = ix;
      if (!rtIsNaN(x2[ix - 1])) {
        g_mtmp = x2[ix - 1];
        exitg8 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 1000) {
    while (ixstart + 1 < 1001) {
      if (x2[ixstart] < g_mtmp) {
        g_mtmp = x2[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  h_mtmp = x2[0];
  if (rtIsNaN(x2[0])) {
    ix = 2;
    exitg7 = false;
    while ((!exitg7) && (ix < 1001)) {
      ixstart = ix;
      if (!rtIsNaN(x2[ix - 1])) {
        h_mtmp = x2[ix - 1];
        exitg7 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 1000) {
    while (ixstart + 1 < 1001) {
      if (x2[ixstart] > h_mtmp) {
        h_mtmp = x2[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  i_mtmp = y2[0];
  if (rtIsNaN(y2[0])) {
    ix = 2;
    exitg6 = false;
    while ((!exitg6) && (ix < 1001)) {
      ixstart = ix;
      if (!rtIsNaN(y2[ix - 1])) {
        i_mtmp = y2[ix - 1];
        exitg6 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 1000) {
    while (ixstart + 1 < 1001) {
      if (y2[ixstart] < i_mtmp) {
        i_mtmp = y2[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  j_mtmp = y2[0];
  if (rtIsNaN(y2[0])) {
    ix = 2;
    exitg5 = false;
    while ((!exitg5) && (ix < 1001)) {
      ixstart = ix;
      if (!rtIsNaN(y2[ix - 1])) {
        j_mtmp = y2[ix - 1];
        exitg5 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 1000) {
    while (ixstart + 1 < 1001) {
      if (y2[ixstart] > j_mtmp) {
        j_mtmp = y2[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  k_mtmp = z2[0];
  if (rtIsNaN(z2[0])) {
    ix = 2;
    exitg4 = false;
    while ((!exitg4) && (ix < 1001)) {
      ixstart = ix;
      if (!rtIsNaN(z2[ix - 1])) {
        k_mtmp = z2[ix - 1];
        exitg4 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 1000) {
    while (ixstart + 1 < 1001) {
      if (z2[ixstart] < k_mtmp) {
        k_mtmp = z2[ixstart];
      }

      ixstart++;
    }
  }

  ixstart = 1;
  l_mtmp = z2[0];
  if (rtIsNaN(z2[0])) {
    ix = 2;
    exitg3 = false;
    while ((!exitg3) && (ix < 1001)) {
      ixstart = ix;
      if (!rtIsNaN(z2[ix - 1])) {
        l_mtmp = z2[ix - 1];
        exitg3 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 1000) {
    while (ixstart + 1 < 1001) {
      if (z2[ixstart] > l_mtmp) {
        l_mtmp = z2[ixstart];
      }

      ixstart++;
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

  /*  maximal size of second contour */
  /*  discretization of first contour: */
  xe[1000] = x1[0];
  ye[1000] = b_y1[0];
  memcpy(&xe[0], &x1[0], 1000U * sizeof(double));
  memcpy(&ye[0], &b_y1[0], 1000U * sizeof(double));
  memcpy(&ze[0], &z1[0], 1000U * sizeof(double));
  ze[1000] = z1[0];
  diff(xe, dv0);
  power(dv0, x);
  diff(ye, dv1);
  power(dv1, dv2);
  diff(ze, dv3);
  power(dv3, dx);
  for (ix = 0; ix < 1000; ix++) {
    x[ix] = (x[ix] + dv2[ix]) + dx[ix];
  }

  b_sqrt(x);
  for (ixstart = 0; ixstart < 999; ixstart++) {
    x[ixstart + 1] += x[ixstart];
  }

  /*  total length */
  cLee[0] = 0.0;
  memcpy(&cLee[1], &x[0], 1000U * sizeof(double));
  emxInit_real_T(&t, 2);
  emxInit_real_T(&xi, 2);
  emxInit_real_T(&yi, 2);
  emxInit_real_T(&zi, 2);
  emxInit_real_T(&dxi, 2);
  emxInit_real_T(&dyi, 2);
  emxInit_real_T(&dzi, 2);
  emxInit_real_T(&r0, 2);
  emxInit_real_T(&r1, 2);

  /* t=0:dt:cLend; */
  linspace(x[999], rt_roundd_snf(x[999] / (0.002 * mtmp)), t);

  /*  closed */
  interp1(cLee, xe, t, xi);
  interp1(cLee, ye, t, yi);

  /*  current discretization points */
  interp1(cLee, ze, t, zi);

  /*  current discretization points */
  b_diff(xi, dxi);
  b_diff(yi, dyi);
  b_diff(zi, dzi);
  b_power(dxi, t);
  b_power(dyi, r0);
  b_power(dzi, r1);
  ix = t->size[0] * t->size[1];
  t->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)t, ix, (int)sizeof(double));
  ixstart = t->size[0];
  ix = t->size[1];
  loop_ub = ixstart * ix;
  for (ix = 0; ix < loop_ub; ix++) {
    t->data[ix] = (t->data[ix] + r0->data[ix]) + r1->data[ix];
  }

  c_sqrt(t);

  /*  mean points: */
  if (1 > xi->size[1] - 1) {
    loop_ub = 0;
  } else {
    loop_ub = xi->size[1] - 1;
  }

  if (2 > xi->size[1]) {
    ix = 0;
  } else {
    ix = 1;
  }

  emxInit_real_T(&xim, 2);
  ixstart = xim->size[0] * xim->size[1];
  xim->size[0] = 1;
  xim->size[1] = loop_ub;
  emxEnsureCapacity((emxArray__common *)xim, ixstart, (int)sizeof(double));
  for (ixstart = 0; ixstart < loop_ub; ixstart++) {
    xim->data[xim->size[0] * ixstart] = (xi->data[ixstart] + xi->data[ix +
      ixstart]) / 2.0;
  }

  if (1 > yi->size[1] - 1) {
    loop_ub = 0;
  } else {
    loop_ub = yi->size[1] - 1;
  }

  if (2 > yi->size[1]) {
    ix = 0;
  } else {
    ix = 1;
  }

  emxInit_real_T(&yim, 2);
  ixstart = yim->size[0] * yim->size[1];
  yim->size[0] = 1;
  yim->size[1] = loop_ub;
  emxEnsureCapacity((emxArray__common *)yim, ixstart, (int)sizeof(double));
  for (ixstart = 0; ixstart < loop_ub; ixstart++) {
    yim->data[yim->size[0] * ixstart] = (yi->data[ixstart] + yi->data[ix +
      ixstart]) / 2.0;
  }

  if (1 > zi->size[1] - 1) {
    loop_ub = 0;
  } else {
    loop_ub = zi->size[1] - 1;
  }

  if (2 > zi->size[1]) {
    ix = 0;
  } else {
    ix = 1;
  }

  emxInit_real_T(&zim, 2);
  ixstart = zim->size[0] * zim->size[1];
  zim->size[0] = 1;
  zim->size[1] = loop_ub;
  emxEnsureCapacity((emxArray__common *)zim, ixstart, (int)sizeof(double));
  for (ixstart = 0; ixstart < loop_ub; ixstart++) {
    zim->data[zim->size[0] * ixstart] = (zi->data[ixstart] + zi->data[ix +
      ixstart]) / 2.0;
  }

  /*  discretization of second contour: */
  xe[1000] = x2[0];
  ye[1000] = y2[0];
  memcpy(&xe[0], &x2[0], 1000U * sizeof(double));
  memcpy(&ye[0], &y2[0], 1000U * sizeof(double));
  memcpy(&ze[0], &z2[0], 1000U * sizeof(double));
  ze[1000] = z2[0];
  diff(xe, dv4);
  power(dv4, x);
  diff(ye, dv5);
  power(dv5, dv2);
  diff(ze, dv6);
  power(dv6, dx);
  for (ix = 0; ix < 1000; ix++) {
    x[ix] = (x[ix] + dv2[ix]) + dx[ix];
  }

  b_sqrt(x);
  for (ixstart = 0; ixstart < 999; ixstart++) {
    x[ixstart + 1] += x[ixstart];
  }

  /*  total length */
  cLee[0] = 0.0;
  memcpy(&cLee[1], &x[0], 1000U * sizeof(double));
  emxInit_real_T(&zi2, 2);
  emxInit_real_T(&dxi2, 2);
  emxInit_real_T(&dyi2, 2);
  emxInit_real_T(&dzi2, 2);

  /* t=0:dt:cLend; */
  linspace(x[999], rt_roundd_snf(x[999] / (0.002 * b_mtmp)), t);

  /*  closed */
  interp1(cLee, xe, t, xi);
  interp1(cLee, ye, t, yi);

  /*  current discretization points */
  interp1(cLee, ze, t, zi2);

  /*  current discretization points */
  b_diff(xi, dxi2);
  b_diff(yi, dyi2);
  b_diff(zi2, dzi2);
  b_power(dxi2, t);
  b_power(dyi2, r0);
  b_power(dzi2, r1);
  ix = t->size[0] * t->size[1];
  t->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)t, ix, (int)sizeof(double));
  ixstart = t->size[0];
  ix = t->size[1];
  loop_ub = ixstart * ix;
  for (ix = 0; ix < loop_ub; ix++) {
    t->data[ix] = (t->data[ix] + r0->data[ix]) + r1->data[ix];
  }

  c_sqrt(t);

  /*  mean points: */
  if (1 > xi->size[1] - 1) {
    loop_ub = 0;
  } else {
    loop_ub = xi->size[1] - 1;
  }

  if (2 > xi->size[1]) {
    ix = 0;
  } else {
    ix = 1;
  }

  emxInit_real_T(&xim2, 2);
  ixstart = xim2->size[0] * xim2->size[1];
  xim2->size[0] = 1;
  xim2->size[1] = loop_ub;
  emxEnsureCapacity((emxArray__common *)xim2, ixstart, (int)sizeof(double));
  for (ixstart = 0; ixstart < loop_ub; ixstart++) {
    xim2->data[xim2->size[0] * ixstart] = (xi->data[ixstart] + xi->data[ix +
      ixstart]) / 2.0;
  }

  if (1 > yi->size[1] - 1) {
    loop_ub = 0;
  } else {
    loop_ub = yi->size[1] - 1;
  }

  if (2 > yi->size[1]) {
    ix = 0;
  } else {
    ix = 1;
  }

  ixstart = zi->size[0] * zi->size[1];
  zi->size[0] = 1;
  zi->size[1] = loop_ub;
  emxEnsureCapacity((emxArray__common *)zi, ixstart, (int)sizeof(double));
  for (ixstart = 0; ixstart < loop_ub; ixstart++) {
    zi->data[zi->size[0] * ixstart] = (yi->data[ixstart] + yi->data[ix + ixstart])
      / 2.0;
  }

  if (1 > zi2->size[1] - 1) {
    loop_ub = 0;
  } else {
    loop_ub = zi2->size[1] - 1;
  }

  if (2 > zi2->size[1]) {
    ix = 0;
  } else {
    ix = 1;
  }

  ixstart = yi->size[0] * yi->size[1];
  yi->size[0] = 1;
  yi->size[1] = loop_ub;
  emxEnsureCapacity((emxArray__common *)yi, ixstart, (int)sizeof(double));
  for (ixstart = 0; ixstart < loop_ub; ixstart++) {
    yi->data[yi->size[0] * ixstart] = (zi2->data[ixstart] + zi2->data[ix +
      ixstart]) / 2.0;
  }

  emxFree_real_T(&zi2);
  ix = t->size[0] * t->size[1];
  t->size[0] = 1;
  t->size[1] = xim2->size[1];
  emxEnsureCapacity((emxArray__common *)t, ix, (int)sizeof(double));
  loop_ub = xim2->size[1];
  for (ix = 0; ix < loop_ub; ix++) {
    t->data[ix] = 0.0;
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
    ix = b_xim->size[0] * b_xim->size[1];
    b_xim->size[0] = 1;
    b_xim->size[1] = xim2->size[1];
    emxEnsureCapacity((emxArray__common *)b_xim, ix, (int)sizeof(double));
    mtmp = xim->data[cc];
    loop_ub = xim2->size[0] * xim2->size[1];
    for (ix = 0; ix < loop_ub; ix++) {
      b_xim->data[ix] = mtmp - xim2->data[ix];
    }

    b_power(b_xim, xi);
    ix = b_yim->size[0] * b_yim->size[1];
    b_yim->size[0] = 1;
    b_yim->size[1] = zi->size[1];
    emxEnsureCapacity((emxArray__common *)b_yim, ix, (int)sizeof(double));
    mtmp = yim->data[cc];
    loop_ub = zi->size[0] * zi->size[1];
    for (ix = 0; ix < loop_ub; ix++) {
      b_yim->data[ix] = mtmp - zi->data[ix];
    }

    b_power(b_yim, r0);
    ix = b_zim->size[0] * b_zim->size[1];
    b_zim->size[0] = 1;
    b_zim->size[1] = yi->size[1];
    emxEnsureCapacity((emxArray__common *)b_zim, ix, (int)sizeof(double));
    mtmp = zim->data[cc];
    loop_ub = yi->size[0] * yi->size[1];
    for (ix = 0; ix < loop_ub; ix++) {
      b_zim->data[ix] = mtmp - yi->data[ix];
    }

    b_power(b_zim, r1);
    ix = xi->size[0] * xi->size[1];
    xi->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)xi, ix, (int)sizeof(double));
    ixstart = xi->size[0];
    ix = xi->size[1];
    loop_ub = ixstart * ix;
    for (ix = 0; ix < loop_ub; ix++) {
      xi->data[ix] = (xi->data[ix] + r0->data[ix]) + r1->data[ix];
    }

    c_sqrt(xi);

    /*  dot product */
    ix = b_dxi->size[0] * b_dxi->size[1];
    b_dxi->size[0] = 1;
    b_dxi->size[1] = dxi2->size[1];
    emxEnsureCapacity((emxArray__common *)b_dxi, ix, (int)sizeof(double));
    mtmp = dxi->data[cc];
    b_mtmp = dyi->data[cc];
    c_mtmp = dzi->data[cc];
    loop_ub = dxi2->size[0] * dxi2->size[1];
    for (ix = 0; ix < loop_ub; ix++) {
      b_dxi->data[ix] = (mtmp * dxi2->data[ix] + b_mtmp * dyi2->data[ix]) +
        c_mtmp * dzi2->data[ix];
    }

    rdivide(b_dxi, xi, r0);
    ix = t->size[0] * t->size[1];
    t->size[0] = 1;
    emxEnsureCapacity((emxArray__common *)t, ix, (int)sizeof(double));
    ixstart = t->size[0];
    ix = t->size[1];
    loop_ub = ixstart * ix;
    for (ix = 0; ix < loop_ub; ix++) {
      t->data[ix] += r0->data[ix];
    }

    cc++;
  }

  emxFree_real_T(&b_xim);
  emxFree_real_T(&b_yim);
  emxFree_real_T(&b_zim);
  emxFree_real_T(&b_dxi);
  emxFree_real_T(&r1);
  emxFree_real_T(&r0);
  emxFree_real_T(&xim2);
  emxFree_real_T(&dzi2);
  emxFree_real_T(&dyi2);
  emxFree_real_T(&dxi2);
  emxFree_real_T(&zim);
  emxFree_real_T(&yim);
  emxFree_real_T(&xim);
  emxFree_real_T(&dzi);
  emxFree_real_T(&dyi);
  emxFree_real_T(&dxi);
  emxFree_real_T(&zi);
  emxFree_real_T(&yi);
  emxFree_real_T(&xi);
  mtmp = sum(t);
  //L = 1.0000000000000001E-7 * fabs(mtmp);
  L = fabs(mtmp);
  emxFree_real_T(&t);
  return L;
}

/*
 * File trailer for inductance_neuman.c
 *
 * [EOF]
 */

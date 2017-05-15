/*
 * File: power.h
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 15-May-2017 14:17:50
 */

#ifndef POWER_H
#define POWER_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "inductance_neuman_types.h"

/* Function Declarations */
extern void b_power(const emxArray_real_T *a, emxArray_real_T *y);
extern void power(const double a[1000], double y[1000]);

#endif

/*
 * File trailer for power.h
 *
 * [EOF]
 */
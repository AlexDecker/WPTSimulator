/*
 * File: main.c
 *
 * MATLAB Coder version            : 3.1
 * C/C++ source code generated on  : 17-May-2017 11:29:01
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include Files */
#include "rt_nonfinite.h"
#include "inductance_neuman.h"
#include "main.h"
#include "inductance_neuman_terminate.h"
#include "inductance_neuman_emxAPI.h"
#include "inductance_neuman_initialize.h"

static void main_inductance_neuman(void);

static void main_inductance_neuman(void)
{
  emxArray_real_T *x1;
  emxArray_real_T *y1;
  emxArray_real_T *z1;
  
  emxArray_real_T *x2;
  emxArray_real_T *y2;
  emxArray_real_T *z2;
  double L; int i;
  
  static int size[2] = { 1, 1000 };
  
  double R2 = 0.2; double R1 = 0.1; double N = 15; double tx = 0.1;
  double delta = (R2-R1)/N;
  double tetaMin = R1*N*2*PI/(R2-R1);
  double tetaMax = R2*N*2*PI/(R2-R1);

  x1 = emxCreateND_real_T(2, size);
  y1 = emxCreateND_real_T(2, size);
  z1 = emxCreateND_real_T(2, size);
  x2 = emxCreateND_real_T(2, size);
  y2 = emxCreateND_real_T(2, size);
  z2 = emxCreateND_real_T(2, size);
  
  double teta = tetaMin; double step = (tetaMax-tetaMin)/1000;
  
  for (i = 0; i < x1->size[1U]; i++) {
    x1->data[x1->size[0] * i] = delta*teta*cos(teta)/(2*PI);
	y1->data[y1->size[0] * i] = delta*teta*sin(teta)/(2*PI);
	z1->data[z1->size[0] * i] = 0.0;
	x2->data[x2->size[0] * i] = x1->data[x1->size[0] * i];
	y2->data[y2->size[0] * i] = y1->data[y1->size[0] * i];
	z2->data[z2->size[0] * i] = tx;
	teta = (teta+step>=tetaMax)?tetaMax:teta+step;
  }

  
  L = inductance_neuman(x1, y1, z1, x2, y2, z2);
  emxDestroyArray_real_T(z2);
  emxDestroyArray_real_T(y2);
  emxDestroyArray_real_T(x2);
  emxDestroyArray_real_T(z1);
  emxDestroyArray_real_T(y1);
  emxDestroyArray_real_T(x1);
  printf("\nResultado: %f\n",L);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  inductance_neuman_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_inductance_neuman();

  /* Terminate the application.
     You do not need to do this more than one time. */
  inductance_neuman_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */

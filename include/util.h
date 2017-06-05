#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Matrix.h"

#ifndef UTIL_H
#define UTIL_H

typedef struct{
	double x;
	double y;
	double z;
}point;

typedef struct{
	point* data;
	int size;
}pointVector;

enum AXIS { 
	AXIS_X,
	AXIS_Y, 
	AXIS_Z
};

typedef struct{
	Matrix* imag;
	Matrix* real;
}complexMatrix;

typedef struct{
	double imag;
	double real;
}complexDouble;

void showError(const char* s);
double distance(point A, point B);

#endif
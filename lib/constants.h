#include <stdio.h>
#include <stdlib.h>
#include "../aux/Matrix.h"

typedef struct{
	double x;
	double y;
	double z;
}point;

typedef point* pointVector;

enum AXIS { 
	AXIS_X,
	AXIS_Y, 
	AXIS_Z
};

typedef struct{
	Matrix imag;
	Matrix real;
}complexMatrix;

typedef struct{
	double imag;
	double real;
}complexDouble;

//resistivity (ohm*m) table at 20ºC
//(http://hyperphysics.phy-astr.gsu.edu/hbase/Tables/rstiv.html)
#define R_SILVER 1.59e-8
#define R_COPPER 1.68e-8
#define R_ALUMINIUM 2.65e-8
#define R_TUNGSTEN 5.6e-8
#define R_IRON 9.71e-8
#define R_PLATINUM 10.6e-8

//magnetic permeability (N/A2)

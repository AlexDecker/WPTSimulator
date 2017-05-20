#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

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
	Matrix imag;
	Matrix real;
}complexMatrix;

typedef struct{
	double imag;
	double real;
}complexDouble;

//various
#define COIL_RESOLUTION (1000) //number of points that define a coil
#define PI (3.1415926535)
#define F_1KHZ (1.0e+3)
#define F_10KHZ (1.0e+4)
#define F_100KHZ (1.0e+5)
#define F_1MHZ (1.0e+6)
#define F_3MHZ (3.0e+6)

//default simulation values
#define DEFAULT_CAPACITANCE (1.0e-6) //(Farad)
#define DEFAULT_RESISTANCE  (50.0) //(Ohm)
#define DEFAULT_MUTUAL_COUPLING (0.0) //(Henry)
#define DEFAULT_SOURCE_VOLTAGE (1.0) //(Volt)
#define DEFAULT_FREQUENCY F_1KHZ
#define DEFAULT_PERMEABILITY P_VACUUM
#define DEFAULT_RESISTIVITY R_COPPER

//default coil params (m)
#define DEFAULT_INNER_R (0.1)
#define DEFAULT_OUTTER_R (0.2)
#define DEFAULT_NSPIRES (10) //(adimensional)
#define DEFAULT_WIRE_RADIUS (0.001)

//resistivity (ohm*m) table at 20ºC
//(http://hyperphysics.phy-astr.gsu.edu/hbase/Tables/rstiv.html)
#define R_SILVER (1.59e-8)
#define R_COPPER (1.68e-8)
#define R_ALUMINIUM (2.65e-8)
#define R_TUNGSTEN (5.6e-8)
#define R_IRON (9.71e-8)
#define R_PLATINUM (10.6e-8)

//magnetic permeability (N/A2)
#define P_VACUUM (PI*4.0e-7)
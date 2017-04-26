/*Module that encapsulates all the calculations related to physics simulations*/

#include "../aux/Matrix.h"
#include "RLCsystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void calculateCurrents(Matrix RealZ, Matrix ImagZ, Matrix RealV, Matrix ImagV,
			Matrix& RealI, Matrix& ImagI);

void calculatePower(Matrix RealI, Matriz ImagI, Matrix RealZ, Matrix ImagZ);

void calculateUnitaryImpedance(double resistence, double capacitance, double selfInductance, double* realZ, double* imagZ);



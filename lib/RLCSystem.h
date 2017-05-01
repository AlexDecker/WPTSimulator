#include "coil.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Class RLCSystem{

	public:
	
//*********************************************************************
	private:
		void calculateUnitaryImpedance(double resistence,
			double capacitance, double selfInductance, double* realZ,
				double* imagZ);
};
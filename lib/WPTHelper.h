#include "../aux/Matrix.h"
#include "RLCSystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Class WPTHelper{

	public:
	
//*********************************************************************
	private:
		void calculateCurrents(Matrix RealZ, Matrix ImagZ, Matrix RealV,
			Matrix ImagV, Matrix& RealI, Matrix& ImagI);
		void calculatePower(Matrix RealI, Matriz ImagI, Matrix RealZ,
			Matrix ImagZ);
		void calculateMutualInductance(RLCsystem s1, RLCsystem s2,
			double permeability);
};

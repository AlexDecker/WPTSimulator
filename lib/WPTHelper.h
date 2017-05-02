#include "constants.h"
#include "../aux/Matrix.h"
#include "RLCSystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Class WPTHelper{

	public:
		static WPTHelper* getInstance();
//*********************************************************************
	private:
		//(Singleton pattern issues)
		WPTHelper(){};  
	  	WPTHelper(WPTHelper const&){};             // copy constructor is private
	  	WPTHelper& operator=(WPTHelper const&){};  // assignment operator is private
	  	static WPTHelper* Instance = NULL;

	  	//Matrix for global kirchhoff estimations
	  	complexMatrix Impedance;
	  	complexMatrix SourceVoltage;
	  	complexMatrix Current;

	  	double permeability;

	  	RLCSystem* environment;//pointers to all RLC Systems in the environment (index=id of each RLCSystem)

		void calculateCurrents();
		void calculateMutualInductance(int id1, int id2);
};

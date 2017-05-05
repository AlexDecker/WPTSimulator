#include "constants.h"
#include "../aux/Matrix.h"
//#include "RLCSystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Class GlobalCoupler{

	public:
		static GlobalCoupler* getInstance();
		complexDouble getCurrent(int nodeId);

		void updateVoltageSource(int nodeId, complexDouble newVoltage);
		void updateCapacitance(int nodeId, double newCapacitance);
		void updateResitance(int nodeId, double newResistance);

		void updateMutualCouplingMatrix(complexMatrix newMetrix);
//*********************************************************************
	private:
		//(Singleton pattern issues)
		GlobalCoupler(){};  
	  	GlobalCoupler(GlobalCoupler const&){};             // copy constructor is private
	  	GlobalCoupler& operator=(GlobalCoupler const&){};  // assignment operator is private
	  	static GlobalCoupler* Instance = NULL;

	  	//Matrix for global kirchhoff estimations
	  	Matrix CapacitanceMatrix;//1xn matrix
	  	Matrix ResistanceMatrix;//1xn matrix
	  	Matrix MutualCouplingMatrix;//nxn matrix
	  	complexMatrix SourceVoltage;//2x1xn matrix
	  	complexMatrix Current;//2x1xn matrix

	  	bool allTheSame=false;//flag that tells the system if the values must not be recalculated

	  	//for future implementations:
	  	//double permeability;
	  	//RLCSystem* environment;//pointers to all RLC Systems in the environment (index=id of each RLCSystem)

		void calculateCurrents();
		//for future implementations:
		//void calculateMutualInductance(int id1, int id2);
};

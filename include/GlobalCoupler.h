/*
This file models the entire system as a set of resonant coupled RLC systems. "w" defines the angular frequency that all systems resonate. The capacitance of each system cannot be defined by the user, because is set in function of the coil's self inductance in order to maintein the resonance with the voltage source. During the runtime, the user can modify the spacial params of the coil (orientation and position), the resistance of each system and each voltage source phasor.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>
#include <string.h>

#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "inductance_neuman_types.h"
#include "constants.h"
#include "Matrix.h"
#include "cinv.h"
#include "Coil.h"

#ifndef GLOBAL_COUPLER_H
#define GLOBAL_COUPLER_H

class GlobalCoupler{

	public:
		static GlobalCoupler* getInstance(int nNodes=2, double permeability=DEFAULT_PERMEABILITY, double frequency=DEFAULT_FREQUENCY);
		
		complexDouble getCurrent(int nodeId);
		double getCapacitance(int nodeId);//(mF)

		void updateSourceVoltage(int nodeId, complexDouble newVoltage);
		//void updateFrequency(double frequency);
		void updateResitance(int nodeId, double newResistance);
		
		void rotateCoil(int nodeId,AXIS axis, double teta);
		void translateCoil(int nodeId, double dx, double dy, double dz);
		
		//returns the index of the coil in the container
		int addNode(Coil& coil, double resistance, complexDouble sourceVoltage);
		
		void destroyEnvironment();
//*********************************************************************
	private:
		//(Singleton pattern issues)
		GlobalCoupler(){};  
	  	GlobalCoupler(GlobalCoupler const&){};             // copy constructor is private
	  	GlobalCoupler& operator=(GlobalCoupler const&){};  // assignment operator is private
	  	static GlobalCoupler* Instance = NULL;
		static int nodesUpToNow = 0;//number of nodes up to now

	  	//Matrix for global kirchhoff estimations
	  	static Matrix partialZMatrix;//nxn matrix with the inductance between the i and j coils. The main diagonal holds the ohmic resistance of each system.
	  	static complexMatrix SourceVoltage;//2x1xn matrix (voltage source phasor)
	  	static complexMatrix Current;//2x1xn matrix
		double w;//global angular frequency

	  	static bool allTheSame=false;//flag that tells the system if the values must not be recalculated

	  	static double env_permeability;
	  	static Coil* coilContainer;//vector with all the coils of the environment

		void calculateCurrents();
		bool updatePartialZMatrix(complexMatrix newMetrix);
		void calculateMutualInductance(int id1, int id2);
		void updateMutualInductances();
		void updateFrequency(double frequency);
		static void showError(const char*  s);
};
#endif
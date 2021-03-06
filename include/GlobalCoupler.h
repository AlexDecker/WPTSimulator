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
#include "inductance_neuman.h"
#include "inductance_neuman_terminate.h"
#include "inductance_neuman_initialize.h"
#include "constants.h"
#include "Matrix.h"
#include "cinv.h"
#include "Coil.h"
#include "util.h"

#ifndef GLOBAL_COUPLER_H
#define GLOBAL_COUPLER_H

class GlobalCoupler{

	public:
		static GlobalCoupler* getInstance();
		static GlobalCoupler* getInstance(int nNodes, double permeability, double frequency);
		
		static const char* mailBox;
		
		complexDouble getCurrent(int nodeId);
		double getCapacitance(int nodeId);//(mF)

		void updateSourceVoltage(int nodeId, complexDouble newVoltage);
		static void updateFrequency(double frequency);
		void updateResistance(int nodeId, double newResistance);
		bool updatePartialZMatrix(Matrix& newMetrix);
		
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
	  	static GlobalCoupler* Instance;
		static int nodesUpToNow;//number of nodes up to now
		static bool terminated;//true if the simulation already has finished

	  	//Matrix for global kirchhoff estimations
	  	static Matrix* partialZMatrix;//nxn matrix with the inductance between the i and j coils. The main diagonal holds the ohmic resistance of each system.
	  	static complexMatrix SourceVoltage;//2x1xn matrix (voltage source phasor)
	  	static complexMatrix Current;//2x1xn matrix
		static double w;//global angular frequency

	  	static bool allTheSame;//flag that tells the system if the values must not be recalculated

	  	static double env_permeability;
	  	static Coil* coilContainer;//vector with all the coils of the environment

		void calculateCurrents();
		void calculateMutualInductance(int id1, int id2);
		void updateMutualInductances();
};
#endif
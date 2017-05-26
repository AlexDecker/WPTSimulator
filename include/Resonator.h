/*Façade class to ensure that the node will directly modify and read only its
own resonator systems.*/
#include <stdio.h>
#include <stdlib.h>
#include "GlobalCoupler.h"
#include "Coil.h"

#ifndef RESONATOR_H
#define RESONATOR_H

class Resonator{
	public:
		Resonator(Coil* coil, double resistance,
			complexDouble sourceVoltage);
		complexDouble getCurrent();
		double getCapacitance();//(mF)

		void updateSourceVoltage(complexDouble newVoltage);
		void requireGlobalFrequencyUpdate(double newFrequency);
		void updateResitance(double newResistance);
		
		void rotateCoil(AXIS axis, double teta);
		void translateCoil(double dx, double dy, double dz);
		
		~Resonator();
	private:
		GlobalCoupler* environment;
		Coil* coilRef;
		int nodeId;
};
#endif
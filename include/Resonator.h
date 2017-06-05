/*Façade class to ensure that the node will directly modify and read only its
own resonator systems.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "GlobalCoupler.h"
#include "Coil.h"

#ifndef RESONATOR_H
#define RESONATOR_H

class Resonator{
	public:
		Resonator(Coil* coil, double newResistance,
			complexDouble newSourceVoltage);
		complexDouble getCurrent();
		double getCapacitance();//(mF)
		double getPower();

		void updateSourceVoltage(complexDouble newVoltage);
		void requireGlobalFrequencyUpdate(double newFrequency);
		void sendBroadcastMessage(const char* message);
		const char* getMailBox();
		void updateResistance(double newResistance);
		
		void rotateCoil(AXIS axis, double teta);
		void translateCoil(double dx, double dy, double dz);
		
		~Resonator();
	private:
		GlobalCoupler* environment;
		Coil* coilRef;
		int nodeId;
		//useful to calculate the power
		double resistance;
};
#endif
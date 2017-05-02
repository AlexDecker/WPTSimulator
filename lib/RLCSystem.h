#include "coil.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Class RLCSystem{

	public:
	//Constructors
		//default (default coil, 1MHz frequency, 5ohms resistance)
		RLCSystem(WPTHelper wptHelper);
		//complete
		RLCSystem(Coil coil, double capacitance, double resistance,
					WPTHelper wptHelper);
	//gets
		getId();
		double getAngFrequency();
		double getResistance();
		complexDouble getUnitaryImpedance();
		complexDouble getSourceVoltage();
	//Uses the helper to calculate the current, if it's not already calculated
		complexDouble getCurrent();
		double getPower();
	//rotate/tranlate the coil and modify the params in the helper
		void rotateCoil(AXIS axis, double teta);
		void translateCoil(double dx, double dy, double dz);
//*********************************************************************
	private:
		//You cannot destroy the RLCSystem during the simulation
		~RLCSystem();

		static int nextId = 0;
		int id;//system id
		bool upToDate=false;//flag that is true when 

		WPTHelper wptHelper;
		Coil coil;
		double angFrequency;
		double resistance;
		complexDouble unitaryImpedance;
		complexDouble SourceVoltage;

		complexDouble calculateUnitaryImpedance();
};
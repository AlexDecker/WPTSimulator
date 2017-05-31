/*
Simple example to test the mutual coupling calculations.
Change the value of 'VERBOSE' on constants.h to print the
values of the mutual inductance in (1.0e-5)H
*/ 
#include "example.h"

void example2(){
	
	double radius = 0.1225;
	int nSpires = 8;
	double pitch = 0.003;
	double wireRadius = 0.0001;
	
	GlobalCoupler* GC = GlobalCoupler::getInstance(2, DEFAULT_PERMEABILITY, DEFAULT_FREQUENCY);//creating the environment
	
	complexDouble source1;
	source1.real = DEFAULT_SOURCE_VOLTAGE;
	source1.imag = 0.0;
	
	complexDouble source2;
	source2.real = 0.0;
	source2.imag = 0.0;
	
	//creates a solenoid coil
	Coil* c1 = new Coil(radius, nSpires, pitch, wireRadius,DEFAULT_RESISTIVITY, DEFAULT_PERMEABILITY);
	Coil* c2 = new Coil(radius, nSpires, pitch, wireRadius,DEFAULT_RESISTIVITY, DEFAULT_PERMEABILITY);
	
	Resonator* TX = new Resonator(c1, DEFAULT_RESISTANCE, source1);
	Resonator* RX = new Resonator(c2, DEFAULT_RESISTANCE, source2);
	
	RX->translateCoil(0.0, 0.0, wireRadius+nSpires*pitch);//translate the length of the coil, so the coils start side by side
	
	for(double i=0.02;i<=0.22;i+=0.02){
		RX->translateCoil(0.0, 0.0, 0.02);
		//dummie invocation to update the mutual inductance matrix
		RX->getCurrent();
		printf("\n");
	}
	
	delete RX; delete TX;
	GC->destroyEnvironment();
}
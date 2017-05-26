//Simple example to set default resonators and calculate the current on RX
#include "example.h"

void example2(){
	
	GlobalCoupler* GC = GlobalCoupler::getInstance(2, DEFAULT_PERMEABILITY, DEFAULT_FREQUENCY);//creating the environment
	
	complexDouble source1;
	source1.real = DEFAULT_SOURCE_VOLTAGE;
	source1.imag = 0.0;
	
	complexDouble source2;
	source2.real = 0.0;
	source2.imag = 0.0;
	
	Resonator* TX = new Resonator(new Coil(), DEFAULT_RESISTANCE, source1);
	Resonator* RX = new Resonator(new Coil(), DEFAULT_RESISTANCE, source2);
	
	RX->translateCoil(0.0, 0.0, 0.1);
	complexDouble i = RX->getCurrent();
	
	printf("Phasor of the current on RX node: (%f,%f) A\n",i.real,i.imag);
	
	delete RX; delete TX;
	GC->destroyEnvironment();
}
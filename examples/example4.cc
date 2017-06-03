//Simple example to set default resonators and send a broadcast message.
#include "example.h"

void example4(){
	
	GlobalCoupler* GC = GlobalCoupler::getInstance(2, DEFAULT_PERMEABILITY, DEFAULT_FREQUENCY);//creating the environment
	
	complexDouble source1;
	source1.real = DEFAULT_SOURCE_VOLTAGE;
	source1.imag = 0.0;
	
	complexDouble source2;
	source2.real = 0.0;
	source2.imag = 0.0;
	
	Resonator* TX = new Resonator(new Coil(), DEFAULT_RESISTANCE, source1);
	Resonator* RX = new Resonator(new Coil(), DEFAULT_RESISTANCE, source2);
	
	RX->translateCoil(0.0, 0.0, 0.1);//put some distance between them
	TX->sendBroadcastMessage("test");
	
	printf("Received Message: '%s'\n",RX->getMailBox());
	
	delete RX; delete TX;
	GC->destroyEnvironment();
}
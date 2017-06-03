/*
Sample described on Usage section of the paper.
*/ 

#include "example.h"



void example5(){
	
	GlobalCoupler* GC = GlobalCoupler::getInstance(4, DEFAULT_PERMEABILITY, F_100KHZ);//creating the environment
	
	complexDouble source1;
	source1.real = DEFAULT_SOURCE_VOLTAGE;
	source1.imag = 0.0;
	
	complexDouble source2;
	source2.real = 0.0;
	source2.imag = 0.0;
	
	//create three default coils with different impedances
	Resonator* TX1 = new Resonator(new Coil(), 10, source1);
	Resonator* TX2 = new Resonator(new Coil(), 7, source1);
	Resonator* TX3 = new Resonator(new Coil(), 9, source1);
	Resonator* RX = new Resonator(new Coil(), 5, source2);
	
	//pose the coils
	TX1->translateCoil(-DEFAULT_OUTTER_R, -DEFAULT_OUTTER_R*tan(PI/6), 0.0);
	TX2->translateCoil(DEFAULT_OUTTER_R, -DEFAULT_OUTTER_R*tan(PI/6), 0.0);
	TX3->translateCoil(0.0, DEFAULT_OUTTER_R/cos(PI/6), 0.0);
	RX->translateCoil(0.0, 0.0, 0.05);
	
	
	//impedance matching
	RX->sendBroadcastMessage("5");
	printf("Impedance Matching: Set resistance to %s ohms\n",TX1->getMailBox());
	TX1->updateResitance((double)atoi(TX1->getMailBox()));
	TX2->updateResitance((double)atoi(TX2->getMailBox()));
	TX3->updateResitance((double)atoi(TX3->getMailBox()));
	
	//move the RX coil over the square of 0.4x0.4 around the origin
	RX->translateCoil(-0.2, -0.2, 0.0);
	for(int i = 0; i<11; i++){
		for(int j = 0; j<11; j++){
			printf("\n(%d,%d) POWER: %f W\n",i,j,RX->getPower());
			RX->translateCoil(0.04, 0.0, 0.0);
		}
		RX->translateCoil(-0.44, 0.04, 0.0);
	}
	
	delete RX; delete TX1; delete TX2; delete TX3;
	GC->destroyEnvironment();
}
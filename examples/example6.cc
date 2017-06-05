/*
Sample described on Usage section of the paper.
*/ 

#include "example.h"
#define OPEN_CIRCUIT (1000000.0) //the resistance of open circuits
#define CLOSED_CIRCUIT (5.0) //the resistance of closed circuits


void example6(){
	
	GlobalCoupler* GC = GlobalCoupler::getInstance(4, DEFAULT_PERMEABILITY, F_100KHZ);//creating the environment
	
	complexDouble source1;
	source1.real = 3*DEFAULT_SOURCE_VOLTAGE;
	source1.imag = 0.0;
	
	complexDouble source0;
	source0.real = 0.0;
	source0.imag = 0.0;
	
	//create three default coils with different impedances
	Resonator* TX1 = new Resonator(new Coil(), 5, source1);
	Resonator* TX2 = new Resonator(new Coil(), 5, source1);
	Resonator* TX3 = new Resonator(new Coil(), 5, source1);
	Resonator* RX = new Resonator(new Coil(), 5, source0);
	
	//centers of the TX coils
	point cTX1;
	cTX1.x=-DEFAULT_OUTTER_R;cTX1.y=-DEFAULT_OUTTER_R*tan(PI/6);cTX1.z=0.0;
	point cTX2;
	cTX2.x=DEFAULT_OUTTER_R;cTX2.y=-DEFAULT_OUTTER_R*tan(PI/6);cTX2.z=0.0;
	point cTX3;
	cTX3.x=0.0;cTX3.y=DEFAULT_OUTTER_R/cos(PI/6);cTX3.z=0.0;
	
	//pose the coils
	TX1->translateCoil(cTX1.x, cTX1.y, cTX1.z);
	TX2->translateCoil(cTX2.x, cTX2.y, cTX2.z);
	TX3->translateCoil(cTX3.x, cTX3.y, cTX3.z);
	RX->translateCoil(0.0, 0.0, 0.05);
	
	//move the RX coil over the square of 0.4x0.4 around the origin
	point cRX; cRX.x = -0.2; cRX.y = -0.2; cRX.z = 0.05;
	RX->translateCoil(-0.2, -0.2, 0.0);
	
	for(int i = 0; i<11; i++){
		for(int j = 0; j<11; j++){
			TX1->updateResistance(OPEN_CIRCUIT);
			TX2->updateResistance(OPEN_CIRCUIT);
			TX3->updateResistance(OPEN_CIRCUIT);
			
			if(distance(cRX, cTX1)<distance(cRX, cTX2)){
				if(distance(cRX, cTX1)<distance(cRX, cTX3)){
					TX1->updateResistance(CLOSED_CIRCUIT);
					printf("<Coil TX1 selected>");
				}else{
					TX3->updateResistance(CLOSED_CIRCUIT);
					printf("<Coil TX3 selected>");
				}
			}else{
				if(distance(cRX, cTX2)<distance(cRX, cTX3)){
					TX2->updateResistance(CLOSED_CIRCUIT);
					printf("<Coil TX2 selected>");
				}else{
					TX3->updateResistance(CLOSED_CIRCUIT);
					printf("<Coil TX3 selected>");
				}
			}
			
			//printf("\n(%d,%d) POWER: %f W\n",i,j,RX->getPower());
			printf("M2(%d,%d) = %f;\n",i+1,j+1,RX->getPower());
			
			cRX.x+=0.04;
			RX->translateCoil(0.04, 0.0, 0.0);
		}
		cRX.x-=0.44;cRX.y+=0.04;
		RX->translateCoil(-0.44, 0.04, 0.0);
	}
	
	delete RX; delete TX1; delete TX2; delete TX3;
	GC->destroyEnvironment();
}
/*
Simple example to test the mutual coupling and efficience
calculations. Change the value of 'VERBOSE' on constants.h
to print the values of the mutual inductance in (1.0e-5)H.
Keep it on 0 to print just the power on each coil.
*/ 

#include "example.h"

#define USE_DEFAULT_DATA 1
#define RESISTANCE 100

#if USE_DEFAULT_DATA
void initializeDefaultMatrix(double L, Matrix& M){
	M(1,1) = RESISTANCE; M(2,2) = RESISTANCE;
	M(1,2) = L; M(2,1) = L;
}

Matrix** initiateDefaultData(){
	Matrix** DATA = (Matrix**)malloc(7*sizeof(Matrix*));
	for(int i=0;i<7;i++) DATA[i] = new Matrix(2,2);
	initializeDefaultMatrix(835.467225,*(DATA[0]));
	initializeDefaultMatrix(470.738684,*(DATA[1]));
	initializeDefaultMatrix(287.711538,*(DATA[2]));
	initializeDefaultMatrix(185.318196,*(DATA[3]));
	initializeDefaultMatrix(124.454980,*(DATA[4]));
	initializeDefaultMatrix(86.610612,*(DATA[5]));
	initializeDefaultMatrix(62.170492,*(DATA[6]));
	return DATA;
}
#endif

void example3(){
	
	double radius = 0.15;
	int nSpires = 22;
	double length = 0.022;
	double wireRadius = 0.0009;
	double pitch = (length-wireRadius)/nSpires;
	
	double permeability = 0.47 * DEFAULT_PERMEABILITY; //adjusted to fit the data
	
	GlobalCoupler* GC = GlobalCoupler::getInstance(2, permeability, 589*F_1KHZ);//creating the environment
	
	complexDouble source1;
	source1.real = DEFAULT_SOURCE_VOLTAGE;
	source1.imag = 0.0;
	
	complexDouble source2;
	source2.real = 0.0;
	source2.imag = 0.0;
	
	//creates a solenoid coil
	Coil* c1 = new Coil(radius, nSpires, pitch, wireRadius,DEFAULT_RESISTIVITY, DEFAULT_PERMEABILITY);
	Coil* c2 = new Coil(radius, nSpires, pitch, wireRadius,DEFAULT_RESISTIVITY, DEFAULT_PERMEABILITY);
	
	Resonator* TX = new Resonator(c1, RESISTANCE, source1);
	Resonator* RX = new Resonator(c2, RESISTANCE, source2);
	
	#if USE_DEFAULT_DATA
		int j=0;
		Matrix** DATA = initiateDefaultData();
	#else
		RX->translateCoil(0.0, 0.0, length);//translate the length of the coil, so the coils start side by side
	#endif
	for(double i=0.02;i<=0.32;i+=0.05){
		#if USE_DEFAULT_DATA
			GC->updatePartialZMatrix(*(DATA[j]));//o erro está nessa chamada
			j++;
		#else
			RX->translateCoil(0.0, 0.0, 0.05);
		#endif
		printf(" TX: %f W | RX: %f W\n", TX->getPower(),RX->getPower());
	}
	
	delete RX; delete TX;
	GC->destroyEnvironment();
}
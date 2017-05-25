/*Multiple examples to test all the new modules*/
#include <stdio.h>
#include "GlobalCoupler.h"
#include "Coil.h"

int main(){
	GlobalCoupler* GC = GlobalCoupler::getInstance(2, DEFAULT_PERMEABILITY, DEFAULT_FREQUENCY);//creating the environment
	
	Coil* C1 = new Coil(); Coil* C2 = new Coil();//creating default coils
	
	//setting voltage source configurations
	complexDouble source1; source1.real = DEFAULT_SOURCE_VOLTAGE; source1.imag = 0.0;
	complexDouble source2; source2.real = 0.0; source2.imag = 0.0;
	
	int id1 = GC->addNode(*C1,DEFAULT_RESISTANCE,source1);
	int id2 = GC->addNode(*C2,DEFAULT_RESISTANCE,source2);
	
	printf("%d %d\n",id1,id2);
	
	//cleaning everything
	delete C1; delete C2;
	GC->destroyEnvironment();
	return 0;
}
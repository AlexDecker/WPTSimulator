#include "Resonator.h"

Resonator::Resonator(GlobalCoupler* environment, Coil& coil, double resistance,
	complexDouble sourceVoltage){
	if(environment!=NULL){
		GC = environment;
		nodeId = GC->addNode(coil, resistance, sourceVoltage);
	}else{
		//showError
	}
}

complexDouble
Resonator::getCurrent(){
	return GC->getCurrent(nodeId);
}

double
Resonator::getCapacitance(){
	return GC->getCapacitance(nodeId);
}

void
Resonator::updateSourceVoltage(complexDouble newVoltage){
	GC->updateSourceVoltage(nodeId, newVoltage);
}

/*void Resonator::requireGlobalFrequencyUpdate(double newFrequency){
	GC->updateFrequency(newFrequency);
}*/

void
Resonator::updateResitance(double newResistance){
	GC->updateResitance(nodeId, newResistance);
}

void
Resonator::rotateCoil(AXIS axis, double teta){
	GC->rotateCoil(nodeId, axis, teta);
}

void
Resonator::translateCoil(double dx, double dy, double dz){
	GC->translateCoil(nodeId, dx, dy, dz);
}
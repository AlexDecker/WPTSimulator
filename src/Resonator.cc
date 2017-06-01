#include "Resonator.h"

Resonator::Resonator(Coil* coil, double newResistance,
	complexDouble newSourceVoltage){
	environment = GlobalCoupler::getInstance();
	if(environment!=NULL)
		if(coil!=NULL){
			coilRef = coil;
			nodeId = environment->addNode(*coil, newResistance,
				newSourceVoltage);
			resistance = newResistance;
		}else{
			showError("Resonator: NULL coil.");
		}
}

complexDouble
Resonator::getCurrent(){
	return environment->getCurrent(nodeId);
}

double
Resonator::getCapacitance(){
	return environment->getCapacitance(nodeId);
}

double
Resonator::getPower(){
	complexDouble i = getCurrent();
	return resistance*(pow(i.imag,2)+pow(i.real,2));
}

void
Resonator::updateSourceVoltage(complexDouble newVoltage){
	environment->updateSourceVoltage(nodeId, newVoltage);
}

void Resonator::requireGlobalFrequencyUpdate(double newFrequency){
	environment->updateFrequency(newFrequency);
}

void
Resonator::updateResitance(double newResistance){
	environment->updateResitance(nodeId, newResistance);
	resistance = newResistance;
}

void
Resonator::rotateCoil(AXIS axis, double teta){
	environment->rotateCoil(nodeId, axis, teta);
}

void
Resonator::translateCoil(double dx, double dy, double dz){
	environment->translateCoil(nodeId, dx, dy, dz);
}

Resonator::~Resonator(){
	delete coilRef;
}
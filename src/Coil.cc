#include "../lib/Coil.h"

Coil::Coil(){
	createCoil(DEFAULT_INNER_R, DEFAULT_OUTTER_R, DEFAULT_NSPIRES);
	calculateCoilSelfParams(DEFAULT_PERMEABILITY, DEFAULT_RESISTIVITY, DEFAULT_WIRE_RADIUS);
}

Coil::Coil(pointVector points, double wireRadius, double resistivity, double permeability){
	setPointVector(points);
	calculateCoilSelfParams(permeability, resistivity, wireRadius);
}

Coil::Coil(pointVector points, double newResistance, double newL){
	setPointVector(points);
	setInnerResitance(newResistance);
	setSelfInductance(newL);
}

Coil::Coil(double innerRadius, double outterRadius, int nSpires, double wireRadius,
	double resistivity, double permeability){
	if((innerRadius<=0.0)||(outterRadius<=innerRadius)||(nSpires<1)){
		NS_LOG_UNCOND("Coil constructor: Wrong coil geometric params.");
		return;
	}
	createCoil(innerRadius, outterRadius, nSpires);
	calculateCoilSelfParams(permeability, resistivity, wireRadius);
}

Coil::~Coil(){
	emxDestroyArray_real_T(pointsX);
	emxDestroyArray_real_T(pointsY);
	emxDestroyArray_real_T(pointsZ);
}

void
Coil::rotateCoil(AXIS axis, double teta){

}

void
Coil::translateCoil(double dx, double dy, double dz){
	if(dx!=0.0){
		for (int i = 0; i < pointsX->size[1U]; i++) {
			pointsX->data[pointsX->size[0] * i] += dx;
		}
	}
	if(dy!=0.0){
		for (int i = 0; i < pointsY->size[1U]; i++) {
			pointsY->data[pointsY->size[0] * i] += dy;
		}
	}
	if(dz!=0.0){
		for (int i = 0; i < pointsZ->size[1U]; i++) {
			pointsZ->data[pointsZ->size[0] * i] += dz;
		}
	}
}


void
Coil::setPointVector(pointVector points){
	if(points.size!=COIL_RESOLUTION){
		NS_LOG_UNCOND("Coil constructor: Wrong coil resolution.");
		return;
	}
	static int size[2] = { 1, COIL_RESOLUTION };
	pointsX = emxCreateND_real_T(2, size);
	pointsY = emxCreateND_real_T(2, size);
	pointsZ = emxCreateND_real_T(2, size);
	for(int i=0;i<COIL_RESOLUTION;i++){
		pointsX->data[pointsX->size[0] * i] = points.data[i].x;
		pointsY->data[pointsY->size[0] * i] = points.data[i].y;
		pointsZ->data[pointsZ->size[0] * i] = points.data[i].z;
	}
}

pointVector
Coil::getPointVector(){
	pointVector ret
	ret.data = (pointVector) malloc(sizeof(point)*pointsX->size[1U]);
	for (int i = 0; i < pointsX->size[1U]; i++) {
		ret[i].x = pointsX->data[pointsX->size[0] * i];
		ret[i].y = pointsY->data[pointsY->size[0] * i];
		ret[i].z = pointsZ->data[pointsZ->size[0] * i];
	}
	return ret;
}

double
Coil::getInnerResistance(){
	return resitance;
}

double
Coil::getSelfInductance(){
	return selfInductance;
}

void
Coil::setInnerResitance(double newResistance){
	if(newResistance>0.0)
		resistance = newResistance;
	else{
		NS_LOG_UNCOND("Coil constructor: The inner resistance must be a positive real number.");
		return;
	}
}

void
Coil::setSelfInductance(double newL){
	if(newL>0.0)
		selfInductance = newL;
	else{
		NS_LOG_UNCOND("Coil constructor: The self inductance must be a positive real number.");
		return;
	}
}

void
Coil::createCoil(double innerRadius, double outterRadius, int nSpires){
	static int size[2] = { 1, COIL_RESOLUTION };
	pointsX = emxCreateND_real_T(2, size);
	pointsY = emxCreateND_real_T(2, size);
	pointsZ = emxCreateND_real_T(2, size);
	
	double delta = (outterRadius-innerRadius)/nSpires;
	double tetaMin = innerRadius*nSpires*2*PI/(outterRadius-innerRadius);
	double tetaMax = outterRadius*nSpires*2*PI/(outterRadius-innerRadius);
	
	double teta = tetaMin; double step = (tetaMax-tetaMin)/COIL_RESOLUTION;
	
	for(int i=0;i<COIL_RESOLUTION;i++){
		pointsX->data[pointsX->size[0] * i] = delta*teta*cos(teta)/(2*PI);
		pointsY->data[pointsY->size[0] * i] = delta*teta*sin(teta)/(2*PI);
		pointsZ->data[pointsZ->size[0] * i] = 0.0;
		teta = (teta+step>=tetaMax)?tetaMax:teta+step;
	}
}

void
Coil::calculateCoilSelfParams(double permeability, double resistivity,
	double wireRadius){
	//ToDo
}
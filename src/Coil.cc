#include "Coil.h"

Coil::Coil(){
	createCoil(DEFAULT_INNER_R, DEFAULT_OUTTER_R, DEFAULT_NSPIRES);
	calculateCoilSelfParams(DEFAULT_PERMEABILITY, DEFAULT_RESISTIVITY, DEFAULT_WIRE_RADIUS);
	updated = false;
}

Coil::Coil(pointVector points, double wireRadius, double resistivity, double permeability){
	setPointVector(points);
	calculateCoilSelfParams(permeability, resistivity, wireRadius);
	updated = false;
}

Coil::Coil(pointVector points, double newResistance, double newL){
	setPointVector(points);
	setInnerResitance(newResistance);
	setSelfInductance(newL);
	updated = false;
}

Coil::Coil(double innerRadius, double outterRadius, int nSpires, double wireRadius,
	double resistivity, double permeability){
	if((innerRadius<=0.0)||(outterRadius<=innerRadius)||(nSpires<1)){
		showError("Coil constructor: Wrong geometric coil params.");
		return;
	}
	createCoil(innerRadius, outterRadius, nSpires);
	calculateCoilSelfParams(permeability, resistivity, wireRadius);
	updated = false;
}

Coil::Coil(double radius, int nSpires, double pitch, double wireRadius,
	double resistivity, double permeability){
	if((radius<=0.0)||(pitch<=0.0)||(nSpires<1)){
		showError("Coil constructor: Wrong geometric coil params.");
		return;
	}
	
	static int size[2] = { 1, COIL_RESOLUTION };
	pointsX = emxCreateND_real_T(2, size);
	pointsY = emxCreateND_real_T(2, size);
	pointsZ = emxCreateND_real_T(2, size);
	
	double teta = 0; double teta1 = 2*PI*nSpires; double delta = teta1/COIL_RESOLUTION;
	for(int i=0;i<COIL_RESOLUTION;i++){
		pointsX->data[pointsX->size[0] * i] = radius*cos(teta);
		pointsY->data[pointsY->size[0] * i] = radius*sin(teta);
		pointsZ->data[pointsZ->size[0] * i] = teta/(2*PI)*pitch;
		teta = (teta+delta>teta1)?teta1:teta+delta;
	}
	calculateCoilSelfParams(permeability, resistivity, wireRadius);
	updated = false;
}

Coil::~Coil(){
	emxDestroyArray_real_T(pointsX);
	emxDestroyArray_real_T(pointsY);
	emxDestroyArray_real_T(pointsZ);
}

void
Coil::rotateCoil(AXIS axis, double teta){
	int x,y,z,x1,y1,z1;
	if(teta!=0.0){
		updated=false;
		switch(axis){
			case AXIS_X:
				for (int i = 0; i < pointsX->size[1U]; i++) {
					x = pointsX->data[pointsX->size[0] * i];
					y = pointsY->data[pointsY->size[0] * i];
					z = pointsZ->data[pointsZ->size[0] * i];
					
					x1 = x;
					y1 = cos(teta)*y-sin(teta)*z;
					z1 = sin(teta)*y+cos(teta)*z;
					
					pointsX->data[pointsX->size[0] * i] = x1;
					pointsY->data[pointsY->size[0] * i] = y1;
					pointsZ->data[pointsZ->size[0] * i] = z1;
				}
				break;
			case AXIS_Y:
				for (int i = 0; i < pointsX->size[1U]; i++) {
					x = pointsX->data[pointsX->size[0] * i];
					y = pointsY->data[pointsY->size[0] * i];
					z = pointsZ->data[pointsZ->size[0] * i];
					
					x1 = cos(teta)*x+sin(teta)*z;
					y1 = y;
					z1 = -sin(teta)*x+cos(teta)*z;
					
					pointsX->data[pointsX->size[0] * i] = x1;
					pointsY->data[pointsY->size[0] * i] = y1;
					pointsZ->data[pointsZ->size[0] * i] = z1;
				}
				break;
			case AXIS_Z:
				for (int i = 0; i < pointsX->size[1U]; i++) {
					x = pointsX->data[pointsX->size[0] * i];
					y = pointsY->data[pointsY->size[0] * i];
					z = pointsZ->data[pointsZ->size[0] * i];
					
					x1 = cos(teta)*x-sin(teta)*y;
					y1 = sin(teta)*x+cos(teta)*y;
					z1 = z;
					
					pointsX->data[pointsX->size[0] * i] = x1;
					pointsY->data[pointsY->size[0] * i] = y1;
					pointsZ->data[pointsZ->size[0] * i] = z1;
				}
				break;
		}
	}
}

void
Coil::translateCoil(double dx, double dy, double dz){
	if(dx!=0.0){
		updated=false;
		for (int i = 0; i < pointsX->size[1U]; i++) {
			pointsX->data[pointsX->size[0] * i] += dx;
		}
	}
	if(dy!=0.0){
		updated=false;
		for (int i = 0; i < pointsY->size[1U]; i++) {
			pointsY->data[pointsY->size[0] * i] += dy;
		}
	}
	if(dz!=0.0){
		updated=false;
		for (int i = 0; i < pointsZ->size[1U]; i++) {
			pointsZ->data[pointsZ->size[0] * i] += dz;
		}
	}
}

void
Coil::setUpdated(){
	updated = true;
}

bool
Coil::isUpdated(){
	return updated;
}

void
Coil::setPointVector(pointVector points){
	if(points.size!=COIL_RESOLUTION){
		showError("Coil constructor: Wrong coil resolution.");
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
	pointVector ret;
	ret.data = (point*) malloc(sizeof(point)*pointsX->size[1U]);
	for (int i = 0; i < pointsX->size[1U]; i++) {
		ret.data[i].x = pointsX->data[pointsX->size[0] * i];
		ret.data[i].y = pointsY->data[pointsY->size[0] * i];
		ret.data[i].z = pointsZ->data[pointsZ->size[0] * i];
	}
	return ret;
}

double
Coil::getInnerResistance(){
	return resistance;
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
		showError("Coil constructor: The inner resistance must be a positive real number.");
		return;
	}
}

void
Coil::setSelfInductance(double newL){
	if(newL>0.0)
		selfInductance = newL;
	else{
		showError("Coil constructor: The self inductance must be a positive real number.");
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
	//default:
	wireRadius = 0.0;
	resistance = 0.0;
	selfInductance = 0.0;
	//PRECISION CONTROL:
	//the resistance must be multiplied by 0.001 because of the mOHM*m resistivity
	//the same must be done for the selfInductace, because of the same reason
	
	//ToDo
}
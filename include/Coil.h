#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "constants.h"
#include "util.h"
#include "inductance_neuman_emxAPI.h"

#ifndef COIL_H
#define COIL_H

class Coil{

	public:
	//Constructors
		//Creates a spiral coil with default params (0.1,0.2,10,0.001,R_COPPER,P_VACUUM)
		Coil();
		//Creates a generic coil. Its geometry will be defined by interconnecting the (x,y,z) points with lines.
		Coil(pointVector points, double wireRadius, double resistivity, double permeability);
		//Creates a generic coil. Sets the internal resistence and selfInductance, instead of calculating it.
		Coil(pointVector points, double newResistance, double newL);
		//Creates a spiral coil over the XY plane. The coil will be centered in the origin of the coordinates.
		Coil(double innerRadius, double outterRadius, int nSpires, double wireRadius,
			double resistivity, double permeability);
		//Creates a solenoid coil
		Coil(double radius, int nSpires, double pitch, double wireRadius,
			double resistivity, double permeability);
	//Destructor
		~Coil();
	//Geometric operations
		//Rotates the coil counter-clockwise. The 'axis' param may be AXIS_X, AXIS_Y or AXIS_Z
		void rotateCoil(AXIS axis, double teta);
		void translateCoil(double dx, double dy, double dz);
		void setUpdated();//set if the mutual coupling between this coil and all
		//the others is already up to date, after proceduring a geometric operation
		bool isUpdated();
	//Gets
		pointVector getPointVector();
		double getInnerResistance();
		double getSelfInductance();
	//The points are public to facilitate the Mutual Inductance calculation
		emxArray_real_T* pointsX;
		emxArray_real_T* pointsY;
		emxArray_real_T* pointsZ;
//*********************************************************************
	private:
		double wireRadius;
		double resistance;
		double selfInductance;
		
		bool updated;
		
		void calculateCoilSelfParams(double permeability, double resistivity,
			double wireRadius);
		void setPointVector(pointVector points);//create and set the coil's geometry
		void setInnerResitance(double newResistance);
		void setSelfInductance(double newL);
		void createCoil(double innerRadius, double outterRadius, int nSpires);
};
#endif
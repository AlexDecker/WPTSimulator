#ifndef CONSTANTS_H
#define CONSTANTS_H

//various
#define VERBOSE 0 //if not 0, print the mutual inductance values in
//(1.0e-5)H and the elapsed time in seconds
#define COIL_RESOLUTION (1000) //number of points that define a coil
#define PI (3.1415926535)
#define F_1KHZ (1.0e+3)
#define F_10KHZ (1.0e+4)
#define F_100KHZ (1.0e+5)
#define F_1MHZ (1.0e+6)
#define F_3MHZ (3.0e+6)
#define NS3 0 //if 1, enable doxygen

//default simulation values
#define DEFAULT_RESISTANCE  (50.0) //(Ohm)
#define DEFAULT_MUTUAL_COUPLING (0.0) //(Henry)
#define DEFAULT_SOURCE_VOLTAGE (1.0) //(Volt)
#define DEFAULT_FREQUENCY F_1KHZ
#define DEFAULT_PERMEABILITY P_VACUUM
#define DEFAULT_RESISTIVITY R_COPPER

//default coil params (m)
#define DEFAULT_INNER_R (0.1)
#define DEFAULT_OUTTER_R (0.2)
#define DEFAULT_NSPIRES (5) //(adimensional)
#define DEFAULT_WIRE_RADIUS (0.001)

//resistivity (mOHM*m) table at 20?C
//(http://hyperphysics.phy-astr.gsu.edu/hbase/Tables/rstiv.html)
#define R_SILVER (1.59e-5)
#define R_COPPER (1.68e-5)
#define R_ALUMINIUM (2.65e-5)
#define R_TUNGSTEN (5.6e-5)
#define R_IRON (9.71e-5)
#define R_PLATINUM (10.6e-5)

//magnetic permeability (mN/A2)
#define P_VACUUM (PI*4.0e-4)

#endif
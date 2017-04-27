Class Coil{

	public:
	//Constructors
		//Creates a spiral coil with default params (0.1,0.2,10,0.001,R_COPPER,P_VACUUM)
		Coil();
		//Creates a generic coil. Its geometry will be defined by interconnecting the (x,y,z) points with lines.
		Coil(pointVector points, double wireRadius, double resistivity, double permeability);
		//Creates a generic coil. Sets the internal resistence and selfInductance, instead of calculating it.
		Coil(pointVector points, double resistance, double selfInductance);
		//Creates a spiral coil over the XY plane. The coil will be centered in the origin of the coordinates.
		Coil(double innerRadius, double outterRadius, double nSpires, double wireRadius,
			double resistivity, double permeability);
	//Destructor
		~Coil();
	//Geometric operations
		//Rotates the coil counter-clockwise. The 'axis' param may be AXIS_X, AXIS_Y or AXIS_Z
		void rotateCoil(AXIS axis, double teta);
		
		void translateCoil(double dx, double dy, double dz);
	//Gets
		pointVector getPointVector();
		double getInnerResistance();
		double getSelfInductance();
//*********************************************************************
	private:


};

#include "GlobalCoupler.h"

static GlobalCoupler*
GlobalCoupler::getInstance(int nNodes=2, double permeability=DEFAULT_PERMEABILITY, double frequency=DEFAULT_FREQUENCY){
	if(Instance==NULL){
		if(nNodes>1){
			CapacitanceMatrix = new Matrix(nNodes);
			CapacitanceMatrix.set(DEFAULT_CAPACITANCE);

		  	ResistanceMatrix = new Matrix(nNodes);
		  	CapacitanceMatrix.set(DEFAULT_RESISTANCE);

		  	Matrix MutualCouplingMatrix = new Matrix(nNodes,nNodes);
		  	CapacitanceMatrix.set(DEFAULT_MUTUAL_COUPLING);
		  	
		  	SourceVoltage.imag = new Matrix(nNodes);
		  	SourceVoltage.real = new Matrix(nNodes);
		  	SourceVoltage.imag.set(0.0);
		  	SourceVoltage.real.set(DEFAULT_SOURCE_VOLTAGE);
		  	
		  	Current.imag = new Matrix(nNodes);
		  	Current.real = new Matrix(nNodes);
		  	Current.imag.set(0.0);
		  	Current.real.set(0.0);
			
			if(env_permeability>0.0)
				env_permeability = permeability;
			else{
				NS_LOG_UNCOND("GlobalCoupler: The permeability must be more then 0.0.");
				return NULL;
			}
			
			w = 2*PI*DEFAULT_FREQUENCY;
			updateFrequency(frequency);
			
			Instance = new GlobalCoupler();
			coilContainer = (Coil*)malloc(nNodes*sizeof(Coil));
		}else{
			NS_LOG_UNCOND("GlobalCoupler: Number of nodes must be greater then one.");
			return NULL;
		}
	}
	return Instance;
}

complexDouble
GlobalCoupler::getCurrent(int nodeId){
	if((nodeId>=0)&&(nodeId<nodesUpToNow)){
		
		updateMutualInductances();//if the coils aren't modified, this command
		//do nothing
		
		if(!allTheSame)calculateCurrents();//Check if it must to recalculate the values

		complexDouble ret;
		ret.real = Current.real(nodeId);
		ret.imag = Current.imag(nodeId);
		return ret;
	}else{
		NS_LOG_UNCOND("GlobalCoupler: Invalid nodeId.");
		return NULL;
	}
}

void 
GlobalCoupler::updateSourceVoltage(int nodeId, complexDouble newVoltage){
	if((nodeId>=0)&&(nodeId<nodesUpToNow)){
		SourceVoltage.real(nodeId) = newVoltage.real;
		SourceVoltage.imag(nodeId) = newVoltage.imag;
	}else{
		NS_LOG_UNCOND("GlobalCoupler: Invalid nodeId.");
		return;
	}
}

void
GlobalCoupler::void updateFrequency(double frequency){
	if((frequency>=F_1KHZ)&&(frequency<=F_3MHZ))
		w = 2*PI*frequency;
	else{
		NS_LOG_UNCOND("GlobalCoupler: The global resonant frequency must be between 1KHz and 3MHz.");
		return;
	}
}

void
GlobalCoupler::updateResitance(int nodeId, double newResistance){
	if((nodeId>=0)&&(nodeId<nodesUpToNow)){
		if(newResistance>0.0)
			partialZMatrix(nodeId, nodeId) = newResistance;
		else{
			NS_LOG_UNCOND("GlobalCoupler: The resistance must be a positive real number.");
			return;
		}
	}else{
		NS_LOG_UNCOND("GlobalCoupler: Invalid nodeId.");
		return;
	}
}

bool
GlobalCoupler::updatePartialZMatrix(complexMatrix newMetrix){
	if((newMetrix.rRow()==MutualCouplingMatrix.nRow())&&
		(newMetrix.nCol()==MutualCouplingMatrix.nCol())){
			MutualCouplingMatrix = newMetrix;
	}else{
		NS_LOG_UNCOND("GlobalCoupler: The size of the new matrix must agree with the old one.");
		return false;
	}
	return true;
}

void
GlobalCoupler::calculateCurrents(){
	int nNodes = partialZMatrix.nRow();
	if(nNodes!=nodesUpToNow){
		NS_LOG_UNCOND("GlobalCoupler: All nodes must be defined before any calculation.");
		return;
	}
	complexMatrix Z, Z_inv;
	Z.real = new Matrix(nNodes,nNodes);//creates the Z matrix
	Z.imag = new Matrix(nNodes,nNodes);
	Z_inv.real = new Matrix(nNodes,nNodes);//creates the inverse matrix
	Z_inv.imag = new Matrix(nNodes,nNodes);

	//calculates the Z matrix
	for(int i=0; i<nNodes; i++){
		for(int j=0; j<nNodes; j++){
			if(i==j){
				Z.real(i,j) = partialZMatrix(i,j)
					+coilCOntainer[i].getInnerResistance();
				Z.imag(i,j) = 0.0;//resonance ensures purely resistive impedance
			}else{
				//multiplying the frequency and the permeability first helps to
				//avoid imprecisions due very low values.
				Z.imag(i,j) = -(w*env_permeability)*partialZMatrix(i,j)/(4*PI);
				Z.real(i,j) = 0.0;
			}
		}
	}
	
	//calculates the inverse of the matrix
	cinv(Z.real, Z.imag, Z_inv.real, Z_inv.imag);
	
	for(int i=0; i<Current.real.nRow(); i++){
		Current.real(i) = 0.0;
		Current.imag(i) = 0.0;
		for(int j=0; j<Z.real.nCol();j++){
			Current.real(i) += SourceVoltage.real(j)*Z.real(i,j)
				-SourceVoltage.imag(j)*Z.imag(i,j);
			Current.imag(i) += SourceVoltage.real(j)*Z.imag(i,j)
				+SourceVoltage.imag(j)*Z.real(i,j);
		}
	}
}

void 
GlobalCoupler::rotateCoil(int nodeId,AXIS axis, double teta){
	if((nodeId<0)||(nodeId>=nodesUpToNow)){
		NS_LOG_UNCOND("GlobalCoupler: Invalid nodeId.");
		return;
	}
	coilContainer[nodeId].rotateCoil(axis,teta);
}

GlobalCoupler::void translateCoil(int nodeId, double dx, double dy, double dz){
	if((nodeId<0)||(nodeId>=nodesUpToNow)){
		NS_LOG_UNCOND("GlobalCoupler: Invalid nodeId.");
		return;
	}
	coilContainer[nodeId].translateCoil(axis,dx,dy,dz);
}

int
GlobalCoupler::addNode(Coil& coil,double resistance, complexDouble sourceVoltage){
	if(nNodes==nodesUpToNow){
		NS_LOG_UNCOND("GlobalCoupler: All nodes yet have been defined.");
		return -1;
	}
	allTheSame=false;
	coilContainer[nodesUpToNow]=coil;
	updateSourceVoltage(nodesUpToNow, sourceVoltage);
	updateResitance(nodesUpToNow, resistance);
	nodesUpToNow++;
}

void 
GlobalCoupler::calculateMutualInductance(int id1, int id2){
	if((id1<0)||(id2<0)||(id1>=partialZMtrix.nRow())
		||(id2>=partialZMtrix.nRow())){
		NS_LOG_UNCOND("GlobalCoupler: Index of the partialZMatrix is out of the bounds.");
		return;
	}
	partialZMatrix(id1,id2) = inductance_neuman(coilContainer[id1].getX(), 
		coilContainer[id1].getY(), coilContainer[id1].getZ(),
		coilContainer[id2].getX(), coilContainer[id2].getY(),
		coilContainer[id2].getZ());
	partialZMatrix(id2,id1) = partialZMatrix(id1,id2);
}

void
GlobalCoupler::updateMutualInductances(){
	bool allTheSame=true;
	int nNodes = partialZMatrix.nRow();//partialZMatrix is sqare
	//the matrix is symmetric, so we must only calculate the inferior triangle
	for(int i=0; i<nNodes; i++){
		for(int j=0; j<i; j++){
			if((!coilContainer[i].isUpdated())
				||(!coilContainer[j].isUpdated()){
				partialZMatrix(i,j) = calculateMutualInductance(i,j);
				allTheSame=false;//if at least one coil is modified, all
				//current calculations must be performed again next time.
			}
		}
	}
	//copy the correspondent values to the superior triangle
	//and set the coils updated
	for(int i=0; i<nNodes; i++){
		coilContainer[i].setUpdated();
		for(int j=i+1; j<nNodes-i; j++){
			partialZMatrix(i,j) = partialZMatrix(j,i);
		}
	}
}

double
getCapacitance(int nodeId){
	double L = coilContainer[nodeId].getSelfInductance();
	if(L==0.0){
		NS_LOG_UNCOND("GlobalCoupler: ooil's self inductance cannot be zero.");
		return 0.0;
	}
	return 1000.0/(L*(w*w));
}
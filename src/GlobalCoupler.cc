#include "../lib/GlobalCoupler.h"

static GlobalCoupler*
GlobalCoupler::getInstance(int nNodes=2){
	if(Instance==NULL){
		if(nNodes>1){
			Instance = new GlobalCoupler();
			
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
		}else{
			NS_LOG_UNCOND("GlobalCoupler: Number of nodes must be greater then one.");
			return NULL;
		}
	}
	return Instance;
}

complexDouble
GlobalCoupler::getCurrent(int nodeId){
	if((nodeId>=0)&&(nodeId<Current.real.nRow())){
		
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
GlobalCoupler::updateVoltageSource(int nodeId, complexDouble newVoltage){
	if((nodeId>=0)&&(nodeId<SourceVoltage.real.nRow())){
		SourceVoltage.real(nodeId) = newVoltage.real;
		SourceVoltage.imag(nodeId) = newVoltage.imag;
	}else{
		NS_LOG_UNCOND("GlobalCoupler: Invalid nodeId.");
		return;
	}
}

void
GlobalCoupler::updateCapacitance(int nodeId, double newCapacitance){
	if((nodeId>=0)&&(nodeId<CapacitanceMatrix.nRow())){
		CapacitanceMatrix(nodeId) = newCapacitance;
	}else{
		NS_LOG_UNCOND("GlobalCoupler: Invalid nodeId.");
		return;
	}
}

void
GlobalCoupler::updateResitance(int nodeId, double newResistance){
	if((nodeId>=0)&&(nodeId<ResistanceMatrix.nRow())){
		ResistanceMatrix(nodeId) = newResistance;
	}else{
		NS_LOG_UNCOND("GlobalCoupler: Invalid nodeId.");
		return;
	}
}

void
GlobalCoupler::updateMutualCouplingMatrix(complexMatrix newMetrix){
	if((newMetrix.rRow()==MutualCouplingMatrix.nRow())&&
		(newMetrix.nCol()==MutualCouplingMatrix.nCol())){
			MutualCouplingMatrix = newMetrix;
	}else{
		NS_LOG_UNCOND("GlobalCoupler: The size of the new matrix must agree with the old one.");
		return;
	}
}

void
GlobalCoupler::calculateCurrents(){
	int nNodes = MutualCouplingMatrix.nRow();
	complexMatrix Z, Z_inv;
	Z.real = new Matrix(nNodes,nNodes);//creates the Z matrix
	Z.imag = new Matrix(nNodes,nNodes);
	Z_inv.real = new Matrix(nNodes,nNodes);//creates the inverse matrix
	Z_inv.imag = new Matrix(nNodes,nNodes);

	for(int i=0; i<MutualCouplingMatrix.nRow(); i++){
		for(int j=0; j<MutualCouplingMatrix.nCol(); j++){
			if(i==j){

			}else{
				Z.imag(i,j) = -
			}
		}
	}
}

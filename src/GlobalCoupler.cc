#include "../lib/GlobalCoupler.h"

static GlobalCoupler*
GlobalCoupler::getInstance(int nNodes=2){
	if(Instance==NULL){
		if(nNodes>1){
			Instance = new GlobalCoupler();
			
			CapacitanceMatrix = new Matrix(n);
			CapacitanceMatrix.set(DEFAULT_CAPACITANCE);

		  	ResistanceMatrix = new Matrix(n);
		  	CapacitanceMatrix.set(DEFAULT_RESISTANCE);

		  	Matrix MutualCouplingMatrix = new Matrix(n,n);
		  	CapacitanceMatrix.set(DEFAULT_MUTUAL_COUPLING);
		  	
		  	SourceVoltage.imag = new Matrix(n);
		  	SourceVoltage.real = new Matrix(n);
		  	SourceVoltage.imag.set(0.0);
		  	SourceVoltage.real.set(DEFAULT_SOURCE_VOLTAGE);
		  	
		  	Current.imag = new Matrix(n);
		  	Current.real = new Matrix(n);
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

}

void
GlobalCoupler::calculateCurrents(){

}

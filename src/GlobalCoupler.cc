#include "GlobalCoupler.h"


GlobalCoupler* GlobalCoupler::Instance = NULL;
int GlobalCoupler::nodesUpToNow = 0;
Matrix* GlobalCoupler::partialZMatrix;
complexMatrix GlobalCoupler::SourceVoltage;
complexMatrix GlobalCoupler::Current;
double GlobalCoupler::w;
bool GlobalCoupler::allTheSame;
double GlobalCoupler::env_permeability;
Coil* GlobalCoupler::coilContainer;


GlobalCoupler*
GlobalCoupler::getInstance(){
	if(GlobalCoupler::Instance==NULL){
		showError("GlobalCoupler: You must specify the params in the first time you use this function.");
	}
	return GlobalCoupler::Instance;
}

GlobalCoupler*
GlobalCoupler::getInstance(int nNodes, double permeability, double frequency){
	if(GlobalCoupler::Instance==NULL){
		if(nNodes>1){
			GlobalCoupler::partialZMatrix = new Matrix(nNodes,nNodes);
		  	GlobalCoupler::partialZMatrix->set(DEFAULT_MUTUAL_COUPLING);
			for(int i=1;i<=nNodes;i++)
				(*GlobalCoupler::partialZMatrix)(i,i) = DEFAULT_RESISTANCE;
		  	
		  	GlobalCoupler::SourceVoltage.imag = new Matrix(nNodes);
		  	GlobalCoupler::SourceVoltage.real = new Matrix(nNodes);
		  	GlobalCoupler::SourceVoltage.imag->set(0.0);
		  	GlobalCoupler::SourceVoltage.real->set(DEFAULT_SOURCE_VOLTAGE);
		  	
		  	GlobalCoupler::Current.imag = new Matrix(nNodes);
		  	GlobalCoupler::Current.real = new Matrix(nNodes);
		  	GlobalCoupler::Current.imag->set(0.0);
		  	GlobalCoupler::Current.real->set(0.0);
			
			if(permeability>0.0)
				GlobalCoupler::env_permeability = permeability;
			else{
				showError("GlobalCoupler: The permeability must be more then 0.0.");
				return NULL;
			}
			
			GlobalCoupler::w = 2*PI*DEFAULT_FREQUENCY;
			updateFrequency(frequency);
			
			GlobalCoupler::Instance = new GlobalCoupler();
			GlobalCoupler::coilContainer = (Coil*)malloc(nNodes*sizeof(Coil));
			inductance_neuman_initialize();
			
			GlobalCoupler::allTheSame=false;
			GlobalCoupler::nodesUpToNow=0;
		}else{
			showError("GlobalCoupler: Number of nodes must be greater then one.");
			return NULL;
		}
	}
	return GlobalCoupler::Instance;
}

complexDouble
GlobalCoupler::getCurrent(int nodeId){
	if((nodeId>=0)&&(nodeId<nodesUpToNow)){
		
		updateMutualInductances();//if the coils aren't modified, this command
		//do nothing
		
		if(!GlobalCoupler::allTheSame)calculateCurrents();//Check if it must to recalculate the values

		complexDouble ret;
		ret.real = (*GlobalCoupler::Current.real)(nodeId+1);
		ret.imag = (*GlobalCoupler::Current.imag)(nodeId+1);
		return ret;
	}else{
		showError("GlobalCoupler: Invalid nodeId.");
		complexDouble ret;
		ret.real = 0.0;
		ret.imag = 0.0;
		return ret;
	}
}

void 
GlobalCoupler::updateSourceVoltage(int nodeId, complexDouble newVoltage){
	if((nodeId>=0)&&(nodeId<GlobalCoupler::nodesUpToNow)){
		(*GlobalCoupler::SourceVoltage.real)(nodeId+1) = newVoltage.real;
		(*GlobalCoupler::SourceVoltage.imag)(nodeId+1) = newVoltage.imag;
	}else{
		showError("GlobalCoupler: Invalid nodeId.");
		return;
	}
}

void
GlobalCoupler::updateFrequency(double frequency){
	if((frequency>=F_1KHZ)&&(frequency<=F_3MHZ))
		GlobalCoupler::w = 2*PI*frequency;
	else{
		showError("GlobalCoupler: The global resonant frequency must be between 1KHz and 3MHz.");
		return;
	}
}

void
GlobalCoupler::updateResitance(int nodeId, double newResistance){
	if((nodeId>=0)&&(nodeId<GlobalCoupler::nodesUpToNow)){
		if(newResistance>0.0)
			(*GlobalCoupler::partialZMatrix)(nodeId+1, nodeId+1) = newResistance;
		else{
			showError("GlobalCoupler: The resistance must be a positive real number.");
			return;
		}
	}else{
		showError("GlobalCoupler: Invalid nodeId.");
		return;
	}
}

bool
GlobalCoupler::updatePartialZMatrix(Matrix& newMetrix){
	if((newMetrix.nRow()==GlobalCoupler::partialZMatrix->nRow())&&
		(newMetrix.nCol()==GlobalCoupler::partialZMatrix->nCol())){
			(*GlobalCoupler::partialZMatrix) = newMetrix;
			return true;
	}else{
		showError("GlobalCoupler: The size of the new matrix must agree with the old one.");
		return false;
	}
}

void
GlobalCoupler::calculateCurrents(){
	int nNodes = GlobalCoupler::partialZMatrix->nRow();
	if(nNodes!=GlobalCoupler::nodesUpToNow){
		showError("GlobalCoupler: All nodes must be defined before any calculation.");
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
				(*Z.real)(i+1,j+1) = (*GlobalCoupler::partialZMatrix)(i+1,j+1)
					+coilContainer[i].getInnerResistance();
				(*Z.imag)(i+1,j+1) = 0.0;//resonance ensures purely resistive impedance
			}else{
				//multiplying the frequency and the permeability first helps to
				//avoid imprecisions due very low values.
				(*Z.imag)(i+1,j+1) = -(GlobalCoupler::w * GlobalCoupler::env_permeability)
										*(*partialZMatrix)(i+1,j+1)/(4*PI*1000);
				//the 1/1000 factor is udes in order to control the precision of
				//the calculations. The mN/A2 permeability (instead of N/A2) avoids
				//the use of overly small numbers
				(*Z.real)(i+1,j+1) = 0.0;
			}
		}
	}
	
	//calculates the inverse of the matrix
	cinv((*Z.real), (*Z.imag), (*Z_inv.real), (*Z_inv.imag));
	
	for(int i=1; i<=GlobalCoupler::Current.real->nRow(); i++){
		(*GlobalCoupler::Current.real)(i) = 0.0;
		(*GlobalCoupler::Current.imag)(i) = 0.0;
		for(int j=1; j<=Z.real->nCol();j++){
			(*GlobalCoupler::Current.real)(i) += (*GlobalCoupler::SourceVoltage.real)(j)*(*Z.real)(i,j)
				-(*GlobalCoupler::SourceVoltage.imag)(j)*(*Z.imag)(i,j);
			(*GlobalCoupler::Current.imag)(i) += (*GlobalCoupler::SourceVoltage.real)(j)*(*Z.imag)(i,j)
				+(*GlobalCoupler::SourceVoltage.imag)(j)*(*Z.real)(i,j);
		}
	}
}

void 
GlobalCoupler::rotateCoil(int nodeId,AXIS axis, double teta){
	if((nodeId<0)||(nodeId>=GlobalCoupler::nodesUpToNow)){
		showError("GlobalCoupler: Invalid nodeId.");
		return;
	}
	GlobalCoupler::coilContainer[nodeId].rotateCoil(axis,teta);
}

void
GlobalCoupler::translateCoil(int nodeId, double dx, double dy, double dz){
	if((nodeId<0)||(nodeId>=GlobalCoupler::nodesUpToNow)){
		showError("GlobalCoupler: Invalid nodeId.");
		return;
	}
	GlobalCoupler::coilContainer[nodeId].translateCoil(dx,dy,dz);
}

int
GlobalCoupler::addNode(Coil& coil,double resistance, complexDouble sourceVoltage){
	int nNodes = GlobalCoupler::partialZMatrix->nRow();
	if(nNodes==GlobalCoupler::nodesUpToNow){
		showError("GlobalCoupler: All nodes yet have been defined.");
		return -1;
	}
	int id = GlobalCoupler::nodesUpToNow;
	GlobalCoupler::nodesUpToNow++;
	GlobalCoupler::allTheSame=false;
	GlobalCoupler::coilContainer[id]=coil;
	updateSourceVoltage(id, sourceVoltage);
	updateResitance(id, resistance);
	return id;
}

void 
GlobalCoupler::calculateMutualInductance(int id1, int id2){
	if((id1<0)||(id2<0)||(id1>=GlobalCoupler::partialZMatrix->nRow())
		||(id2>=GlobalCoupler::partialZMatrix->nRow())){
		showError("GlobalCoupler: Index of the partialZMatrix is out of the bounds.");
		return;
	}
	(*partialZMatrix)(id1+1,id2+1) = inductance_neuman(GlobalCoupler::coilContainer[id1].pointsX, 
		GlobalCoupler::coilContainer[id1].pointsY, GlobalCoupler::coilContainer[id1].pointsZ,
		GlobalCoupler::coilContainer[id2].pointsX, GlobalCoupler::coilContainer[id2].pointsY,
		GlobalCoupler::coilContainer[id2].pointsZ);
}

void
GlobalCoupler::updateMutualInductances(){
	GlobalCoupler::allTheSame=true;
	int nNodes = GlobalCoupler::partialZMatrix->nRow();//partialZMatrix is sqare
	//the matrix is symmetric, so we must only calculate the inferior triangle
	for(int i=0; i<nNodes; i++){
		for(int j=0; j<i; j++){
			if((!GlobalCoupler::coilContainer[i].isUpdated())
				||(!GlobalCoupler::coilContainer[j].isUpdated())){
				calculateMutualInductance(i,j);
				GlobalCoupler::allTheSame=false;//if at least one coil is modified, all
				//current calculations must be performed again next time.
			}
		}
	}
	//copy the correspondent values to the superior triangle
	//and set the coils updated
	for(int i=0; i<nNodes; i++){
		GlobalCoupler::coilContainer[i].setUpdated();
		for(int j=i+1; j<nNodes-i; j++){
			(*GlobalCoupler::partialZMatrix)(i+1,j+1) = (*GlobalCoupler::partialZMatrix)(j+1,i+1);
		}
	}
}

double
GlobalCoupler::getCapacitance(int nodeId){
	double L = GlobalCoupler::coilContainer[nodeId].getSelfInductance();
	if(L==0.0){
		showError("GlobalCoupler: coil's self inductance cannot be zero.");
		return 0.0;
	}
	return 1000.0/(L*(w*w));
}

void
GlobalCoupler::destroyEnvironment(){
	inductance_neuman_terminate();
	free(GlobalCoupler::coilContainer);
	delete GlobalCoupler::partialZMatrix;
	delete GlobalCoupler::SourceVoltage.real;
	delete GlobalCoupler::Current.real;
	delete GlobalCoupler::SourceVoltage.imag;
	delete GlobalCoupler::Current.imag;
}

void
GlobalCoupler::showError(const char* s){
	#if NS3
		NS_LOG_UNCOND(s);
	#else
		printf("%s\n",s);
	#endif
}
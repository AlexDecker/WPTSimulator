#include "util.h"

void
showError(const char* s){
	#if NS3
		NS_LOG_UNCOND(s);
	#else
		printf("%s\n",s);
	#endif
}

double
distance(point A, point B){
	return sqrt(pow(A.x-B.x,2)+pow(A.y-B.y,2)+pow(A.z-B.z,2));
}
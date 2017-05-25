#include "util.h"

void
showError(const char* s){
	#if NS3
		NS_LOG_UNCOND(s);
	#else
		printf("%s\n",s);
	#endif
}
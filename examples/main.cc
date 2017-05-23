/*Multiple examples to test all the new modules*/
#include <stdio.h>
#include "Matrix.h"

int main(){
	Matrix* m = new Matrix(2,2);
	m->set(1.0);
	(*m)(1,1) = 2.234;
	printf("%f\n",(*m)(1,1));
	printf("%f\n",(*m)(2,1));
	delete m;
	return 0;
}
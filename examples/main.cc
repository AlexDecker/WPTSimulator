/*Multiple examples to test all the new modules*/
#include <stdio.h>
#include "example.h"

int main(int argc, char* argv[]){
	if(argc!=2){
		printf("Usage:\nmake EXAMPLE=\"[example_number]\" run\n or: ./standalone [example_number]\n");
		return 0;
	}
	int ex = atoi(argv[1]);
	switch(ex){
		case 1:
			example1();
			break;
		case 2:
			example2();
			break;
		case 3:
			example3();
			break;
		case 4:
			example4();
			break;
		default:
			printf("Example %s not found.\n",argv[1]);
	}
	return 0;
}

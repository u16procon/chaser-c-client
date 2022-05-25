#include "proConnect.h"
#include "stdlib.h"
#include <stdio.h>

int main (int argc, char* argv[]) {
	if(argc < 2){
		printf("bad argment\n");
		return -1;
	}

	initConnect(argv[1], atoi(argv[2]), "‚ ‚ ");

	while(checkEnd() != -1){
		getReady();
		walkRight();
	}

	endGame();

	return 0;
}

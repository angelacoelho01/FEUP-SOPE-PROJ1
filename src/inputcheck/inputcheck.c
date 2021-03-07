#include "inputcheck.h"

void usageNotRight(){
    printf("usage: ./xmod [OPTIONS] MODE FILE/DIR\n");
	printf("   or  ./xmod [OPTIONS] OCTAL-MODE FILE/DIR\n\n");

//Define the description better
    printf(" OPTIONS: \n");
    printf("      '-v' : verbose mode\n");
    printf("      '-c' : verbose mode only for modifications\n");
    printf("      '-R' : recursivity on the directory\n");
    printf(" If more than one option write them like this for example: -vR\n");

}
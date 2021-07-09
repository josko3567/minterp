#include "minterp.h"
#include <windows.h>
#include <conio.h>

char * getinput(char * message, char * variable, short size){
	printf("%s", message);
	fgets(variable, sizeof(char) * size, stdin);
	sscanf(variable, "%[^\n]", variable);
}

int main(){
	char * buffer;
	char * input;
	char * output;
	//char * nulby = calloc(1024, sizeof(char));
	bool running = true;
	while(running){
		input = calloc(1024, sizeof(char));
		getinput("\n Input math: \n << ", input, 1024);
		minterp(input, &output);
		printf("\n >> %s", output);
		//memcpy(input, nulby, 1024);
		free(output);
		free(input);
		getch();
		system("cls");
	}
}
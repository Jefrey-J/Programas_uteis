#include <stdio.h>



typedef void (*CallBackType)();

void TesteCallback(CallBackType callback) {
	callback();
}

void CallBackFunciton() {
	printf("Callback called!\n"); 
}

int main(int argc, char **argv) {

	CallBackType cbf1 = CallBackFunciton; 
	
	TesteCallback(cbf1);
	return 0; 
}

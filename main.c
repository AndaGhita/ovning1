#include "uart.h" // inkluderar egna headerfil


int main(){ //deklarerar och initierar huvudfunktionen
  
	USART2_Init(); // ser till att etablera UART funktion från uart.c
	
	//test_setup();
	printf("Hello there from main function");
	while(1){ // loop som printar det vi efterfrågar
	
	}

}

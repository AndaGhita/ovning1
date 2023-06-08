#include "uart.h" // inkluderar vår lokala header och därmed dess innehåll

void USART2_Init(void){ // konstrurera vår UART funktion

 RCC->APB1ENR  |=  0x20000; // enablea clock access till UART2

 RCC->AHB1ENR   |=0x01; // enablea clock-access till Port A

 
GPIOA->MODER &=~0x00F0; // sätter PA2 och 3 i reset
GPIOA->MODER |= 0x00A0; //sätter PA2 och 3 i alternativ funktion

 GPIOA->AFR[0] &= ~0xFF00;//sätt typ av alternativ funktion till 7
 GPIOA->AFR[0] |= 0x7700;


USART2->BRR  =  0x0683; //hantera baud rate på utvecklingskortet
USART2->CR1  =  0x000C; //aktiverar Tx och Rx
USART2->CR2  =  0x000; // nollställer CR2
USART2->CR3  =  0x000; // nollställer CR3
USART2->CR1  |=  0x2000; // enable UART
	
	

}

int USART2_write(int ch){ // funktion för att skriva med UART

	while(!(USART2->SR & 0x0080)){}
	USART2->DR = (ch & 0xFF);
	
  return ch; //grundläggande funktion som skriver till registret om det är tpmt
}

int USART2_read(void){ // funktion för att läsa med UART
  while(!(USART2->SR & 0x0020)){}
	return USART2->DR; // grundlegande funktion som läser ifrån registret när det ej är tomt
}

struct __FILE { int handle; }; // en struktur för IO-händelser
FILE __stdin  = {0};
FILE __stdout = {1};
FILE __stderr = {2};


int fgetc(FILE *f) { 
    int c;

    c = USART2_read();      // läs karaktär ifrån terminal

    if (c == '\r') {        
        USART2_write(c);    // skriv karaktär  till terminal
        c = '\n';
    }

    USART2_write(c);       //echo 

    return c;
}



int fputc(int c, FILE *f) { //input funktionen 
    return USART2_write(c);  
}


int n;
char str[80];
		
void test_setup(void){ //test funktion
	
	printf("please enter a number: ");
	scanf("%d", &n);
	printf("the number entered is: %d\r\n", n);
	printf("please type a character string: ");
	gets(str);
	printf("the character string entered is: ");
	puts(str);
	printf("\r\n");
	
}

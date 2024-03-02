#include<lpc17xx.h>

unsigned int tohex[10]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
unsigned int i=0, j=0;
int main(){
	LPC_PINCON->PINSEL3 = 0X0;
	LPC_PINCON->PINSEL0=0;
	LPC_PINCON->PINSEL1=0;
	
	LPC_GPIO0->FIODIR=0Xff<<15;
	LPC_GPIO1->FIODIR=0Xf<<23;
	
	while(1){
		for (i=1;i<=4;i++){
			LPC_GPIO1->FIOPIN= (i-1)<<23;
			LPC_GPIO0->FIOPIN= tohex[i]<<15;
		}
	}
}

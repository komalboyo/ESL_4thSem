#include<lpc17xx.h>

unsigned int tohex[10]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
unsigned int i=0, j=0;
int a[4]={0,0,0,0};
int main(){
	LPC_PINCON->PINSEL3 = 0X0;
	LPC_PINCON->PINSEL0=0;
	LPC_PINCON->PINSEL1=0;
	
	LPC_GPIO0->FIODIR=0Xff<<15;						//data lines
	LPC_GPIO1->FIODIR=0Xf<<23;						//enable lines
	
	while(1){
		for(a[3]=0;a[3]<=9;a[3]++)
		{
			for(a[2]=0;a[2]<=9;a[2]++)
		   {
			   for(a[1]=0;a[1]<=9;a[1]++)
		      {
						for(a[0]=0;a[0]<=9;a[0]++)
		         {
			         for(i=0;i<4;i++)
							  {
									LPC_GPIO1->FIOPIN= i<<23;
									LPC_GPIO0->FIOPIN= tohex[a[i]]<<15;
									for(j=0;j<10000;j++);
								}
		         }
		      }
		   }
		}
	}
}

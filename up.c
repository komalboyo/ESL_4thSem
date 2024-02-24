#include <LPC17xx.h>
 
int main()
{
  unsigned int i,j;
  
  SystemInit();
  SystemCoreClockUpdate();
  
  LPC_PINCON->PINSEL0 &= 0X0;
  LPC_PINCON->PINSEL1 &= 0X0;
  
  LPC_GPIO0->FIODIR =0xFF<<15;
  
  while(1)
  { 
	  for(i=0;i<256;i++)
			{
				LPC_GPIO0->FIOPIN=i<<15;
				for(j=0;j<100000;j++);
			}
  }
}
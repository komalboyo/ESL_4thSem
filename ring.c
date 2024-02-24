#include <LPC17xx.h>
 
int main()
{
  unsigned long LED = 0x80;
  unsigned int i,j;
	unsigned int x;
  
  SystemInit();
  SystemCoreClockUpdate();
  
  LPC_PINCON->PINSEL0 &= 0X0;
  LPC_PINCON->PINSEL1 &= 0X0;
  
  LPC_GPIO0->FIODIR =0xFF<<15 | 0xFF<<15;
  
  while(1)
  {
		x=LPC_GPIO0->FIOPIN>>10;
		x&=1;  
		LPC_GPIO0->FIOPIN=LED<<15;
		for(j=0;j<100000;j++);
	  if(x==1)
		{ LED=LED>>1;
        if(LED==0)
				  LED=0X80;
		}
		else
		{
			 LED=LED<<1;
			  if(LED>0X80)
					 LED=1;
		}
  }
}
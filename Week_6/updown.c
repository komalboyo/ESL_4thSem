#include <LPC17xx.h>
 
int main()
{
  unsigned int x;
  unsigned int i,j;
  
  SystemInit();
  SystemCoreClockUpdate();
  
  LPC_PINCON->PINSEL0 &= 0X0;
  LPC_PINCON->PINSEL1 &= 0X0;
  
  LPC_GPIO0->FIODIR =0<<10 | 0xFF<<15;
  
  while(1)
  {
    x=LPC_GPIO0->FIOPIN>>10;
		x&=1;  
	  if(x==1)
		{
			for(i=0;i<256;i++)
			{
				LPC_GPIO0->FIOPIN=i<<15;
				for(j=0;j<100000;j++);
			}
		}
		else
		{
			for(i=255;i>0;i--)
			{
				LPC_GPIO0->FIOPIN=i<<15;
				for(j=0;j<100000;j++);
			}
		}
  }
}
//keep switch pressed its like a doorbell, top make switch 1 you have to keep it pressed
//this code will complete 256 numbers up/down at one stretch only then you can change
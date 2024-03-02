#include<lpc17xx.h>

unsigned int tohex[10]={0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
unsigned int i,cur=0,j , x;
unsigned int a[4]={0,0,0,0};
int main(){
	LPC_PINCON->PINSEL3 = 0X0;
	LPC_PINCON->PINSEL0=0;
	LPC_PINCON->PINSEL1=0;
	
	LPC_GPIO0->FIODIR=0Xff<<15|0<<10;						//data lines
	LPC_GPIO1->FIODIR=0Xf<<23;						//enable lines
	
	while(1){
		x=LPC_GPIO0->FIOPIN>>10;
		x&=1;
		a[0]=cur%10;
    a[1]=(cur/10)%10;
    a[2]=(cur/100)%10;
    a[3]=cur/1000;		
	  for(i=0;i<=3;i++)
    {
      LPC_GPIO1->FIOPIN=i<<23;
      LPC_GPIO0->FIOPIN=tohex[a[i]]<<15;
      for(j=0;j<10000;j++);		
    }			
		
		if(x==1)
		{
		  cur++;
			if(cur>9999)
				cur=0;
	  }
		else
		{
			if(cur==0)
				cur=9999;
			else
		  cur--;
		}
	}
}

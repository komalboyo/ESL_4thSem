#include<LPC17xx.h>

void lcd_init(void);
void write(int, int);
//void delay_lcd(unsigned int);
void inittime0();
void delay(int milliseconds);
void lcd_com(int, int);
void clear_ports(void);
void lcd_puts(unsigned char *);
//lcd initialization
void lcd_init()
			{
			/*Ports initialized as GPIO */
			LPC_PINCON->PINSEL1 &= 0xFC003FFF; //P0.23 to P0.28
			/*Setting the directions as output */
			LPC_GPIO0->FIODIR |= 0x0F<<23 | 1<<27 | 1<<28;
			clear_ports();
			delay(3200);
			lcd_com(0x33, 0);
			delay(30000);
			lcd_com(0x32, 0);
			delay(30000);
			lcd_com(0x28, 0); //function set
			delay(30000);
			lcd_com(0x0c, 0);//display on cursor off
			delay(800);
			lcd_com(0x06, 0); //entry mode set increment cursor right
			delay(800);
			lcd_com(0x01, 0); //display clear
			delay(10000);
			return;
			}
void lcd_com(int temp1, int type)
		{
		int temp2 = temp1 & 0xf0; //move data (26-8+1) times : 26 - HN place, 4 - Bits
		temp2 = temp2 << 19; //data lines from 23 to 26
		write(temp2, type);
		temp2 = temp1 & 0x0f; //26-4+1
		temp2 = temp2 << 23;
		write(temp2, type);
		delay(1000);
		return;
		}
void write(int temp2, int type) //write to command/data reg
			{
			clear_ports();
			LPC_GPIO0->FIOPIN = temp2; // Assign the value to the data lines
			if(type==0)
			LPC_GPIO0->FIOCLR = 1<<27; // clear bit RS for Command
			else
			LPC_GPIO0->FIOSET = 1<<27; // set bit RS for Data
			LPC_GPIO0->FIOSET = 1<<28; // EN=1
			delay(25);
			LPC_GPIO0->FIOCLR = 1<<28; // EN =0
			return;
			}
			
void inittime0(){
		LPC_TIM0->CTCR = 0x0;
		LPC_TIM0->TCR = 0x2;
		LPC_TIM0->PR = 2999;
}

void delay(int milliseconds){
		LPC_TIM0->TCR = 0x2;
		LPC_TIM0->TCR = 0x1;
		while(LPC_TIM0->TC < milliseconds);
		LPC_TIM0->TCR = 0x0;
}
			
/*
void delay_lcd(unsigned int r1)
		{
		unsigned int r;
		for(r=0;r<r1;r++);
		return;
		}
*/
			
void clear_ports(void)
		{
		/* Clearing the lines at power on */
		LPC_GPIO0->FIOCLR = 0x0F<<23; //Clearing data lines
		LPC_GPIO0->FIOCLR = 1<<27; //Clearing RS line
		LPC_GPIO0->FIOCLR = 1<<28; //Clearing Enable line
		return;
		}
void lcd_puts(unsigned char *buf1)
{
unsigned int i=0;
unsigned int temp3;
while(buf1[i]!='\0')
		{
		temp3 = buf1[i];
		lcd_com(temp3, 1);
		i++;
		if(i==16)
		{
		lcd_com(0xc0, 0);
		}

		}
return;
}
void scan(void);

unsigned char row,flag,key;
unsigned long int i,var1,temp1,temp,temp2,temp3;
unsigned char scan_code[16]={0x11,0x21,0x41,0x81,0x12,0x22,0x42,0x82,
	0x14,0x24,0x44,0x84,0x18,0x28,0x48,0x88};
unsigned char ascii_code[16]={'0','1','2','3','4','5',
	'6','7','8','9','A','B','+','-','*','/'};
int idx = 1;
int ans = 0;
unsigned char finans[3] = {'0','0','\0'};
int a = 0;
int b = 0;
char op;
int count = 0;

int main(void)
{
	LPC_GPIO2->FIODIR = 0x3c00;
	LPC_GPIO1->FIODIR = 0xf87fffff;
	lcd_init();
	temp1 = 0x80;
	lcd_com(temp1,0);
	delay(800);
	while(count<3)
	{
		while(1)
		{
			for(row=1; row<5; row++)
			{
				if(row==1)
					var1 = 0x400;
				else if(row==2)
					var1 = 0x800;
				else if(row==3)
					var1 = 0x1000;
				else if(row==4)
					var1 = 0x2000;
				temp = var1;
				LPC_GPIO2->FIOCLR = 0x3c00;
				LPC_GPIO2->FIOSET = var1;
				flag = 0;
				scan();
				if(flag==1)
				{
					count++;
					break;
				}
			}
			if(flag==1)
				break;
		}
		for(i=0; i<16; i++)
		{
			if(key==scan_code[i])
			{
				key = ascii_code[i];
				lcd_puts(&key);
				delay(50000);
				if(count==1)
					a = key-48;
				else if(count==2)
					op = key;
				else if(count==3)
					b = key-48;
				break;
			}
		}
	}
	temp1 = 0xc0;
	lcd_com(temp1,0);
	delay(800);
	switch(op)
	{
		case '+':
			ans = a+b;
			break;
		case '-':
			ans = a-b;
			break;
		case '*':
			ans = a*b;
			break;
		case '/':
			ans = a/b;
			break;
	}
	while(ans!=0)
	{
		finans[idx--] = (ans%10)+48;
		ans = ans/10;
	}
	lcd_puts(&finans[0]);
	return 0;
}

void scan(void)
{
	temp3 = LPC_GPIO1->FIOPIN;
	temp3 &= 0x07800000;
	if(temp3!=0)
	{
		flag = 1;
		temp3>>=19;
		temp>>=10;
		key = temp3|temp;
	}
}

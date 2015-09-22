#include<p18f4520.h>
//keyboard-----------------------------------------------------
//#define coloum1 PORTB
//#define row1 PORTC

void key_pressed();
void delay(unsigned int time);

unsigned char cur_col=0;
unsigned char prev_col=0;
unsigned char row=0;
unsigned char x[11]={'0','0','0','0','0','0','0','0','0','0','0'};
unsigned int time;
unsigned char temp;
unsigned int cnt=0;
rom unsigned char key[4][4]={ '1','2','3','A',
					'4','5','6','B',
					'7','8','9','C',
					'*','0','#','D'
				};
//unsigned char msg[]="Error";
unsigned char tmsg[]="Done!";
//LCD--------------------------------------------------------------

#define data PORTD
#define rs PORTAbits.RA1
#define rw PORTAbits.RA2
#define en PORTAbits.RA3

#define busy_flag PORTDbits.RD7
unsigned char display_msg[] = "Please enter no";
unsigned  int i=1;
unsigned char *pt=0;
void lcdcmd(unsigned char val);
void lcdready();
void lcddata(unsigned char *pt,unsigned int cnt);
void lcdinit();
//void lcddat(unsigned char vall);

void delay(unsigned int time);
//---------------------------------------------------------------------------
void lcdready()
{
	TRISD=0xFF;
	rs=0;
	rw=1;
	while(busy_flag==1)
	{
		en=1;
		delay(1);
		//if(!busy_flag)
		//	break;
		en=0;
	}
	TRISD=0x00;
}

//lcd initialisation----------------------------------------------------
void lcdinit()
{
		
	en=0;
	delay(25);
	
	lcdcmd(0x38);
	lcdready();
	//delay(20);
	
	lcdcmd(0x0E);
	lcdready();
	//delay(20);
	
	lcdcmd(0x06);
	//delay(20);
	lcdready();
	
	lcdcmd(0x01);
	delay(20);


		lcdcmd(0x02);
		delay(20);
}
//LCD Commands and Data-------------------------------------------------


void lcdcmd(unsigned char val)
{
	data= val;
	rs=0;
	rw=0;
	en=1;
	delay(1);
	en=0;
}
void lcddata(unsigned char *pt,unsigned int cnt)
{
	if(cnt==10)
	{	
	while(cnt!=0)
	{
		data=*pt;
	
	rs=1;
	rw=0;
	en=1;
	delay(1);
	en=0;
	pt++;
	cnt--;
	delay(20);
	}
	delay(3000);
	}
	while(cnt!=0)
	{
		data=*pt;
	
	rs=1;
	rw=0;
	en=1;
	delay(1);
	en=0;
	pt++;
	cnt--;
	delay(20);
	}
	
}



void delay(unsigned int time)
{
	unsigned int j,k;
	for(j=0;j<time;j++)
		for(k=0;k<40;k++);
}

//Keyboard------------------------------------------------------

void key_pressed()
{
	cur_col=0;
	prev_col = 0;
	PORTC=0x0E;
	if(PORTB!=0xF0)
	{	
		row=0;
		cur_col=0;
		prev_col = 0;
		temp=PORTB;
		temp ^=0xF0;
		if(!temp)
			return;
		while(temp>>=1)
			cur_col++;
// delay of 15 msec
// read portb, calc temp and fins col value again
//if prev col == curr col then it's a valid press
delay(1000);
	if(PORTB!=0xF0)
	{	
		temp=PORTB;
		temp ^=0xF0;
		if(!temp)
			return;
		while(temp>>=1)
			prev_col++;
	}
	if(cur_col==prev_col)
	{
		while(PORTB!=0xF0);
		delay(2000);
		x[i-1]=key[row][cur_col];
		//x[i-1]=cur_col+0x30;	
		lcdcmd(0xC0);
		lcddata(x,i);
		i++;
	}	
		return;

	}	
	PORTC=0x0D;
	if(PORTB!=0xF0)
	{	
		row=1;	
		cur_col=0;
		prev_col = 0;
		temp=PORTB;
		temp ^=0xF0;
		if(!temp)
			return;
		while(temp>>=1)
			cur_col++;
delay(1000);		
	if(PORTB!=0xF0)
	{	
		temp=PORTB;
		temp ^=0xF0;
		if(!temp)
			return;
		while(temp>>=1)
			prev_col++;
	}
	if(cur_col==prev_col)
	{
		while(PORTB!=0xF0);
		x[i-1]=key[row][cur_col];
		delay(2000);
		//x[i] = i + 0x30;
		//x[i-1]=cur_col+0x30;
		lcdcmd(0xC0);
		lcddata(x,i);
		i++;
	}
		return;

	}	
	PORTC=0x0B;
	if(PORTB!=0xF0)
	{	
		row=2;
		cur_col=0;
		prev_col = 0;
		temp=PORTB;
		temp ^=0xF0;
		if(!temp)
			return;
		while(temp>>=1)
			cur_col++;
		
delay(1000);
	if(PORTB!=0xF0)
	{	
		temp=PORTB;
		temp ^=0xF0;
		if(!temp)
			return;
		while(temp>>=1)
			prev_col++;
	}
	if(cur_col==prev_col)
	{

	while(PORTB!=0xF0);
		delay(2000);
		x[i-1]=key[row][cur_col];
	//	x[i-1]=cur_col+0x30;
		lcdcmd(0xC0);
		lcddata(x,i);
		i++;
	}	
		return;
	}	
	PORTC=0x07;
	if(PORTB!=0xF0)
	{	
	
		row=3;
		cur_col=0;
		prev_col = 0;
		temp=PORTB;
		temp ^=0xF0;
		if(!temp)
			return;
		while(temp>>=1)
			cur_col++;
	delay(1000);	
		if(PORTB!=0xF0)
		{	
			temp=PORTB;
			temp ^=0xF0;
			if(!temp)
				return;
			while(temp>>=1)
				prev_col++;
		}
		if(cur_col==prev_col)
		{
	
			while(PORTB!=0xF0);
			delay(2000);
			x[i-1]=key[row][cur_col];
			//x[i-1]=cur_col+0x30;
			lcdcmd(0xC0);
			lcddata(x,i);
			i++;
		}
		return;
	}	
}
void main()
{
	ADCON1=0x0F;
	TRISAbits.TRISA0=1;

//LCD-----------------------------------------------------------
while(PORTAbits.RA0==0)
{	
		i=1;
		TRISD=0x00;
		TRISA=0x00;
		TRISC=0x00;
		PORTC=0x00;
		PORTD=0x00;	
		lcdinit();	
		lcdready();	
		lcddata(display_msg,15);
		lcdcmd(0xC0);
		delay(2000);

//keyboard----------------------------------
				
	while(i<11)
	{
		
		INTCON2bits.RBPU=0;
		TRISB=0xFF;
		//TRISBbits.TRISB0=1;
		TRISC=0x00;
		PORTC=0x00;
		while(PORTB==0xF0);
		key_pressed();
	}
	lcdinit();
	lcddata(tmsg,5);
	delay(6000);
}

}

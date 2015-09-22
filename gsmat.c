#include<p18f4520.h>

void INT_ISR( void );
void  srm( void );
void  xyz(rom unsigned char *pt);
void receive(rom unsigned char *pt_1,unsigned int );
int flag=0;
int rec_flag=0;
unsigned int Rec_char_cnt=0;
unsigned char rec_str[30];
rom unsigned char simcheck[]="AT+CPIN?";
rom unsigned char command1[5]="AT\n\r";
rom unsigned char smsmode[40]="AT+CMGF=1\n\r";
rom unsigned char smsmode_1[40]="AT+CMGS=";
rom unsigned char number[40]="9975707628";
rom unsigned char msg2[40]="YOU HAVE INTRUDER!!\n";
rom unsigned char ascii_doublequotes[2] = { 0x22, 0};
rom unsigned char ascii_newline[4] = {0x0D , 0x0A, 0 , 0};
rom unsigned char EndOfMsg = 0x1A;
rom unsigned char *pt;
rom unsigned char *pt_1;
rom unsigned char Resp_simcheck[]="0x0D0x0A+CPIN: READY";
rom unsigned char receivemsg[]="0x0D0x0A+CMGS";
rom unsigned char Resp_arrow[4]={0x0D,0x0A,'>',0x20};
rom unsigned char Resp_OK[6] = {0x0D,0x0A,'O','K',0x0D , 0x0A};
unsigned int time=0;
void delay(unsigned int time);

#pragma code InterruptVectorHigh = 0x08
void
InterruptVectorHigh (void)
{
  _asm
    goto INT_ISR //jump to interrupt routine
  _endasm
}
#pragma code
#pragma interrupt INT_ISR

void INT_ISR()
{
         if (INTCONbits.INT0IF && INTCONbits.INT0IE)
          {
				INTCONbits.INT0IF = 0;
				*pt=0;
				*pt_1=0;
     			flag=1;
       	  }
}
 void srm( void )
{
        xyz(command1);
		receive(Resp_OK,5);
		if(rec_flag==0)
			return;
		PORTD=0x01;
      
	/*	xyz(simcheck);
		receive(Resp_simcheck,15);
		if(rec_flag==0)
			return;
		receive(Resp_OK,5);
		if(rec_flag==0)
			return;
		xyz(command1);
		receive(Resp_OK,5);
		if(rec_flag==0)
			return;*/

		xyz(smsmode);
		receive(Resp_OK,5);
		if(rec_flag==0)
			return;
		PORTD=0x02;
        xyz(smsmode_1);
		xyz(ascii_doublequotes); 
        xyz(number);
		xyz(ascii_doublequotes); 
 		xyz(ascii_newline);
		receive(Resp_arrow,3);
		if(rec_flag==0)
			return;
		PORTD=0x04;
        xyz(msg2);
 		//xyz(ascii_newline);
   		TXREG=EndOfMsg;
		while(TXSTAbits.TRMT==0);
		receive(receivemsg,6);
		if(rec_flag==0)
			return;
		PORTD=0x08;
        flag=0;
		delay(1250);
}

void xyz(rom unsigned char *pt)
{
        while(*pt)
        {
            TXREG=*pt;
    		while(TXSTAbits.TRMT==0);	
        	*pt++;
			
        }   
    
        
}

void receive(rom unsigned char *pt_1,unsigned int Rec_char_cnt)
{
	unsigned int i = 0;
	rec_str[i] = RCREG;
	while(i<=Rec_char_cnt)
	{
		while(!PIR1bits.RCIF);
		rec_str[i] = RCREG;
		i++;
	}	


		i=0;
		while(i<=Rec_char_cnt)
		{
			if(rec_str[i]==*pt_1)
			{	
				*pt_1++;
				i++;
			}
			else
			{
				rec_flag=0;
				break;
			}
			
		}
//		if(rec_str[i]=='\0')
			rec_flag=1;
	
	
}
void delay(unsigned int time)
{
	unsigned int i,j;
	RCSTA = 0;
	for(i=0;i<time;i++)
	{
		PORTDbits.RD0 = ~PORTDbits.RD0;
		for(j=0;j<=300;j++);
	}
	PORTDbits.RD0 = 0;
	RCSTA = 0x90;

}


void main() 
{
			ADCON1 = 0x0F;           // AD converter off
       
            TRISB = 0xFF;            // Set PB0 as input
            TRISC = 0x00;            // Set Portc as output
			//TRISCbits.TRISC6=1;
			TRISD=0x00;
			PORTD=0x00;
			TRISCbits.TRISC7=1;
        	SPBRG=156;
        	TXSTA=0x24;
            RCSTA=0x90;            
            INTCONbits.INT0IF=0;
            INTCONbits.INT0IE=1;
            INTCONbits.GIE=1;

 			while(1)
                {       
							if(flag==1)
                                srm();
			    } 	         
                   

}

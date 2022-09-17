#include <16f887.h>
#device ADC=10 
#fuses XT,NOWDT,NOPROTECT,NOLVP,PUT,BROWNOUT,INTRC_IO  
#use delay(clock=8000000)  
#INCLUDE <LCD.C>

int16 duty=1023;
int16 read=0;
int16 temp=0;
int Timer2,Poscaler;
void main() { 
   LCD_INIT();     
   LCD_PUTC("\f");  
   Timer2=152;  
   Poscaler=1; 
   
   setup_timer_2(t2_div_by_1,Timer2,Poscaler);   
   setup_ccp1(ccp_pwm);              
   setup_adc_ports(all_analog);     
   setup_adc(adc_clock_internal);
   while(TRUE)
   {
        set_adc_channel(0);   
        delay_us(600);   
        read = read_adc();
        duty=read+temp;
        set_pwm1_duty(388);
        delay_us(600);  
        set_pwm1_duty(380);
        
        LCD_GOTOXY(1,1);        
        if((read>318)&&(read<343)){
            LCD_PUTC("Sistema estable");

            
        }
        if(read<319){
            LCD_PUTC("Nivel Bajo <");
            temp++;
            temp++;
        }
        if(read>342){
            LCD_PUTC("Nivel Alto >");
            temp--;
            temp--;
        }
        

        LCD_GOTOXY(1,2);      
        printf(LCD_PUTC, "%ld", read);
        printf(LCD_PUTC, " %ld", duty);
        LCD_PUTC("\f"); 
   }
}



#include <16f887.h>
#device ADC=10 
#fuses XT,NOWDT,NOPROTECT,NOLVP,PUT,BROWNOUT,INTRC_IO  
#use delay(clock=8000000) 
#INCLUDE <LCD.C>
#INCLUDE <math.h>

int16 duty=1023;
int16 read=0;
int16 fun=0;
int16 voltage=0;
int Timer2,Poscaler;
void main() { 
   LCD_INIT();       
   LCD_PUTC("\f");
   Timer2=152;   
   //
   setup_timer_2(t2_div_by_1,Timer2,Poscaler);  
   setup_ccp1(ccp_pwm);            
   setup_adc_ports(all_analog);       
   setup_adc(adc_clock_internal);
   while(TRUE)
   {
        set_adc_channel(0);   
        read = read_adc();
        duty=227;
        voltage = read*(20000/1023);
        //fun = -9.421*pow(10,-7)*pow(read,3)+0.002201*pow(read,2)-1.663*read+629.7;
        fun = 2.047*pow(10,-13)*pow(read,5)-2.841*pow(10,-10)*pow(read,4)-1.029*pow(10,-6)*pow(read,3)+0.002471*pow(read,2)-1.778*read+643.1;
        set_pwm1_duty(fun);
        LCD_GOTOXY(1,1);    
        LCD_PUTC("Vin[mV] = ");
        printf(LCD_PUTC, "%ld", voltage);
        LCD_GOTOXY(1,2);    
        printf(LCD_PUTC, "%ld", read);
        printf(LCD_PUTC, "-> %ld", fun);
        delay_ms(50);
        LCD_PUTC("\f"); 
   }
}


/*
 * PianitoLight.c
 *
 * Created: 13/03/2018 12:27:10 p. m.
 * Author: barby
 */

#include <mega328p.h>
float Frec[8]={261.3,293.6,329.6,349.2,391.9,440,493.8,523.2};

void Tono (float Frecuencia)
{
    float Cuentas;
    unsigned int CuentasEnteras;
    
    TCCR1A=0x40;    //Salida en OC1A
    TCCR1B=0x09;    //Modo de CTC sin pre-escalador
    
    Cuentas=500000.0/Frecuencia;
    CuentasEnteras=Cuentas;
        if((Cuentas-CuentasEnteras)>=0.5)
            CuentasEnteras++;
        
        OCR1AH=(CuentasEnteras-1)/256;
        OCR1AL=(CuentasEnteras-1)%256;
}

void noTono ()
{
    TCCR1A=0;   //Desconecta
    PORTB.1=0;  //Apaga timer
    PORTB.1=0; //Si solo dejo PORTB.1=0; el programa no me har� caso porque este regitro tienen un 40 (ese pin es toggle en compare_macth 
}

void main(void)
{
    PORTD=0xFF; //Pull-up de PD0 a PD7 switches
    DDRB.1=1; //PB1 de salida
    
while (1)
    {
        //Revisar switch por switch 
        
        //Do
        if(PIND.0==0)
        {
            Tono(Frec[0]);
            while(PIND.0==0); //Esperar hasta que deja de presionar
            noTono();
        }
        //Re
         if(PIND.1==0)
        {
            Tono(Frec[1]);
            while(PIND.1==0); //Esperar hasta que deja de presionar
            noTono();
        }
        //Mi
         if(PIND.2==0)
        {
            Tono(Frec[2]);
            while(PIND.2==0); //Esperar hasta que deja de presionar
            noTono();
        }
        //Fa
         if(PIND.3==0)
        {
            Tono(Frec[3]);
            while(PIND.3==0); //Esperar hasta que deja de presionar
            noTono();
        }  
        //Sol
         if(PIND.4==0)
        {
            Tono(Frec[4]);
            while(PIND.4==0); //Esperar hasta que deja de presionar
            noTono();
        }
       //La 
         if(PIND.5==0)
        {
            Tono(Frec[5]);
            while(PIND.5==0); //Esperar hasta que deja de presionar
            noTono();
        }
        //Si
         if(PIND.6==0)
        {
            Tono(Frec[6]);
            while(PIND.6==0); //Esperar hasta que deja de presionar
            noTono();
        }
        //Do*
         if(PIND.7==0)
        {
            Tono(Frec[7]);
            while(PIND.7==0); //Esperar hasta que deja de presionar
            noTono();
        }

    }
}

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
unsigned char i;

void noTono ()
{
    TCCR1A=0;   //Desconecta
    PORTB.1=0;  //Apaga timer
    PORTB.1=0; //Si solo dejo PORTB.1=0; el programa no me hará caso porque este regitro tienen un 40 (ese pin es toggle en compare_macth 
}

void main(void)
{
    PORTD=0xFF; //Pull-up de PD0 a PD7 switches
    DDRB.1=1; //PB1 de salida
    
while (1)
    {
        for(i=0;i<8;i++)
        {
            if(((PIND>>i)&0x01)==0) //PIND.i=0 (no me deja hacerlo el compilador)
            {
                Tono(Frec[i]);
                while(((PIND>>i)&0x01)==0); //Esperar hasta que deja de presionar
                noTono();
            }
        
        }
    }
}

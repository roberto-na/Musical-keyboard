/*
 * Pianito_Tarea.c
 *
 * Created: 13/03/2018 12:27:10 p. m.
 * Author: 
 */

#include <mega328p.h>
#include <delay.h>
#include <io.h>

unsigned long int msec=0,temp; 
unsigned char i;

float Frec[8]={261.3,293.6,329.6,349.2,391.9,440,493.8,523.2};
unsigned char j; //Contador de notas almacenadas
unsigned char Notas [100]; //Arreglo de notas
unsigned char Tiempo [100]; //Tiempo de las notas

// Timer2 output compare interrupt service routine
interrupt [TIM2_COMPA] void timer2_compa_isr(void)
{
  msec++;
}

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
    PORTB.1=0; //Si solo dejo PORTB.1=0; el programa no me hará caso porque este regitro tienen un 40 (ese pin es toggle en compare_macth 
}

void main(void)
{
    PORTD=0xFF; //Pull-up de PD0 a PD7 switches
    DDRB.1=1; //PB1 de salida 
    
    TCCR2A=0x02;
    TCCR2B=0x02;
    OCR2A=124;     
    TIMSK2=0x02;  
    #asm("sei")
    j=0;
    
    
while (1)
    {
        for (i=0; i<8;i++)
        {
            if(((PIND>>i)&0x01)==0)   //PIND.i==0
            {
                //Aquí no pongo los delay porque tardaré en hacerle caso al usuario 
                Tono(Frec[0]);
                delay_ms(30);
                Notas[j]=i;
                temp=msec;
                while(((PIND>>i)&0x01)==0); //Esperar hasta que deja de presionar
                Tiempo[j]=msec-temp;
                noTono(); 
                //Aquí pongo el delay ¡Woohoo!
                delay_ms(10);
                j++;
            }
       
         }
         
         //Revisar botón de clear (si está presionado: borro  j=0;)
         //Revisar el botón de PLAY (Si está presionado reproducir canción)
         //de k=0 a j-1
    }
}

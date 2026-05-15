#include <xc.h>

// CONFIGURATION BITS
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define _XTAL_FREQ 20000000

void main(void)
{
    // Disable Analog Inputs
   // ADCON1 = 0x06;

    // Set RB0 as Output
    TRISBbits.TRISB0 = 0;

    // Clear PORTB
    // PORTB = 0x00;

    while(1)
    {
        PORTBbits.RB0 = 1;   // LED ON
        __delay_ms(100);

        PORTBbits.RB0 = 0;   // LED OFF
        __delay_ms(100);
    }
}


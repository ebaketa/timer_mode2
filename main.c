// ********************************************************
// Program:     Timer mode 2
// Author:      Elvis Baketa
// Processor:   AT89C2051
// Oscillator:  12 MHz
// Compiler:    SDCC (Linux)
// Version:     0.1
// Source:      
// Comment:     timer mode 2, 8 bit, autoreload
// ********************************************************

#include <at89x051.h>
#include <stdint.h>

volatile uint16_t count = 0;

void Timer0_ISR(void) __interrupt (1) {
        count++;
}

int main()
{
    // declare and assign variable
    uint8_t led_state = 0;
    
    // run once    
    TMOD = 0x02;    // Timer mode 2
    TL0 = 0x00;     // Clear register
    TH0 = 0xCE;     // Set value to count from
    TR0 = 1;        // Set timer to run.
    ET0 = 1;        // Set interrupt.
    EA = 1;         // Set global interrupt.
    
    // loop forever
    while(1)
    {
        // count to 10000 for 1 second delay
        if (count == 10000)
        {
            // change LED state
            led_state = !led_state;
            count = 0;
        }
        
        // turn OFF or ON led
        if (led_state) {
            P1 = 0xFF;
        } else {
            P1 = 0x00;
        }
    }
}


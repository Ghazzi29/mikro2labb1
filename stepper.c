#include "gd32vf103.h"

#define CW 1
#define CCW 0

static int NROFSTEPS = 0;

void initStep(void){
    
    rcu_periph_clock_enable(RCU_GPIOA);//init klocka och pinnar
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,
              GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    //sätter alla pinnar till LOW vid init 
    gpio_bit_reset(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);        

}

void execStep(int cw){
 
    while (1)
    {
    gpio_bit_set(GPIOA, GPIO_PIN_0);
    for (volatile int i = 0; i < 100000; i++){}
    gpio_bit_set(GPIOA, GPIO_PIN_0 | GPIO_PIN_1);
    for (volatile int i = 0; i < 100000; i++){}

    gpio_bit_reset(GPIOA, GPIO_PIN_0);

    gpio_bit_set(GPIOA, GPIO_PIN_1 | GPIO_PIN_2);
    for (volatile int i = 0; i < 100000; i++){}

    gpio_bit_reset(GPIOA, GPIO_PIN_1);

    gpio_bit_set(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);
    for (volatile int i = 0; i < 100000; i++){}

    gpio_bit_reset(GPIOA, GPIO_PIN_2);

    gpio_bit_set(GPIOA, GPIO_PIN_0 | GPIO_PIN_3);
    for (volatile int i = 0; i < 100000; i++){}

    gpio_bit_reset(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    for (volatile int i = 0; i < 100000; i++){}

    }

     
}


/*

switch (cw)
    {
    case CW:

        switch (NROFSTEPS)
        {
        case 0:
            break;

        case 1:
            break;
        
        case 2:
            break;

        case 8:
            NROFSTEPS=0;
            break;
        }

        NROFSTEPS++;
        break;


    case CCW:
        break;

    default:
        break;
    }
    */
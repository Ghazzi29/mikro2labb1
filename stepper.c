#include "gd32vf103.h"

#define CW 1
#define CCW 0

static int CurrentStep = 0;

void initStep(void){
    
    rcu_periph_clock_enable(RCU_GPIOA);//init klocka och pinnar
    gpio_init(GPIOA, GPIO_MODE_OUT_PP, GPIO_OSPEED_50MHZ,
              GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    //sätter alla pinnar till LOW vid init 
    //gpio_bit_reset(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);        

}

void execStep(int cw){

    gpio_bit_reset(GPIOA, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3); 
    setStep(CurrentStep);

    if (cw==1){
        CurrentStep++;
    }
    else{
        CurrentStep--;
    }

    if (CurrentStep<0){
        CurrentStep=7;
    }
    else if(CurrentStep>7){
        CurrentStep=0;
    }
}    

void setStep(int n){
    switch(n){

        case 0:
            gpio_bit_set(GPIOA, GPIO_PIN_0);
            break;

        case 1:
            gpio_bit_set(GPIOA, GPIO_PIN_0 | GPIO_PIN_1);
            break;

        case 2:
            gpio_bit_set(GPIOA, GPIO_PIN_1);
            break;

        case 3:
            gpio_bit_set(GPIOA, GPIO_PIN_1 | GPIO_PIN_2);
            break;

        case 4:
            gpio_bit_set(GPIOA, GPIO_PIN_2);
            break;

        case 5:
            gpio_bit_set(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);
            break;                

        case 6:
            gpio_bit_set(GPIOA, GPIO_PIN_3);
            break;    

        case 7:
            gpio_bit_set(GPIOA, GPIO_PIN_0 | GPIO_PIN_3);    

    }
        
} 

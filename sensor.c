
#include "gd32vf103.h"

volatile int sensorTriggered = 0;
    
extern volatile int max_temp;
extern volatile int min_temp;
extern volatile int middle;
extern volatile int currentTemp; 
extern volatile int phase; 

void initSensorInterrupt(void) {

    // Enable clocks
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_AF);

    // Configure PA5 and PA6 as inputs with pull-up
    gpio_init(GPIOA, GPIO_MODE_IPU,
              GPIO_OSPEED_50MHZ,
              GPIO_PIN_5 | GPIO_PIN_6);

    // Connect PA5 to EXTI5
    gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOA,
                            GPIO_PIN_SOURCE_5);

    // Connect PA6 to EXTI6
    gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOA,
                            GPIO_PIN_SOURCE_6);

    // Detect both rising and falling edges
    exti_init(EXTI_5, EXTI_INTERRUPT, EXTI_TRIG_BOTH);
    exti_init(EXTI_6, EXTI_INTERRUPT, EXTI_TRIG_BOTH);

    // Clear pending interrupts
    exti_interrupt_flag_clear(EXTI_5);
    exti_interrupt_flag_clear(EXTI_6);

    // Enable shared interrupt in ECLIC
    eclic_irq_enable(EXTI5_9_IRQn, 1, 0);
}


// Interrupt handler for PA5 and PA6
void EXTI5_9_IRQHandler(void) {

    // Encoder channel A (PA5)
    if (exti_interrupt_flag_get(EXTI_5) != RESET) {

        sensorTriggered = 1;

        switch (phase)
        {
        case 0:
            currentTemp++;
            if (currentTemp==max_temp){phase++;}
            break;
        case 1:
            currentTemp--;
            if (currentTemp==min_temp){phase++;}
            break;
        case 2:
        currentTemp++;
        if (currentTemp==middle){phase++;}
            break;
        }

        exti_interrupt_flag_clear(EXTI_5);
    }

    // Encoder channel B (PA6)
    if (exti_interrupt_flag_get(EXTI_6) != RESET) {

        sensorTriggered = 1;

        exti_interrupt_flag_clear(EXTI_6);
    }
}

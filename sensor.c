#include "gd32vf103.h"

void initSensorInterrupt(void) {

    // Enable clocks
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_AF);

    // Configure PA4 as input with pull-down
    gpio_init(GPIOA, GPIO_MODE_IPD,
              GPIO_OSPEED_50MHZ, GPIO_PIN_4);

    // Connect PA4 to EXTI4
    gpio_exti_source_select(GPIO_PORT_SOURCE_GPIOA,
                            GPIO_PIN_SOURCE_4);

    // Configure rising-edge interrupt
    exti_init(EXTI_4, EXTI_INTERRUPT, EXTI_TRIG_RISING);

    // Clear pending interrupt
    exti_interrupt_flag_clear(EXTI_4);

    // Enable interrupt in ECLIC
    eclic_irq_enable(EXTI4_IRQn, 1, 0);
}

volatile int sensorTriggered = 0;

void EXTI4_IRQHandler(void) {

    if (exti_interrupt_flag_get(EXTI_4) != RESET) {

        sensorTriggered = 1;

        // Clear interrupt flag
        exti_interrupt_flag_clear(EXTI_4);
    }
}
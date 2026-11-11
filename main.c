#include "gd32vf103.h"
#include "stepper.h"
#include "sensor.h"

#define CW 1
#define CCW 0

// 0 går till max, 1 till min, 2 till mid, 3 sover

volatile int max_temp = 7;
volatile int min_temp = 0;
volatile int middle = 3;
volatile int currentTemp = 4;
volatile int phase = 0;

int main() {

    rcu_periph_clock_enable(RCU_GPIOB);

    // Initialize PB0 LED
    gpio_init(GPIOB, GPIO_MODE_OUT_PP,
              GPIO_OSPEED_50MHZ, GPIO_PIN_0);

    gpio_bit_reset(GPIOB, GPIO_PIN_0);

    initStep();

    // Interrupts
    initSensorInterrupt();
    eclic_global_interrupt_enable();

    int previousTemp = currentTemp;

    while (1) {

        // TEST: Toggle PB0 when temperature changes
        if (currentTemp != previousTemp) {

            if (gpio_output_bit_get(GPIOB, GPIO_PIN_0)) {
                gpio_bit_reset(GPIOB, GPIO_PIN_0);
            } else {
                gpio_bit_set(GPIOB, GPIO_PIN_0);
            }

            previousTemp = currentTemp;
        }

        switch (phase) {
            case 0:
                execStep(CW);
                break;

            case 1:
                execStep(CCW);
                break;

            case 2:
                execStep(CW);
                break;

            case 3:
                // sleep
                break;
        }

        for (volatile int i = 0; i < 100000; i++) {}
    }
}
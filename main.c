
#include "gd32vf103.h"
#include "stepper.h"
#include "sensor.h"
#include "drivers.h"

#define CW 1
#define CCW 0

// 0 = max, 1 = min, 2 = middle, 3 = stop

volatile int max_temp = 4;
volatile int min_temp = 0;
volatile int middle = 2;
volatile int currentTemp = 1;
volatile int phase = 0;

static int activeCol = 3;


// Initialize one fixed column
void initDisplay(void) {

    colinit();
    l88init();

    // colset() starts at 7 and counts down.
    // Four calls select column 3.
    for (int i = 0; i < 4; i++) {
        activeCol = colset();
    }

    // Start with all LEDs off in this column
    l88mem(activeCol, 0x00);
    l88row(activeCol);
}


// Display temperature using 0-8 LEDs
void displayTemp(int temp) {

    if (temp < 0) temp = 0;
    if (temp > 8) temp = 8;

    // Convert temperature to LED bitmask
    int pattern = (1 << temp) - 1;

    // Update only the selected column
    l88mem(activeCol, pattern);
    l88row(activeCol);
}


int main(void) {

    // Initialize hardware
    initStep();
    initDisplay();
    initSensorInterrupt();

    // Enable interrupts
    eclic_global_interrupt_enable();

    // Display initial temperature
    int previousTemp = currentTemp;
    displayTemp(previousTemp);

    while (1) {

        // Update LEDs only when temperature changes
        int temp = currentTemp;

        if (temp != previousTemp) {
            displayTemp(temp);
            previousTemp = temp;
        }

        // Motor control
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
                // Stop motor
                break;

            default:
                break;
        }
		for (volatile int i = 0; i < 50000; i++)
		{
			/* code */
		}
		
    }
}

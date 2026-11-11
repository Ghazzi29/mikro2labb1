#include "gd32vf103.h"
#include "stepper.h"
#include "sensor.h"
#include "drivers.h"

#define CW 1
#define CCW 0

int main(){

	volatile int max_temp = 7;
	volatile int min_temp = 0;
	volatile int middle = (max_temp + min_temp)/2;
	volatile int currentTemp = 4;
	volatile int phase = 0; 

	// 0 går till max, 1 till min 2 till mid, 3 sover

	rcu_periph_clock_enable(RCU_GPIOB);
	initStep();

	l88init();
	
	//interrups
	initSensorInterrupt();
	eclic_global_interrupt_enable();
	
	while(1){
		switch(phase){
			case 0:
				execStep(CW);
				currentTemp++;
				break;

			case 1:
				execStep(CCW);
				currentTemp--;
				break;
			
			case 2:
				execStep(CW);
				currentTemp++;
				if (currentTemp==middle){
					phase = 3;
				}
				break;

			case 3:
				//sleep
				break;	
		}
 		uint8_t pattern = tempToPattern(currentTemp);
		colinit();
		l88mem(0,pattern);

		for (volatile int i = 0; i < 100000; i++){}
	}
}

uint8_t tempToPattern(int currentTemp) {

    if (currentTemp < 0) currentTemp = 0;
    if (currentTemp > 7) currentTemp = 7;

    return (1U << currentTemp) - 1U;
}
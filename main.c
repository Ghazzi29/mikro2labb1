#include "gd32vf103.h"
#include "stepper.h"

#define CW 1
#define CCW 0

int main(){
	int max_steps = 0
	int min_steps = 0
	int middle_steps = 0

	int step = 0

	int phase = 0 
	// 0 går till max, 1 till min 2 till mid, 3 sover

	rcu_periph_clock_enable(RCU_GPIOB);
	
	initStep();

	while(1){
		switch(phase){
			case 0:
				execStep(CW)
				step++;
				break;

			case 1:
				execStep(CCW)
				step--;
				break;
			
			case 2:
				execStep(CW)
				step++
				if (step==middle_steps){
					phase = 3
				}
				break;

			case 3:
				break;	


		}
		for (volatile int i = 0; i < 100000; i++){}
	}
}

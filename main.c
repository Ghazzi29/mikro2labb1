#include "gd32vf103.h"
#include "stepper.h"

int main(){
	rcu_periph_clock_enable(RCU_GPIOB);
	
	initStep();
	execStep(1);
}

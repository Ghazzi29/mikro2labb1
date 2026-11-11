#ifndef SENSOR_H
#define SENSOR_H

extern volatile int sensorTriggered;
extern volatile int encoderA;
extern volatile int encoderB;

void initSensorInterrupt(void);
void EXTI5_9_IRQHandler(void);

#endif


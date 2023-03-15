
#ifndef FIRESYSTEM_H_
#define FIRESYSTEM_H_

#define REDLED PIND3
#define GREENLED PIND4
#define YELLOWLED PIND5

#define FANMOTOR M1
#define WATERMOTOR M2

extern void FIRESYS_Init(void);
extern void FIRESYS_Runnable(void);

#endif 
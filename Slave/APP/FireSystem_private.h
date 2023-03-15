


#ifndef FIRESYSTEM_PRIVATE_H_
#define FIRESYSTEM_PRIVATE_H_

#define TEMPMSG '3'
#define SMOKEMSG '4'
#define UNLOCKMSG    (u8)222

void FIRESYS_WriteTemp(u16 temp);
void FIRESYS_WritePressure(u16 pressure);
void Spi_Interrupt(void); 


#endif 
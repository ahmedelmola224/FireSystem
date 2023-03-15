#include "MemoryMap.h"
#include "Utils.h"
#include "StdTypes.h"
#include "DIO_interface.h"
#include "FireSystem.h"



int main(void)
{
	sei();
	FIRESYS_Init();
	while(1)
	{
		FIRESYS_Runnable();
		
		
	}
}






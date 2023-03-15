#include "MemoryMap.h"
#include "Utils.h"
#include "StdTypes.h"
#include "FireSystem.h"

int main(void)
{
	/***************slave***************/
	sei();
	FIRESYS_Init();
	while(1)
	{
		FIRESYS_Runnable();
	}
}






#include "StdTypes.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "MOTOR_interface.h"
#include "Sensors.h"
#include "LCD.h"
#include "SPI.h"
#include "FireSystem.h"
#include "FireSystem_private.h"

static  volatile u8 TempConfig=35;
static  volatile u8 SmokeConfig=50;
static volatile u8 FireFlag=0;

void FIRESYS_Init(void)
{
	DIO_Init();
	LCD_Init();
	ADC_Init(VREF_AREF,ADC_SCALER_64);
	MOTOR_Init();
	SPI_Init();
	SPI_SetCallBack(Spi_Interrupt);
	SPI_InterruptEnable();
}

void FIRESYS_Runnable(void)
{
	u16 temp=TEMP_Read();
	u16 pressure=PRESSURE_Read();
	FIRESYS_WriteTemp(temp);
	FIRESYS_WritePressure(pressure);
	if(FireFlag)
	{
		LCD_SetCursor(1,5);
		LCD_WriteString("FIRE");
		DIO_WritePin(GREENLED,LOW);
		DIO_WritePin(YELLOWLED,LOW);
		DIO_WritePin(REDLED,HIGH);
		MOTOR_Cw(WATERMOTOR);
		MOTOR_Stop(FANMOTOR);
	}
	else if(temp<=(TempConfig*10)-50)
	{
		LCD_SetCursor(1,5);
		LCD_WriteString("FINE");
		DIO_WritePin(GREENLED,HIGH);
		DIO_WritePin(YELLOWLED,LOW);
		DIO_WritePin(REDLED,LOW);
		MOTOR_Stop(FANMOTOR);
		MOTOR_Stop(WATERMOTOR);
	}
	else if(temp>=((TempConfig*10)))
	{
		if(pressure<((SmokeConfig*10)-50)||FireFlag==0)
		{
			LCD_SetCursor(1,5);
			LCD_WriteString("HEAT");
			DIO_WritePin(GREENLED,LOW);
			DIO_WritePin(YELLOWLED,HIGH);
			DIO_WritePin(REDLED,LOW);
			MOTOR_Cw(FANMOTOR);
			MOTOR_Stop(WATERMOTOR);
		}
		 if(pressure>=((SmokeConfig*10)))
		{
			DIO_WritePin(PINB0,HIGH);
			_delay_ms(1);
			DIO_WritePin(PINB0,LOW);
			FireFlag=1;
		}
		
	}
	
}

void FIRESYS_WriteTemp(u16 temp)
{
	LCD_SetCursor(0,0);
	LCD_WriteString("TEMP");
	LCD_SetCursor(1,0);
	LCD_WriteNumber(temp/10);
	LCD_WriteChar('.');
	LCD_WriteNumber(temp%10);
}

void FIRESYS_WritePressure(u16 pressure)
{
	LCD_SetCursor(0,11);
	LCD_WriteString("SMOKE");
	LCD_SetCursor(1,12);
	LCD_WriteNumber(pressure/10);
	LCD_WriteChar('.');
	LCD_WriteNumber(pressure%10);
	
}

void Spi_Interrupt(void)
{

	static u8 received_flag=0;
	u8 received=SPI_ReceieveNoBlock();
	if(received==UNLOCKMSG)
	{
		FireFlag=0;
	}
	if(received==TEMPMSG)
	{
		received_flag=TEMPMSG;
	}
	else if(received==SMOKEMSG)
	{
		received_flag=SMOKEMSG;
		
	}
	else if(received_flag==TEMPMSG)
	{
		TempConfig=received;
		received_flag=0;
	}
	else if(received_flag==SMOKEMSG)
	{
		SmokeConfig=received;
		received_flag=0;
	}
	
}
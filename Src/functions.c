#include "functions.h"

uint8_t arr_Globe[steps][LED_in_one_side];

void testFunction(void)
{
	clearLED();
	for (int i = 5; i < 10; i++)									// Angle Possion (Column)
	{
		for (int j = 22; j < 29; j++)								// LED Possion (Row)
		{
			arr_Globe[i][j] = COLOR_PURPLE;
		}
	}
}

// Delay 1 unit equal to 0.00001s (0.1ms)
void delay(uint32_t time)
{
	timeDelay = time;
	while(timeDelay);
}

void clearLED(void)
{
	for (int i=0; i<LED_CNT; i++)
	{
		for (int j=0; j<LED_in_one_side; j++)
		{
			arr_Globe[i][j] = COLOR_BLACK;
		}
	}
}

void loadDataToLED(uint8_t pos)
{
	uint8_t opposite_pos = pos;
	uint8_t center_pos = steps/2;
	if (opposite_pos < center_pos)		opposite_pos += center_pos;
	else															opposite_pos -= center_pos;
	
	for (int i = 0; i < 50; i++) 	// Set data for first 50 LED
	{
		led_set_color(i, arr_Globe[pos][i]);
	}
	for (int i = 50; i<100; i++)  // Set data for next 50 LED
	{
		led_set_color(i, arr_Globe[opposite_pos][99-i]);
	}
}

/**
  * @brief  Check position of sensor
  * @param  Pos for input user's position, StandardError amount of reality and theory,  
  * @retval 1 (true) or 0 (false)
  */
uint8_t StartPos(uint8_t Pos)
{ 
	Pos = (Pos*steps)/360*timePerAngle;
	if (timePerRound <= Pos && Pos <= timePerRound + timePerAngle)
	{
		return 1;
	}
	return 0;
}

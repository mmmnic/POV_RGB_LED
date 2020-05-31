#include "ws2812b_control.h"
#include "characters.h"
#include <ctype.h> 
#include <stdio.h> 
#include <stdlib.h>
// Define
#define steps 120 // ~speed=2,5 round/s
#define LED_in_one_side 50
#define roundUpdate 5
// Global arguments
extern uint32_t timePerRound;
extern volatile uint32_t timePerAngle;
extern volatile uint32_t timeDelay;
extern volatile uint8_t isReset;
void testFunction(void);
void delay(uint32_t time);
void loadDataToLED(uint8_t pos);
void clearLED(void);
uint8_t StartPos(uint8_t Pos);

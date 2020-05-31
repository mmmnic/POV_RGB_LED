#include "characters.h"
#include "string.h"
#include <ctype.h> 
#include <stdio.h> 
#include <stdlib.h>

uint8_t **getChar(char data, uint8_t color)
{
	uint8_t **character = (uint8_t **)malloc(7 * sizeof(uint8_t *));
	for (uint8_t i=0; i<7; i++)
	{
		character[i] = (uint8_t *)malloc(5 * sizeof(uint8_t *));
	}
	uint8_t c = color;
	
	switch (data)
	{
		case '0': {
			uint8_t temp[7][5] = {
				{0,c,c,c,0},
				{c,0,0,0,c},
				{c,0,0,c,c},
				{c,0,c,0,c},
				{c,c,0,0,c},
				{c,0,0,0,c},
				{0,c,c,c,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case '1': {
			uint8_t temp[7][5] = {
				{0,0,c,0,0},
				{0,c,c,0,0},
				{0,0,c,0,0},
				{0,0,c,0,0},
				{0,0,c,0,0},
				{0,0,c,0,0},
				{0,c,c,c,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case '2': {
			uint8_t temp[7][5] = {
				{0,c,c,c,0},
				{c,0,0,0,c},
				{0,0,0,0,c},
				{0,c,c,c,0},
				{c,0,0,0,0},
				{c,0,0,0,0},
				{c,c,c,c,c},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case '3': {
			uint8_t temp[7][5] = {
				{0,c,c,c,0},
				{c,0,0,0,c},
				{0,0,0,0,c},
				{0,0,c,c,0},
				{0,0,0,0,c},
				{c,0,0,0,c},
				{0,c,c,c,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case '4': {
			uint8_t temp[7][5] = {
				{c,0,0,c,0},
				{c,0,0,c,0},
				{c,0,0,c,0},
				{c,c,c,c,c},
				{0,0,0,c,0},
				{0,0,0,c,0},
				{0,0,0,c,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case '5': {
			uint8_t temp[7][5] = {
				{c,c,c,c,c},
				{c,0,0,0,0},
				{c,0,0,0,0},
				{c,c,c,c,0},
				{0,0,0,0,c},
				{0,0,0,0,c},
				{c,c,c,c,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case '6': {
			uint8_t temp[7][5] = {
				{0,c,c,c,c},
				{c,0,0,0,0},
				{c,0,0,0,0},
				{c,c,c,c,0},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{0,c,c,c,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case '7': {
			uint8_t temp[7][5] = {
				{c,c,c,c,c},
				{0,0,0,0,c},
				{0,0,0,0,c},
				{0,0,c,c,0},
				{0,c,0,0,0},
				{0,c,0,0,0},
				{0,c,0,0,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case '8': {
			uint8_t temp[7][5] = {
				{0,c,c,c,0},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{0,c,c,c,0},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{0,c,c,c,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case '9': {
			uint8_t temp[7][5] = {
				{0,c,c,c,0},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{0,c,c,c,c},
				{0,0,0,0,c},
				{c,0,0,0,c},
				{0,c,c,c,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case 'A': {
			uint8_t temp[7][5] = {
				{0,c,c,c,0},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,c,c,c,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case 'B': {
			uint8_t temp[7][5] = {
				{c,c,c,c,0},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,c,c,c,0},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,c,c,c,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case 'C': {
			uint8_t temp[7][5] = {
				{0,c,c,c,c},
				{c,0,0,0,0},
				{c,0,0,0,0},
				{c,0,0,0,0},
				{c,0,0,0,0},
				{c,0,0,0,0},
				{0,c,c,c,c},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case 'D': {
			uint8_t temp[7][5] = {
				{c,c,c,c,0},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,c,c,c,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case 'E': {
			uint8_t temp[7][5] = {
				{c,c,c,c,c},
				{c,0,0,0,0},
				{c,0,0,0,0},
				{c,c,c,c,0},
				{c,0,0,0,0},
				{c,0,0,0,0},
				{c,c,c,c,c},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case 'F': {
			uint8_t temp[7][5] = {
				{c,c,c,c,c},
				{c,0,0,0,0},
				{c,0,0,0,0},
				{c,c,c,c,0},
				{c,0,0,0,0},
				{c,0,0,0,0},
				{c,0,0,0,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case 'G': {
			uint8_t temp[7][5] = {
				{0,c,c,c,c},
				{c,0,0,0,0},
				{c,0,0,0,0},
				{c,0,c,c,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{0,c,c,c,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case 'H': {
			uint8_t temp[7][5] = {
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,c,c,c,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case 'I': {
			uint8_t temp[7][5] = {
				{c,c,c,c,c},
				{0,0,c,0,0},
				{0,0,c,0,0},
				{0,0,c,0,0},
				{0,0,c,0,0},
				{0,0,c,0,0},
				{c,c,c,c,c},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case 'J': {
			uint8_t temp[7][5] = {
				{0,c,c,c,0},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,c,c,c,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case 'K': {
			uint8_t temp[7][5] = {
				{c,0,0,0,c},
				{c,0,0,c,0},
				{c,0,c,0,0},
				{c,c,0,0,0},
				{c,0,c,0,0},
				{c,0,0,c,0},
				{c,0,0,0,c},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case 'L': {
			uint8_t temp[7][5] = {
				{c,0,0,0,0},
				{c,0,0,0,0},
				{c,0,0,0,0},
				{c,0,0,0,0},
				{c,0,0,0,0},
				{c,0,0,0,0},
				{c,c,c,c,c},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case 'M': {
			uint8_t temp[7][5] = {
				{c,0,0,0,c},
				{c,c,0,c,c},
				{c,0,c,0,c},
				{c,0,c,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case 'N': {
			uint8_t temp[7][5] = {
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,c,0,0,c},
				{c,0,c,0,c},
				{c,0,0,c,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;

		case 'O': {
			uint8_t temp[7][5] = {
				{0,c,c,c,0},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{0,c,c,c,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case 'P': {
			uint8_t temp[7][5] = {
				{c,c,c,c,0},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,c,c,c,0},
				{c,0,0,0,0},
				{c,0,0,0,0},
				{c,0,0,0,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;

		case 'Q': {
			uint8_t temp[7][5] = {
				{0,c,c,c,0},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,c,0,c},
				{c,0,0,c,c},
				{0,c,c,c,c},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;

		case 'R': {
			uint8_t temp[7][5] = {
				{c,c,c,c,0},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,c,c,c,0},
				{c,0,c,0,0},
				{c,0,0,c,0},
				{c,0,0,0,c},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;

		case 'S': {
			uint8_t temp[7][5] = {
				{0,c,c,c,c},
				{c,0,0,0,0},
				{c,0,0,0,0},
				{0,c,c,c,0},
				{0,0,0,0,c},
				{0,0,0,0,c},
				{c,c,c,c,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;

		case 'T': {
			uint8_t temp[7][5] = {
				{c,c,c,c,c},
				{0,0,c,0,0},
				{0,0,c,0,0},
				{0,0,c,0,0},
				{0,0,c,0,0},
				{0,0,c,0,0},
				{0,0,c,0,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;

		case 'U': {
			uint8_t temp[7][5] = {
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{0,c,c,c,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;

		case 'V': {
			uint8_t temp[7][5] = {
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{0,c,0,c,0},
				{0,0,c,0,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;

		case 'W': {
			uint8_t temp[7][5] = {
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,0,0,c},
				{c,0,c,0,c},
				{c,0,c,0,c},
				{c,c,0,c,c},
				{c,0,0,0,c},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;

		case 'X': {
			uint8_t temp[7][5] = {
				{c,0,0,0,c},
				{c,0,0,0,c},
				{0,c,0,c,0},
				{0,0,c,0,0},
				{0,c,c,c,0},
				{c,0,0,0,c},
				{c,0,0,0,c},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;

		case 'Y': {
			uint8_t temp[7][5] = {
				{c,0,0,0,c},
				{c,0,0,0,c},
				{0,c,0,c,0},
				{0,0,c,0,0},
				{0,0,c,0,0},
				{0,0,c,0,0},
				{0,0,c,0,0},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;

		case 'Z': {
			uint8_t temp[7][5] = {
				{c,c,c,c,c},
				{0,0,0,0,c},
				{0,0,0,c,0},
				{0,0,c,0,0},
				{0,c,0,0,0},
				{c,0,0,0,0},
				{c,c,c,c,c},
			};
			for (int i = 0; i < 7; i++)
			{
				memcpy(character[i], temp[i], sizeof(temp[i]));
			}
		}
		break;
		
		case ' ': {				// space
			uint8_t temp[7][5];
			memset(temp, 0, sizeof(temp));
		}
		break;
	}
	return character;
}

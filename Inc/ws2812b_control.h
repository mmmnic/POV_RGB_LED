#include "main.h"
#include "string.h"

/* Define --------------------------------------------------------------------*/
#define		LED_CNT							100
#define		BYTE_PER_LED				3
#define		BIT_PER_LED					24
#define 	COLOR_BLACK					1
#define 	COLOR_RED						2
#define 	COLOR_GREEN					3
#define 	COLOR_BLUE					4
#define 	COLOR_YELLOW				5
#define 	COLOR_PURPLE				6
#define 	COLOR_CYAN					7							
#define 	COLOR_WHITE					8
typedef struct struct_LED_data
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
}LED_data;

static uint8_t 					leds_colors[BYTE_PER_LED * LED_CNT];
static uint32_t 				tmp_led_data[2 * BIT_PER_LED];
static uint8_t          is_reset_pulse;     /*!< Status if we are sending reset pulse or led data */
static uint32_t         current_led;        /*!< Current LED number we are sending */
static volatile uint8_t is_updating;        /*!< Is updating in progress? */

/* Function prototypes -----------------------------------------------*/
//uint8_t 		    led_set_color(size_t index, uint8_t r, uint8_t g, uint8_t b);
uint8_t 		    led_set_color(size_t index, uint8_t color);
uint8_t					led_set_color_all(LED_data LED);
uint8_t     		led_update(uint8_t block);
uint8_t     		led_is_update_finished(void);
uint8_t     		led_start_reset_pulse(uint8_t num);
uint8_t     		led_is_update_finished(void);
uint8_t     		led_start_reset_pulse(uint8_t num);
static void 		led_update_sequence(uint8_t tc);
static uint8_t 	led_fill_led_pwm_data(size_t ledx, uint32_t* ptr);

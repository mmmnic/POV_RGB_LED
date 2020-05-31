#ifndef __WS2812_CONTROL_H
#define __WS2812_CONTROL_H

/* Includes ------------------------------------------------------------------*/
#include "ws2812b_control.h"

/* ----------------------------- LED Strip 1 ----------------------------- */
/**
 * \brief           Start LEDs update procedure
 * \param[in]       block: Set to `1` to block for update process until finished
 * \return          `1` if update started, `0` otherwise
 */
uint8_t led_update(uint8_t block) {
    if (is_updating) {                          /* Check if update in progress already */
        return 0;
    }
    is_updating = 1;                            /* We are now updating */

    led_start_reset_pulse(1);                   /* Start reset pulse */
    if (block) {
        while (!led_is_update_finished());      /* Wait to finish */
    }
    return 1;
}

/**
 * \brief           Check if update procedure is finished
 * \return          `1` if not updating, `0` if updating process is in progress
 */
uint8_t led_is_update_finished(void) {
    return !is_updating;                        /* Return updating flag status */
}

/**
 * \brief           Start reset pulse sequence
 * \param[in]       num: Number indicating pulse is for beginning (1) or end (2) of PWM data channel
 */
static uint8_t led_start_reset_pulse(uint8_t num) {
    is_reset_pulse = num;                       /* Set reset pulse flag */
    
    memset(tmp_led_data, 0, sizeof(tmp_led_data));   /* Set all bytes to 0 to achieve 50us pulse */
    
    if (num == 1) {
        tmp_led_data[0] = TIM4->ARR / 3;
    }
    
    /* Set DMA to normal mode, set memory to beginning of data and length to 40 elements */
    /* 800kHz PWM x 40 samples = ~50us pulse low */
    LL_DMA_SetMode(DMA1, LL_DMA_STREAM_0, LL_DMA_MODE_NORMAL);  /* Go to non-circular mode */
    LL_DMA_SetMemoryAddress(DMA1, LL_DMA_STREAM_0, (uint32_t)tmp_led_data);
    LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_0, 40);

    /* Reset DMA configuration and enable channel */
    LL_DMA_ClearFlag_TC0(DMA1);
    LL_DMA_ClearFlag_HT0(DMA1);
    LL_DMA_DisableIT_HT(DMA1, LL_DMA_STREAM_0);
    LL_DMA_EnableIT_TC(DMA1, LL_DMA_STREAM_0);
    LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_0);
    
    LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1);  /* Enable channel for timer */
    LL_TIM_EnableCounter(TIM4);                 /* Start timer counter */
    
    return 1;
}

/**
 * \brief           Prepares data from memory for PWM output for timer
 * \note            Memory is in format R,G,B, while PWM must be configured in G,R,B[,W]
 * \param[in]       ledx: LED index to set the color
 * \param[out]      ptr: Output array with at least LED_CFG_RAW_BYTES_PER_LED-words of memory
 */
static uint8_t led_fill_led_pwm_data(size_t ledx, uint32_t* ptr) {
    size_t i;
    
    if (ledx < LED_CNT) {
        for (i = 0; i < 8; i++) {
						// Config autoReload to each bit data, if bit is 1 auto-reload is 2/3 else 0 is 1/3
            ptr[i] =        (leds_colors[BYTE_PER_LED * ledx + 1] & (1 << (7 - i))) ? (2 * TIM4->ARR / 3) : (TIM4->ARR / 3);
            ptr[8 + i] =    (leds_colors[BYTE_PER_LED * ledx + 0] & (1 << (7 - i))) ? (2 * TIM4->ARR / 3) : (TIM4->ARR / 3);
            ptr[16 + i] =   (leds_colors[BYTE_PER_LED * ledx + 2] & (1 << (7 - i))) ? (2 * TIM4->ARR / 3) : (TIM4->ARR / 3);
        }
        return 1;
    }
    return 0;
}

/**
 * \brief           Update sequence function, called on each DMA transfer complete or half-transfer complete events
 * \param[in]       tc: Transfer complete flag. Set to `1` on TC event, or `0` on HT event
 *
 * \note            TC = Transfer-Complete event, called at the end of block
 * \note            HT = Half-Transfer-Complete event, called in the middle of elements transfered by DMA
 *                  If block is 48 elements (our case),
 *                      HT is called when first BIT_PER_LED elements are transfered,
 *                      TC is called when second BIT_PER_LED elements are transfered.
 *									// 0 is HT, 1 is TC
 * \note            This function must be called from DMA interrupt
 */
static void led_update_sequence(uint8_t tc) {    
    tc = !!tc;                                  /* Convert to 1 or 0 value only */
    
    /* Check for reset pulse at the end of PWM channel */
    if (is_reset_pulse == 2) {                  /* Check for reset pulse at the end */
        LL_TIM_CC_DisableChannel(TIM4, LL_TIM_CHANNEL_CH1); /* Disable channel */
        LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_0);    /* Disable DMA channel */
        
        is_updating = 0;                        /* We are not updating anymore */
        return;
    }
    
    /* Check for reset pulse on beginning of PWM channel */
    if (is_reset_pulse == 1) {                  /* Check if we finished with reset pulse */
        /*
         * When reset pulse is active, we have to wait full DMA response,
         * before we can start modifying array which is shared with DMA and PWM
         */
        if (!tc) {                              /* We must wait for transfer complete */
            return;                             /* Return and wait to finish */
        }
        
        /* Disable timer output and disable DMA channel */
        LL_TIM_CC_DisableChannel(TIM4, LL_TIM_CHANNEL_CH1); /* Disable channel */
        LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_0);
        
        is_reset_pulse = 0;                     /* Not in reset pulse anymore */
        current_led = 0;                        /* Reset current led */
    } else {
        /*
         * When we are not in reset mode,
         * go to next led and process data for it
         */
        current_led++;                          /* Go to next LED */
    }
    
    /*
     * This part is used to prepare data for "next" led,
     * for which update will start once current transfer stops in circular mode
     */
    if (current_led < LED_CNT) {
        /*
         * If we are preparing data for first time (current_led == 0)
         * or if there was no TC event (it was HT):
         *
         *  - Prepare first part of array, because either there is no transfer
         *      or second part (from HT to TC) is now in process for PWM transfer
         *
         * In other case (TC = 1)
         */
        if (current_led == 0 || !tc) {
            led_fill_led_pwm_data(current_led, &tmp_led_data[0]);
        } else {
            led_fill_led_pwm_data(current_led, &tmp_led_data[BIT_PER_LED]);
        }
        
        /*
         * If we are preparing first led (current_led = 0), then:
         * 
         *  - We setup first part of array for first led,
         *  - We have to prepare second part for second led to have one led prepared in advance
         *  - Set DMA to circular mode and start the transfer + PWM output
         */
        if (current_led == 0) {
            current_led++;                      /* Go to next LED */
            led_fill_led_pwm_data(current_led, &tmp_led_data[BIT_PER_LED]);   /* Prepare second LED too */
            
            /* Set DMA to circular mode and set length to 48 elements for 2 leds */
            LL_DMA_SetMode(DMA1, LL_DMA_STREAM_0, LL_DMA_MODE_CIRCULAR);  /* Go to non-circular mode */
            LL_DMA_SetMemoryAddress(DMA1, LL_DMA_STREAM_0, (uint32_t)tmp_led_data);
            LL_DMA_SetDataLength(DMA1, LL_DMA_STREAM_0, 2 * BIT_PER_LED);
            
            /* Clear DMA flags */
            LL_DMA_ClearFlag_TC0(DMA1);
            LL_DMA_ClearFlag_HT0(DMA1);
            LL_DMA_EnableIT_HT(DMA1, LL_DMA_STREAM_0);
            LL_DMA_EnableStream(DMA1, LL_DMA_STREAM_0);
					
            LL_TIM_CC_EnableChannel(TIM4, LL_TIM_CHANNEL_CH1);  /* Enable channel */
        }
        
    /*
     * When we reached all leds, we have to wait to transmit data for all leds before we can disable DMA and PWM:
     *
     *  - If TC event is enabled and we have EVEN number of LEDS (2, 4, 6, ...)
     *  - If HT event is enabled and we have ODD number of LEDS (1, 3, 5, ...)
     */
    } else if ((!tc && (LED_CNT & 0x01)) || (tc && !(LED_CNT & 0x01))) {
        LL_TIM_CC_DisableChannel(TIM4, LL_TIM_CHANNEL_CH1); /* Disable channel */
        LL_DMA_DisableStream(DMA1, LL_DMA_STREAM_0);
        
        /* It is time to send final reset pulse, 50us at least */
        led_start_reset_pulse(2);                /* Start reset pulse at the end */
    }
}

/**
  * @brief This function handles DMA1 stream0 global interrupt.
  */
void DMA1_Stream0_IRQHandler(void)
{
	if (LL_DMA_IsActiveFlag_HT0(DMA1)) {        /* Check for HT event */
        LL_DMA_ClearFlag_HT0(DMA1);
        led_update_sequence(0);                 /* Call update sequence as HT event */
    } else if (LL_DMA_IsActiveFlag_TC0(DMA1)) { /* Check for TC event */
        LL_DMA_ClearFlag_TC0(DMA1);
        led_update_sequence(1);                 /* Call update sequence as TC event */
    } 
}

uint8_t led_set_color_all(LED_data LED_data) {
		size_t index;
		for (index = 0; index < LED_CNT; index++) {
        leds_colors[index * BYTE_PER_LED + 0] = LED_data.red;
        leds_colors[index * BYTE_PER_LED + 1] = LED_data.green;
        leds_colors[index * BYTE_PER_LED + 2] = LED_data.blue;
    }
    return 1;
}

/**
 * \brief           Set R,G,B color for specific LED
 * \param[in]       index: LED index in array, starting from `0`
 * \param[in]       r,g,b: Red, Green, Blue values
 * \return          `1` on success, `0` otherwise
 */

uint8_t led_set_color(size_t index, uint8_t color)
{
	if (index < LED_CNT) {
		switch (color)
		{
			case COLOR_BLACK:
				leds_colors[index * BYTE_PER_LED + 0] = 0; 		// red
				leds_colors[index * BYTE_PER_LED + 1] = 0;		// green
				leds_colors[index * BYTE_PER_LED + 2] = 0;		// blue
			return COLOR_BLACK;
			
			case COLOR_RED:
				leds_colors[index * BYTE_PER_LED + 0] = 254; 		// red
				leds_colors[index * BYTE_PER_LED + 1] = 0;			// green
				leds_colors[index * BYTE_PER_LED + 2] = 0;			// blue
			return COLOR_RED;
			
			case COLOR_GREEN:
				leds_colors[index * BYTE_PER_LED + 0] = 0; 			// red
				leds_colors[index * BYTE_PER_LED + 1] = 254;		// green
				leds_colors[index * BYTE_PER_LED + 2] = 0;			// blue
			return COLOR_GREEN;
			
			case COLOR_BLUE:
				leds_colors[index * BYTE_PER_LED + 0] = 0; 			// red
				leds_colors[index * BYTE_PER_LED + 1] = 0;			// green
				leds_colors[index * BYTE_PER_LED + 2] = 254;		// blue
			return COLOR_BLUE;
			
			case COLOR_YELLOW:
				leds_colors[index * BYTE_PER_LED + 0] = 254; 		// red
				leds_colors[index * BYTE_PER_LED + 1] = 254;		// green
				leds_colors[index * BYTE_PER_LED + 2] = 0;			// blue
			return COLOR_YELLOW;
			
			case COLOR_PURPLE:
				leds_colors[index * BYTE_PER_LED + 0] = 254; 		// red
				leds_colors[index * BYTE_PER_LED + 1] = 0;			// green
				leds_colors[index * BYTE_PER_LED + 2] = 254;		// blue
			return COLOR_PURPLE;
			
			case COLOR_CYAN:
				leds_colors[index * BYTE_PER_LED + 0] = 0; 			// red
				leds_colors[index * BYTE_PER_LED + 1] = 254;		// green
				leds_colors[index * BYTE_PER_LED + 2] = 254;		// blue
			return COLOR_CYAN;
			
			case COLOR_WHITE:
				leds_colors[index * BYTE_PER_LED + 0] = 254; 		// red
				leds_colors[index * BYTE_PER_LED + 1] = 254;		// green
				leds_colors[index * BYTE_PER_LED + 2] = 254;		// blue
			return COLOR_WHITE;
		}
	}
	return 0;
}
/*
uint8_t led_set_color(size_t index, uint8_t r, uint8_t g, uint8_t b)
{
    if (index < LED_CNT) {
        leds_colors[index * BYTE_PER_LED + 0] = r;
        leds_colors[index * BYTE_PER_LED + 1] = g;
        leds_colors[index * BYTE_PER_LED + 2] = b;
        return 1;
    }
    return 0;
}
*/
#endif

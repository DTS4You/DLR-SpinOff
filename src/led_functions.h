#include <DDBooster.h>
#include "global_init.h"

extern class DDBooster led_stripe[];

// Funktion_1
void stripe_fill(uint8_t c_index) {
	led_stripe[0].setRGB(color_[c_index][0], color_[c_index][1], color_[c_index][2]);

	// Schleife von Start bis Ende
	for(uint8_t i=0 ; i < max_led_count ; i++)
	{
		led_stripe[0].setLED(i);
	}
}


void led_set_range(uint8_t stripe_sel, uint8_t start, uint8_t end, uint8_t c_index)
{
	led_stripe[stripe_sel].setRGB(color_[c_index][0], color_[c_index][1], color_[c_index][2]);
    delay(ddb_init_delay);
	led_stripe[stripe_sel].setRange(start,end);
}

void led_set_position(uint8_t pos , uint8_t c_index)
{
	led_stripe[0].setRGB(color_[c_index][0], color_[c_index][1], color_[c_index][2]);
	led_stripe[0].setLED(pos);
}

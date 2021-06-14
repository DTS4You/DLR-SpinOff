// Farbtabelle -> Index -> R / G / B
const uint8_t color_[11][3] = {
		{   0 ,   0 ,   0 },		//  0. Farbe	Schwarz -> Aus
		{ 220 ,   0 ,   0 },		//  1. Farbe	Rot		90 %
		{   0 , 220 ,   0 },		//  2. Farbe	Grün	90 %
		{   0 ,   0 , 220 },		//  3. Farbe	Blau	90 %
		{   0 ,   0 , 120 },		//  4. Farbe	Blau 	50 %
		{   0 ,   0 ,  10 },		//  5. Farbe	Blau	5 %
		{   0 ,   0 ,  10 },		//  6. Farbe	Blau  -> Blinken aus
		{ 160 ,  10 ,  60 },		//  7. Farbe	Magenta
		{   0 , 220 ,   0 },		//  8. Farbe	Grün 100%
		{ 220 ,   0 ,   0 },		//  9. Farbe	Rot  100%
		{ 220 , 220 , 220 }			// 10. Farbe	Weiß 70%
};


// --- Farbzuweisungen
#define F_LED_on				10
#define F_LED_def				4
#define F_LED_off				0
#define F_LED_blink_1			4
#define F_LED_blink_2			5
#define F_LED_rot				1
#define F_LED_gruen 			2
#define F_LED_blau				3
#define F_LED_magenta			7

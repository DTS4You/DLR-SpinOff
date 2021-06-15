// ################################################################################
// ### Arduino                                                                  ###
// ################################################################################
// ###                                                                          ###
// ### Projekt			: DLR, SpinOff											###
// ### Version			: 1.01													###
// ### Datum			: 14.06.2021											###
// ###                                                                          ###
<<<<<<< HEAD
// ### Änderung			: überarbeitet VSCode, GitHub							###
=======
// ### Änderung			: überarbeitet, VSCode, GitHub							###
>>>>>>> 47564af2f9af4333b519011bf8202c56b0758f8d
// ###																			###
// ### Hardware			: Arduino Nano											###
// ###					: Leiterplatte 17-0023-02 und 17-0027-02				###
// ###					: max. 8 x Digi-Dot Booster								###
// ################################################################################

#include <arduino.h> 
// #include "ascii_codes.h"
#include "global_init.h"



#include "DDBooster.h"
#include "RBD_Timer.h"  			// https://github.com/alextaujenis/RBD_Timer
#include "SerialCommand.h"
#include "tables_patterns.h"
#include "led_functions.h"


const uint8_t ddb_cs_pin[8] 	= { 2, 3, 4, 5, 6, 7, 8, 9};
const uint8_t ddb_num_led[8]	= { 21, 21, 21, 21, 21, 21, 21, 21};
uint8_t	ddb_refresh = false;

// Digi-Dot-Booster Objekte erzeugen
DDBooster led_stripe[8];			// Objekt anlegen

// RBD::Timer refresh_task;
RBD::Timer refresh_task;

// SerialCommand create object
SerialCommand sCmd;					// The demo SerialCommand object


// ----------------------------------------------------------------------------
// --- Funktionsblöcke von SerialCommand
//-----------------------------------------------------------------------------
void LED_on() {
	Serial.println("LED EIN");
	led_set_range(0, 0, 10, 3);
	ddb_refresh = true;
}

void LED_off() {
	Serial.println("LED AUS");
	led_set_range(0, 0, 10, 5);
	ddb_refresh = true;
}

void sayHello() {
	char *arg;
	arg = sCmd.next();    // Get the next argument from the SerialCommand object buffer
	if (arg != NULL) {    // As long as it existed, take it
		Serial.print("echo ");
    	Serial.println(arg);
  	}
	else {
		Serial.println("ack");
  	}
}

// Command -> processCommand
void processCommand() {
	int aNumber;
	char *arg;
	
	Serial.println("ProcessCommand");
	arg = sCmd.next();
	if (arg != NULL) {
		aNumber = atoi(arg);    // Converts a char string to an integer
		Serial.print("1. arg: ");
		Serial.println(aNumber);
  	}
	else {
		Serial.println("No arguments");
	}

	arg = sCmd.next();
  	if (arg != NULL) {
		aNumber = atol(arg);
    	Serial.print("2. arg: ");
		Serial.println(aNumber);
  	}
  	else {
		Serial.println("No second argument");
  	}
}

// Command -> setCommand
void setCommand() {
	int aNumber;
	uint8_t rgb[3];
	char *arg;
	
	Serial.println("SetCommand");
	arg = sCmd.next();
	if (arg != NULL) {
		aNumber = atoi(arg);    // Converts a char string to an integer
		Serial.print("1. arg: ");
		Serial.println(aNumber);
		rgb[0] = aNumber;
  	}
	else {
		Serial.println("No arguments");
	}

	arg = sCmd.next();
  	if (arg != NULL) {
		aNumber = atol(arg);
    	Serial.print("2. arg: ");
		Serial.println(aNumber);
		rgb[1] = aNumber;
  	}
  	else {
		Serial.println("No 2. argument");
  	}

	arg = sCmd.next();
  	if (arg != NULL) {
		aNumber = atol(arg);
    	Serial.print("3. arg: ");
		Serial.println(aNumber);
		rgb[2] = aNumber;
  	}
  	else {
		Serial.println("No 3. argument");
  	}

	led_stripe[0].setRGB(rgb[0], rgb[1], rgb[2]);
	led_stripe[0].setLED(0);
	ddb_refresh = true;
	
}

void cmd_led_range() {
	int aNumber;
	uint8_t ddb;
	uint8_t	start;
	uint8_t stop;
	uint8_t state;
	uint8_t color;
	char *arg;
	
	Serial.println("Led_Range");
	arg = sCmd.next();
	if (arg != NULL) {
		aNumber = atoi(arg);    // Converts a char string to an integer
		Serial.print("1. arg: ");
		Serial.println(aNumber);
		ddb = aNumber;
  	}
	else {
		Serial.println("No arguments");
	}

	arg = sCmd.next();
  	if (arg != NULL) {
		aNumber = atol(arg);
    	Serial.print("2. arg: ");
		Serial.println(aNumber);
		start = aNumber;
  	}
  	else {
		Serial.println("No 2. argument");
  	}

	arg = sCmd.next();
  	if (arg != NULL) {
		aNumber = atol(arg);
    	Serial.print("3. arg: ");
		Serial.println(aNumber);
		stop = aNumber;
  	}
  	else {
		Serial.println("No 3. argument");
  	}
	
	arg = sCmd.next();
  	if (arg != NULL) {
		aNumber = atol(arg);
    	Serial.print("4. arg: ");
		Serial.println(aNumber);
		state = aNumber;
  	}
  	else {
		Serial.println("No 3. argument");
  	}

	if (state == 1)
	{
		color = F_LED_on;
	}
	else
	{
		color = F_LED_off;
	}
	
	led_set_range(ddb, start, stop, color);
	ddb_refresh = true;
}

void cmd_led_all_def()
{
	led_set_range( 0, 0, 20, F_LED_def);
	led_set_range( 1, 0, 20, F_LED_def);
	led_set_range( 2, 0, 20, F_LED_def);
	led_set_range( 3, 0, 20, F_LED_def);
	ddb_refresh = true;
}

void cmd_led_all_off()
{
	led_set_range( 0, 0, 20, F_LED_off);
	led_set_range( 1, 0, 20, F_LED_off);
	led_set_range( 2, 0, 20, F_LED_off);
	led_set_range( 3, 0, 20, F_LED_off);
	ddb_refresh = true;
}

// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
	Serial.println("NoCommand");
}
//-----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// Setup
// ----------------------------------------------------------------------------
void setup() {
	
	Serial.begin(115200);

	// Setup callbacks for SerialCommand commands
	sCmd.addCommand("on",		LED_on);          	// Turns LED on
	sCmd.addCommand("off",		LED_off);         	// Turns LED off
	sCmd.addCommand("echo",		sayHello);        	// Echos the string argument back
	sCmd.addCommand("P",		processCommand);  	// Converts two arguments to integers and echos them back
	sCmd.addCommand("Set",		setCommand);		// Set Value
	sCmd.addCommand("Led",		cmd_led_range);		// Set Range on selected ddb
	sCmd.addCommand("all_def",	cmd_led_all_def);	// All Leds default
	sCmd.addCommand("all_off", 	cmd_led_all_off);	// All Leds off
	sCmd.setDefaultHandler(unrecognized);      	// Handler for command that isn't matched
	// Send Acknowledge -> "ack" to the serial port
	Serial.println("ack");
	
	for (uint8_t i = 0; i < 7; i++)
	{
		// Digi-Dot-Booster CS-Pin konfigurieren
		led_stripe[i].configurePins(ddb_cs_pin[i]);
		delay(ddb_init_delay);

		// Digi-Dot-Booster -> Anzahl der LEDs pro Digi-Dot-Booster
		led_stripe[i].init(ddb_num_led[i]);
		delay(ddb_init_delay);
		led_stripe[i].clearAll();
		delay(ddb_init_delay);
		led_stripe[i].show();
		delay(ddb_init_delay);
	}
	

	// Timer definieren und starten
	refresh_task.setTimeout(Refresh_Time);
	refresh_task.restart();
	
	//-------------------------------------------------------------------------
	// Grundeinstellungen LED Stripes
	//-------------------------------------------------------------------------
	led_set_range( 0, 0, 20, F_LED_def);
	led_stripe[0].show();
	led_set_range( 1, 0, 20, F_LED_def);
	led_stripe[1].show();
	led_set_range( 2, 0, 20, F_LED_def);
	led_stripe[2].show();
	led_set_range( 3, 0, 20, F_LED_def);
	led_stripe[3].show();
	led_set_range( 4, 0, 20, F_LED_magenta);
	led_stripe[4].show();

	//-------------------------------------------------------------------------
}

// ----------------------------------------------------------------------------
// Main Loop
// ----------------------------------------------------------------------------
void loop() {

	// Serial Command Read
	sCmd.readSerial();
	
	// Refresh Task -> Alle Digi-Dot Booster ddb.show() aufrufen
	if(ddb_refresh)
	{
		ddb_refresh = false;
		for (uint8_t i = 0; i < 7; i++)
		{
			led_stripe[i].show();
		}
	}
}

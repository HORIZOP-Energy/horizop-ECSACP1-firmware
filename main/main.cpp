#include "LED.h"
#include "contactor.h"
#include "C:\Users\Elyes\esp-idf-v4.4.5\components\arduino\cores\esp32\Arduino.h"
#include "adc.h"
#include "sensor_current.h"
int num = 0;


void setup() {
	Serial.begin(115200);
    //LED.setup(); // Call the setup() function of LEDClass to initialize the LED pin.
	// setup Contactor
	//Contactor.setup();

	// Setup ADC for pins A0-A7
	//AdcManager.setup();
}

void loop() {
    //LED.blink(3, 500); // Call the blink() function of LEDClass to blink the LED.#
	/*num = random(2);
	if (num==1)
		Contactor.switchOn();
	else
		Contactor.switchOff();
	if (Contactor.isOn())
		Serial.println("Contactor Is On");
	else
		Serial.println("Contactor Is Off");
	*/

	//bool dataChanged = AdcManager.updatePilotVoltageAndProximityPilotAmps();
	//delay(1000);
	Serial.println(SensorCurrent.phase1Milliamps());
	Serial.println(SensorCurrent.phase2Milliamps());
	Serial.println(SensorCurrent.phase3Milliamps());
}

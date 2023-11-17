#include "LED.h"
#include "C:\Users\Elyes\esp-idf-v4.4.5\components\arduino\cores\esp32\Arduino.h"

LEDClass::LEDClass() {}

void LEDClass::setup()
{
    // initialize LED digital pin as an output.
    pinMode(LED_GPIO_NUM, OUTPUT);
}

void LEDClass::blink(int times, int delayMS)
{
    while (times-- > 0)
    {
        digitalWrite(LED_GPIO_NUM, HIGH);
        delay(delayMS);
        digitalWrite(LED_GPIO_NUM, LOW);
        delay(delayMS);
    }
}

LEDClass LED;

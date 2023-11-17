#include "C:\Users\Elyes\esp-idf-v4.4.5\components\arduino\cores\esp32\Arduino.h"
#include "sensor_current.h"
#include "adc.h"

SensorCurrentClass SensorCurrent;

SensorCurrentClass::SensorCurrentClass()
{
}

unsigned long SensorCurrentClass::phase1Milliamps()
{
    AdcManager.changeInputPin(26);
    ADCMeasurement reading = AdcManager.read(numberOgSamples, 8, 3);
    return reading.highest;
}

unsigned long SensorCurrentClass::phase2Milliamps()
{
    AdcManager.changeInputPin(27);
    ADCMeasurement reading = AdcManager.read(numberOgSamples, 8, 3);
    return reading.highest;
}

unsigned long SensorCurrentClass::phase3Milliamps()
{
    AdcManager.changeInputPin(14);
    ADCMeasurement reading = AdcManager.read(numberOgSamples, 8, 3);
    return reading.highest;
}

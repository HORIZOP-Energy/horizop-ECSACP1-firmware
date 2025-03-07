#include "C:\Users\Elyes\esp-idf-v4.4.5\components\arduino\cores\esp32\Arduino.h"
#include "adc.h"
#include "logger.h"

AdcManagerClass AdcManager;

AdcManagerClass::AdcManagerClass()
{
}

void AdcManagerClass::setup()
{
//    /*
//     * A) Pins setup
//     */
//#ifdef mkrwifi1010
//    int pins[] = {PIN_A0, PIN_A1, PIN_A2, PIN_A3, PIN_A4, PIN_A5, PIN_A6};
//    int pins_size = 7;
//#endif
//#ifdef nano_33_iot
//    int pins[] = {PIN_A0, PIN_A1, PIN_A2, PIN_A3, PIN_A4, PIN_A5, PIN_A6, PIN_A7};
//    int pins_size = 8;
//#endif
//
//    for (int i = 0; i < pins_size; i++)
//    {
//        PinDescription pdesc = g_APinDescription[pins[i]];
//
//        // make PIN INPUT
//        PORT->Group[pdesc.ulPort].DIRCLR.reg = (uint32_t)(1 << pdesc.ulPin);
//
//        // Connect the ADC (Peripheral B)
//        uint32_t temp;
//        if (pdesc.ulPin & 1)
//        {
//
//            // Get whole current setup for both odd and even pins and remove odd one
//            temp = (PORT->Group[pdesc.ulPort].PMUX[pdesc.ulPin >> 1].reg) & PORT_PMUX_PMUXE(0xF);
//            // Set new muxing
//            PORT->Group[pdesc.ulPort].PMUX[pdesc.ulPin >> 1].reg = temp | PORT_PMUX_PMUXO(PIO_ANALOG);
//        }
//        else
//        {
//
//            temp = (PORT->Group[pdesc.ulPort].PMUX[pdesc.ulPin >> 1].reg) & PORT_PMUX_PMUXO(0xF);
//            PORT->Group[pdesc.ulPort].PMUX[pdesc.ulPin >> 1].reg = temp | PORT_PMUX_PMUXE(PIO_ANALOG);
//        }
//
//        // Enable port mux
//        PORT->Group[pdesc.ulPort].PINCFG[pdesc.ulPin].reg |= PORT_PINCFG_PMUXEN;
//    }
//
//    /*
//     * B) ADC setup
//     * MAX sample time is 0,025ms which allowes for 800 samples per 20ms - good enough for sampling a 50Hz-sine wave
//     *
//     * All those options will give the same timing:
//     * (some avergaing is good to even out some noise)
//     *
//     * 0,1ms sample time:
//     * PRESCALE | Nsamples
//     *    DIV8  | 16 *
//     *   DIV16  | 8
//     *   DIV32  | 4
//     *   DIV64  | 2
//     *  DIV128  | 1
//     *
//     * 0,05ms sample time:
//     * PRESCALE | Nsamples
//     *    DIV4  | 16
//     *    DIV8  | 8
//     *   DIV16  | 4
//     *   DIV32  | 2
//     *   DIV64  | 1
//     *
//     * 0,025ms sample time:
//     * PRESCALE | Nsamples
//     *    DIV4  | 8
//     *    DIV8  | 4
//     *   DIV16  | 2
//     *   DIV32  | 1 (most stable output)
//     *
//     */
//
//    // disable ADC
//    ADC->CTRLA.bit.ENABLE = 0;
//    while (ADC->STATUS.bit.SYNCBUSY == 1)
//        ;
//
//    ADC->CTRLB.reg = ADC_CTRLB_PRESCALER_DIV32 | ADC_CTRLB_FREERUN;
//    while (ADC->STATUS.bit.SYNCBUSY == 1)
//        ;
//
//    // Averaging 8 samples
//    //ADC->CTRLB.bit.RESSEL = 1;
//    //while (ADC->STATUS.bit.SYNCBUSY == 1)
//    //    ;
//    //ADC->AVGCTRL.reg = ADC_AVGCTRL_SAMPLENUM_8 | ADC_AVGCTRL_ADJRES(3);
//    //while (ADC->STATUS.bit.SYNCBUSY == 1)
//    //    ;
//
//    // REFCTRL
//    ADC->REFCTRL.reg = ADC_REFCTRL_REFSEL_INTVCC1; // 1/2 VDDANA reference
//    while (ADC->STATUS.bit.SYNCBUSY == 1)
//        ;
//
//    ADC->INPUTCTRL.reg = ADC_INPUTCTRL_MUXNEG_GND | // negative to GND
//                         ADC_INPUTCTRL_GAIN_DIV2;
//    while (ADC->STATUS.bit.SYNCBUSY == 1)
//        ;


	// No additional setup is required for the ADC in Arduino for ESP32.
	// The ADC is automatically initialized and configured.
	Log.log("ADC setup complete");
}

void AdcManagerClass::changeInputPin(unsigned int analogPinName)
{
//    // Disable ADC
//    ADC->CTRLA.bit.ENABLE = 0;
//    while (ADC->STATUS.bit.SYNCBUSY == 1)
//        ;
//
//    // Selection for the positive ADC input
//    ADC->INPUTCTRL.bit.MUXPOS = g_APinDescription[analogPinName].ulADCChannelNumber;
//    while (ADC->STATUS.bit.SYNCBUSY == 1)
//        ;
//
//    // Enable ADC
//    ADC->CTRLA.bit.ENABLE = 1;
//    while (ADC->STATUS.bit.SYNCBUSY == 1)
//        ;
//
//    read(10, 1, 0); // changing input produced invalid data - consume it first


	// In Arduino for ESP32, you don't need to manually change the input pin.
	// The built-in ADC functions (analogRead) handle this for you.


}

// ***25us*** per sample
// for 50Hz -> 800 samples to catch 1 cycle
// for 1kHz -> 40 samples catches 1 cycle
//
// 1kHz:
//     30us /   3% duty cycle
//    100us /  10% duty cycle
//   1000us / 100% duty cycle
struct ADCMeasurement AdcManagerClass::read(unsigned int numberOgSamples, int avg, int shift)
{

    unsigned long sample;
    unsigned int remaining = numberOgSamples / avg;

    struct ADCMeasurement aDCMeasurement;
    aDCMeasurement.highest = 0;
    aDCMeasurement.lowest = 1 << 12; //==4096

    while (remaining-- > 0)
    {

        sample = 0;
        for (int i = 0; i < avg; i++)
        {
//            // no need to start - using free running
//            //ADC->SWTRIG.bit.START = 1;
//
//            // Waiting for the to complete
//            while (ADC->INTFLAG.bit.RESRDY == 0)
//                ;
//
        	//unsigned long newValue = ADC->RESULT.reg;

//            while (ADC->STATUS.bit.SYNCBUSY == 1)
//                ;
        	// Read the ADC value from the analog pin and accumulate the samples.
        	int adcValue = analogRead(pinProxymityPilot); // Replace with the appropriate pin

        	sample += adcValue;
        }

        sample = sample >> shift; // Calculate the average of samples.

        if (sample > aDCMeasurement.highest)
        {
            aDCMeasurement.highest = sample;
        }
        if (sample < aDCMeasurement.lowest)
        {
            aDCMeasurement.lowest = sample;
        }
    }

    return aDCMeasurement;
}

bool AdcManagerClass::updatePilotVoltageAndProximityPilotAmps()
{
    ADCMeasurement adcMeasurement;

    /*
     * Experience has shown that EVs pilot signal might be unstable and switch back and forth
     * within 100ms. Therefore, we buffer the signal for some time and only react upon changes
     * after signal has been stable for this time (500ms).
     */
    const unsigned long bufferTime = 500;

    // measure Pilot Control
    AdcManager.changeInputPin(pinControlPilot);
    adcMeasurement = read(320, 1, 0); // 8 cycles
    const unsigned long newControlPilotAdc = adcMeasurement.highest;
    // has it changed?
    PilotVoltage lastControlPilotVoltage = toControlPilot(lastControlPilotAdc);
    const PilotVoltage newControlPilotVoltage = toControlPilot(newControlPilotAdc);
    if (lastControlPilotVoltage != newControlPilotVoltage)
    {
        lastControlPilotChangedAt = millis();
        lastControlPilotAdc = newControlPilotAdc;
        lastControlPilotVoltage = newControlPilotVoltage;
    }

    // measure Proximity Pilot
    AdcManager.changeInputPin(pinProxymityPilot);
    adcMeasurement = read(320, 1, 0); // 8 cycles
    const unsigned long newProximityPilotAdc = adcMeasurement.highest;
    // has it changed?
    ProximityPilotAmps lastProximityPilotAmps = toProximityPilot(lastProximityPilotAdc);
    const ProximityPilotAmps newProximityPilotAmps = toProximityPilot(newProximityPilotAdc);
    if (lastProximityPilotAmps != newProximityPilotAmps)
    {
        lastProximityPilotChangedAt = millis();
        lastProximityPilotAdc = newProximityPilotAdc;
        lastProximityPilotAmps = newProximityPilotAmps;
    }

    /*
     * Evaluate change
     */
    bool changeDetected = false;

    const unsigned long durationPilotControl = millis() - lastControlPilotChangedAt;
    if (lastControlPilotVoltage != currentControlPilotVoltage && (currentControlPilotVoltage != Volt_6 || durationPilotControl > bufferTime))
    {
        char buf[100];
        snprintf(buf, 100, "Pilot voltage changed from %d to %d. ADC: %lu", currentControlPilotVoltage, lastControlPilotVoltage, lastControlPilotAdc);
        Log.log(buf);

        currentControlPilotVoltage = lastControlPilotVoltage;
        currentControlPilotAdc = lastControlPilotAdc;
        changeDetected = true;
    }

    const unsigned long durationProximityPilot = millis() - lastProximityPilotChangedAt;
    if (lastProximityPilotAmps != currentProximityPilotAmps && durationProximityPilot > bufferTime)
    {
        char buf[100];
        snprintf(buf, 100, "Proximity voltage changed from %d to %d. ADC: %lu", currentProximityPilotAmps, lastProximityPilotAmps, lastProximityPilotAdc);
        Log.log(buf);

        currentProximityPilotAmps = lastProximityPilotAmps;
        currentProximityPilotAdc = lastProximityPilotAdc;
        changeDetected = true;
    }

    return changeDetected;
}

unsigned long AdcManagerClass::adcValueToMilliVolts(unsigned long aDCMeasurement)
{
    // 0 => 0V | 4095 => 3.3V
    uint32_t microVolts = aDCMeasurement * 806;
    return (uint16_t)(microVolts / 1000);
}

ProximityPilotAmps AdcManagerClass::toProximityPilot(unsigned long aDCMeasurement)
{
	// The conversion from ADC value to millivolts depends on the ADC reference voltage and resolution.
	// The ESP32 ADC has a reference voltage of 3.3V and a resolution of 12 bits (0 to 4095).
	// To convert the ADC value to millivolts, we use the formula:
	// millivolts = (ADC Value * Reference Voltage) / (2^Resolution)


    /*
     * 4095 / 330V = 12,409090909090909
     * 
     * Measured:
     * 
     * open     -> 2484 mV (no cable)
     * 1500 Ohm -> 1890 mV (13A) (2187)
     *  680 Ohm -> 1466 mV (20A) (1678)
     *  220 Ohm ->  793 mV (32A) (1129)
     * 
     * https://en.wikipedia.org/wiki/SAE_J1772
     * 
     */
    unsigned long millivolts = adcValueToMilliVolts(aDCMeasurement);

    //Serial.print("PP: ");
    //Serial.print(millivolts);
    //Serial.print("mV / ADC: ");
    //Serial.print(aDCMeasurement.highest);
    //Serial.println();
    //delay(1000);

    if (millivolts < 1129)
    {
        return Amp32;
    }
    else if (millivolts < 1678)
    {
        return Amp20;
    }
    else if (millivolts < 2187)
    {
        return Amp13;
    }
    else
    {
        return NoCable;
    }
}

PilotVoltage AdcManagerClass::toControlPilot(unsigned long aDCMeasurement)
{
    /*
     * R9 = 47k
     * R10 = 200k
     * R11 = 82k
     * 
     * Board-A values:
     * Open      : 2500mV
     * Connected : 1767mV
     * Ready     : 1099mV
     * 
     * Open:      2324mV (step: 634)
     * Connected: 1690mV (step: 535)
     * Ready:     1155mV (step: 535)
     * Vent :     620mV
     * Fault :    
     * Car 2.6k -> millivolts=2546
     * 
     */

    unsigned long millivolts = adcValueToMilliVolts(aDCMeasurement);

    //Serial.print("CP: ");
    //Serial.print(millivolts);
    //Serial.print("mV / ADC: ");
    //Serial.print(aDCMeasurement.highest);
    //Serial.println();
    //delay(1000);

    if (millivolts < 100)
    {
        return Fault;
    }
    else if (millivolts < 662)
    {
        return Volt_3;
    }
    else if (millivolts < 1344)
    {
        return Volt_6;
    }
    else if (millivolts < 2026)
    {
        return Volt_9;
    }
    else
    {
        return Volt_12;
    }
}

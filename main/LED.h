#ifndef _LED_H
#define _LED_H
#define LED_GPIO_NUM 2

class LEDClass
{
    
public:
    LEDClass();

    void setup();
    void blink(int times, int delayMS);
};

extern LEDClass LED;

#endif

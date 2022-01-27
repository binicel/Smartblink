#include "gpio.h"
#include <lgpio.h>

Gpio::Gpio(QObject *parent) : QObject(parent)
{
    // initialization gpio
    m_handle = lgGpiochipOpen(0); /* get a handle to the GPIO */
    int init_lvl = 0;
    for(int pin : LEDS)
        lgGpioClaimOutput(m_handle, LFLAGS, pin, init_lvl); /* initial level = init_lvl */
}


Gpio::~Gpio()
{
    int init_lvl = 0;
    for(int pin : LEDS)
        lgGpioWrite(m_handle, pin, init_lvl); /* initial level = init_lvl */

    lgGpiochipClose(m_handle); // Bei uns optional gibt chip frei


}

void Gpio::set(int pin,bool value)
{
    lgGpioWrite(m_handle, pin, value); /* initial level = init_lvl */
}

void Gpio::set(unsigned int pattern)
{
    // 1011
    // 0001
    //------ AND
    // 0001
    int n = 0;
    bool value;
    unsigned int check = 0b0001;
    for(auto pin : LEDS)
    {
        // n stelle von pattern ausmaskieren
        value = check & pattern>>n; // bit shift to the right;
        lgGpioWrite(m_handle, pin, value);
        n++;
    }
}

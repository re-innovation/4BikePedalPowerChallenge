#pragma once

#include "Config.h"
#include "Player.h"

class LoadedPlayer : public Player {
public:
    LoadedPlayer(uint8_t vinPin, uint16_t r1KOhm, uint16_t r2KOhm, 
                 uint8_t ledPin, uint16_t ledCount, neoPixelType ledType,
                 uint8_t pwmPin);
    void begin();
    void update();
    uint8_t getPwm() { return (uint8_t)_pwmLoad; }

private:
    uint8_t _pwmPin;
    long _pwmLoad;
    float _integral;
    unsigned long _last;

};


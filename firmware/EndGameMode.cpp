#include <Arduino.h>
#include "EndGameMode.h"
#include "ClockDisplay.h"
#include "Settings.h"
#include "Players.h"
#include "CorrectedMillis.h"
#include "Util.h"

_EndGameMode EndGameMode;

_EndGameMode::_EndGameMode()
{
}

void _EndGameMode::start()
{
#ifdef DEBUG
    Serial.println(F("EndGameMode::start()"));
    Serial.print(F("Settings: MaximumPowerWatts="));
    Serial.print(MaximumPowerWatts.get());
    Serial.print(F(" GameDurationSeconds="));
    Serial.print(GameDurationSeconds.get());
    Serial.print(F(" NumberOfLedSegments="));
    Serial.println(NumberOfLedSegments.get());
    Serial.println(F("setup() E"));
#endif
    // Clean button presses from other modes
    _winner = getWinner();
    Players[_winner].fillup();
    ClockDisplay.display('P', _winner+1, '!');
    _start = millis();
    _wipe = playerDisplayRowCount();
}

void _EndGameMode::stop()
{
#ifdef DEBUG
    Serial.println(F("EndGameMode::stop()"));
#endif
    // ensure we leave the display turned on
    ClockDisplay.setEnable(true);
}

void _EndGameMode::modeUpdate()
{
    // flash clock output
    ClockDisplay.setEnable(((millis() - _start)/800)%2==0);

    // wipe the loser displays
    if (_wipe >= 0) {
        for (uint8_t p=0; p<PLAYER_COUNT; p++) {
            if (p != _winner) {
                if (_wipe == (int16_t)Players[p].getMaxIlluminatedRow()-1) {
                    // dim the max indicator for non-winners
                    Players[p].setRowColor(_wipe, colorBrightness(PLAYER_MAX_COLOR[p], 0.1));
                } else if (_wipe > (int16_t)Players[p].getMaxIlluminatedRow()-1) {
                    // for non-winners, turn off pixels above max (should't really be necessary, but
                    // just in case of glitches / testing cases...
                    Players[p].setRowColor(_wipe, 0x000000UL);
                } else {
                    // and draw a dimmed version of the bar below the winning line
                    Players[p].setRowColor(_wipe, colorBrightness(PLAYER_LED_COLOR[p], 0.1));
                }
                // send changed pixel data to LEDs
                Players[p].showLED();
            }
        } 
        _wipe--;
    }

    if (millis() > _last + END_GAME_UPDATE_MS) {
        // throb the winner
        float throb = (millis() - _start) % END_GAME_THROB_MS;
        if (throb > (END_GAME_THROB_MS/2)) {
            throb = (END_GAME_THROB_MS-throb)/(END_GAME_THROB_MS/2);
        } else {
            throb = throb/(END_GAME_THROB_MS/2);
        }
        for (uint16_t row=0; row<Players[_winner].getMaxIlluminatedRow(); row++) {
            Players[_winner].setRowColor(row, colorBrightness(PLAYER_LED_COLOR[_winner], throb));
        }
        Players[_winner].showLED();

        _last = millis();
    }
}

uint8_t _EndGameMode::getWinner()
{
    float max = 0;
    uint8_t winner = 0;
    for(uint8_t i=0; i<PLAYER_COUNT; i++) {
#ifdef DEBUG
        Serial.print(i+1);
        Serial.print(F("UP maxPower="));
        Serial.println(Players[i].getMaxPower());
#endif
        if (Players[i].getMaxPower() > max) {
            max = Players[i].getMaxPower();
            winner = i;
        }
    }
    return winner;
}


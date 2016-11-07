#include "LoadedPlayer.h"
#include "Config.h"

LoadedPlayer Players[PLAYER_COUNT] = {
    LoadedPlayer(PLAYER_VIN_PINS[0], PLAYER_VIN_R1, PLAYER_VIN_R2,
                 PLAYER_LED_PINS[0], PLAYER_LED_COUNT, PLAYER_LED_TYPE,
                 PLAYER_PWM_PINS[0]),
    LoadedPlayer(PLAYER_VIN_PINS[1], PLAYER_VIN_R1, PLAYER_VIN_R2,
                 PLAYER_LED_PINS[1], PLAYER_LED_COUNT, PLAYER_LED_TYPE,
                 PLAYER_PWM_PINS[1]),
    LoadedPlayer(PLAYER_VIN_PINS[2], PLAYER_VIN_R1, PLAYER_VIN_R2,
                 PLAYER_LED_PINS[2], PLAYER_LED_COUNT, PLAYER_LED_TYPE,
                 PLAYER_PWM_PINS[2]),
    LoadedPlayer(PLAYER_VIN_PINS[3], PLAYER_VIN_R1, PLAYER_VIN_R2,
                 PLAYER_LED_PINS[3], PLAYER_LED_COUNT, PLAYER_LED_TYPE,
                 PLAYER_PWM_PINS[3])
};


#ifndef IOT_ACTIONS_H
#define IOT_ACTIONS_H

#include <stdint.h>

// Common actions (0x00-0x0F)
#define IOT_ACTION_IDLE          0x00
#define IOT_ACTION_PING          0x01
#define IOT_ACTION_STATUS        0x02
#define IOT_ACTION_STOP          0x03

// Hexapod actions (0x10-0x3F)
#define IOT_ACTION_HEX_WALK      0x10
#define IOT_ACTION_HEX_TURN      0x11
#define IOT_ACTION_HEX_STAND     0x12
#define IOT_ACTION_HEX_LAYDOWN   0x13
#define IOT_ACTION_HEX_TIPTOES   0x14
#define IOT_ACTION_HEX_WAVE      0x15
#define IOT_ACTION_HEX_DANCE     0x16
#define IOT_ACTION_HEX_FIGHT     0x17
#define IOT_ACTION_HEX_BEEP      0x18
#define IOT_ACTION_HEX_TRIPOD    0x19
#define IOT_ACTION_HEX_RIPPLE    0x1A
#define IOT_ACTION_HEX_SCAMPER   0x1B

// Tank actions (0x40-0x5F)
#define IOT_ACTION_TANK_DRIVE    0x40
#define IOT_ACTION_TANK_TURRET   0x41
#define IOT_ACTION_TANK_FIRE     0x42

// Moto actions (0x60-0x7F)
#define IOT_ACTION_MOTO_THROTTLE 0x60
#define IOT_ACTION_MOTO_STEER    0x61

// Shogun actions (0x80-0x9F)
#define IOT_ACTION_SHOGUN_ASSEMBLE   0x80
#define IOT_ACTION_SHOGUN_DISASSEMBLE 0x81

#endif

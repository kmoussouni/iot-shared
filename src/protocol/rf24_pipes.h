#ifndef IOT_RF24_PIPES_H
#define IOT_RF24_PIPES_H

#include <stdint.h>
#include "device_ids.h"

// RF24 pipe address per device.
// Each device listens on its own address; the remote writes to it.
static const uint64_t IOT_RF24_PIPE_HEXAPOD = 0xB3B4B5B6F1LL;
static const uint64_t IOT_RF24_PIPE_TANK    = 0xB3B4B5B6CDLL;
static const uint64_t IOT_RF24_PIPE_MOTO    = 0xB3B4B5B6A3LL;
static const uint64_t IOT_RF24_PIPE_SHOGUN  = 0xB3B4B5B60FLL;

static inline uint64_t iot_rf24_pipe_for_device(uint8_t device_id)
{
    switch (device_id) {
        case IOT_DEVICE_HEXAPOD: return IOT_RF24_PIPE_HEXAPOD;
        case IOT_DEVICE_TANK:    return IOT_RF24_PIPE_TANK;
        case IOT_DEVICE_MOTO:    return IOT_RF24_PIPE_MOTO;
        case IOT_DEVICE_SHOGUN:  return IOT_RF24_PIPE_SHOGUN;
        default:                 return 0;
    }
}

#endif

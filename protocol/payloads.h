#ifndef IOT_PAYLOADS_H
#define IOT_PAYLOADS_H

#include <stdint.h>

// Joystick payload: 4 bytes
// Used by remote to send analog stick position
struct IotJoystickPayload {
    uint8_t x;         // 0-255 (128 = center)
    uint8_t y;         // 0-255 (128 = center)
    uint8_t buttons;   // bitmask of pressed buttons (up to 8 buttons)
    uint8_t speed;     // 0-255 speed/intensity modifier
};

#define IOT_JOYSTICK_CENTER 128
#define IOT_JOYSTICK_DEADZONE 10

static inline void iot_joystick_to_payload(const IotJoystickPayload* js, uint8_t* out) {
    out[0] = js->x;
    out[1] = js->y;
    out[2] = js->buttons;
    out[3] = js->speed;
}

static inline void iot_joystick_from_payload(const uint8_t* data, IotJoystickPayload* js) {
    js->x = data[0];
    js->y = data[1];
    js->buttons = data[2];
    js->speed = data[3];
}

// Status response payload: 4 bytes
// Sent by device back to remote
struct IotStatusPayload {
    uint8_t battery;     // 0-100 percent
    uint8_t state;       // device-specific state code
    uint8_t distance_cm; // ultrasonic distance (0-255, 255 = no obstacle)
    uint8_t flags;       // bitmask: bit0 = obstacle, bit1 = motion_detected, etc.
};

#define IOT_STATUS_FLAG_OBSTACLE  0x01
#define IOT_STATUS_FLAG_MOTION    0x02
#define IOT_STATUS_FLAG_LOW_BAT   0x04

static inline void iot_status_to_payload(const IotStatusPayload* st, uint8_t* out) {
    out[0] = st->battery;
    out[1] = st->state;
    out[2] = st->distance_cm;
    out[3] = st->flags;
}

static inline void iot_status_from_payload(const uint8_t* data, IotStatusPayload* st) {
    st->battery = data[0];
    st->state = data[1];
    st->distance_cm = data[2];
    st->flags = data[3];
}

#endif

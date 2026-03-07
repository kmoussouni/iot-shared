# CLAUDE.md

This file provides guidance to Claude Code when working with code in this repository.

## Project Overview

Shared libraries for the IoT robotics ecosystem. Provides the common communication protocol and reusable hardware driver abstractions used by all projects (`iot-hexapod`, `iot-remote`, `iot-shogun`). Designed to be consumed as a PlatformIO library dependency.

## Usage as PlatformIO Library

Other projects reference this library in their `platformio.ini`:

```ini
lib_deps =
    https://github.com/kmoussouni/iot-shared.git
```

Or for local development:

```ini
lib_extra_dirs = ../shared
```

## Structure

```
shared/
├── protocol/         # Communication protocol
│   ├── packet.h      # Packet struct, encode/decode
│   ├── device_ids.h  # Device ID constants
│   └── actions.h     # Common action enum
├── drivers/          # Reusable hardware abstractions
│   ├── comm_driver.h # Abstract communication interface
│   └── servo_utils.h # Servo mapping helpers
├── library.json      # PlatformIO library manifest
└── README.md
```

## Protocol

### Packet Format

```
[DEVICE_ID (1 byte) | ACTION (1 byte) | PAYLOAD (0-8 bytes) | CHECKSUM (1 byte)]
```

- **DEVICE_ID**: Target device (0x01=Hexapod, 0x02=Tank, 0x03=Moto, 0x04=Shogun)
- **ACTION**: Command enum value (device-specific)
- **PAYLOAD**: Action parameters (joystick position, settings, etc.)
- **CHECKSUM**: XOR of all preceding bytes

### Bidirectional Communication

- Remote -> Device: Command packets
- Device -> Remote: Status/sensor data packets (same format, different action codes)

## Drivers

### CommunicationDriver

Abstract interface over BT/WiFi/RF24 transport layers:
- `send(packet)` — encode and transmit
- `receive()` — listen and decode
- Concrete implementations per transport (BLE, WiFi, RF24)

### ServoUtils

Common servo helpers:
- Degree to PWM pulse conversion
- Servo range clamping
- Mirror calculation for left/right symmetry

## Key Technical Details

- Header-only where possible for embedded simplicity
- No dynamic allocation (Arduino constraint)
- All structs are packed for consistent byte layout
- Checksum validation on receive side
- Library must compile on both Arduino Mega (AVR) and ESP32

## Development Notes

- Changes here affect ALL downstream projects — be careful with breaking changes
- Maintain backward compatibility in packet format (add fields at end)
- Test on both AVR (Mega 2560) and ESP32 targets
- Keep dependencies minimal (Arduino.h only)

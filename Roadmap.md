# Shared Libraries Roadmap

## Overview

```mermaid
gantt
    title Shared Libraries Development Roadmap
    dateFormat YYYY-MM
    axisFormat %b %Y

    section Phase 0 - Protocol Design
    Packet format specification          :done, p0, 2025-03, 2025-04
    Device ID registry                   :done, p1, 2025-03, 2025-04
    Action enum design                   :p2, 2025-04, 2025-05

    section Phase 1 - Protocol Implementation
    Packet encode/decode                 :i1, 2025-05, 2025-06
    Checksum validation                  :i2, 2025-05, 2025-06
    PlatformIO library packaging         :i3, 2025-05, 2025-06
    Unit tests                           :i4, 2025-06, 2025-07

    section Phase 2 - Driver Abstractions
    CommunicationDriver interface        :d1, 2025-06, 2025-07
    RF24 driver implementation           :d2, 2025-07, 2025-08
    BLE driver implementation            :d3, 2025-07, 2025-08
    ServoUtils helpers                   :d4, 2025-06, 2025-07

    section Phase 3 - Integration
    Hexapod integration                  :h1, 2025-07, 2025-08
    Remote integration                   :h2, 2025-07, 2025-08
    Cross-platform validation            :h3, 2025-08, 2025-09

    section Phase 4 - Quality
    CI pipeline (AVR + ESP32 builds)     :q1, 2025-08, 2025-09
    API documentation                    :q2, 2025-09, 2025-10
```

## Phase 0 — Protocol Design

> Status: **Partially Done**

- [x] Define packet format: `[DEVICE_ID | ACTION | PAYLOAD | CHECKSUM]`
- [x] Assign device IDs (0x01-0x04)
- [ ] Define action enum values per device
  - Common actions: IDLE, PING, STATUS_REQUEST
  - Hexapod-specific: WALK, TURN, DANCE, FIGHT, etc.
  - Tank-specific: DRIVE, TURRET, FIRE
  - Moto-specific: THROTTLE, STEER
  - Shogun-specific: ASSEMBLE, DISASSEMBLE
- [ ] Define payload structures per action
- [ ] Define status response format (device -> remote)

## Phase 1 — Protocol Implementation

> Status: **Planned**

### Packet encode/decode
- [ ] `Packet` struct (packed, no dynamic allocation)
- [ ] `encodePacket()` — struct to byte array
- [ ] `decodePacket()` — byte array to struct
- [ ] Checksum: XOR of all bytes before checksum field
- [ ] `validateChecksum()` — verify integrity

### PlatformIO library packaging
- [ ] Create `library.json` manifest
- [ ] Test as `lib_deps` from GitHub URL
- [ ] Test as `lib_extra_dirs` for local dev
- [ ] Verify compilation on AVR (Mega 2560) and ESP32

### Unit tests
- [ ] Test encode/decode round-trip
- [ ] Test checksum calculation and validation
- [ ] Test malformed packet handling
- [ ] Test all device ID and action combinations

## Phase 2 — Driver Abstractions

> Status: **Planned**

### CommunicationDriver interface
- [ ] Abstract base class with `send()` and `receive()`
- [ ] RF24 concrete implementation (NRF24L01)
- [ ] BLE concrete implementation (ESP32 BLE)
- [ ] WiFi concrete implementation (ESP32 WiFi — optional)
- [ ] Factory or compile-time selection via build flags

### ServoUtils
- [ ] Degree to PWM pulse length conversion
- [ ] Servo range clamping with configurable min/max
- [ ] Left/right mirror calculation
- [ ] Smooth movement interpolation helpers

## Phase 3 — Integration

> Status: **Planned**

- [ ] Replace hexapod's inline protocol code with shared lib
- [ ] Integrate into remote controller firmware
- [ ] End-to-end test: remote -> hexapod via shared protocol
- [ ] Validate on both AVR and ESP32 platforms

## Phase 4 — Quality

> Status: **Planned**

- [ ] GitHub Actions CI: build on AVR + ESP32 targets
- [ ] Unit test execution in CI
- [ ] API documentation (Doxygen or inline comments)
- [ ] Versioning strategy (semver tags)

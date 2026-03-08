#ifndef IOT_PACKET_H
#define IOT_PACKET_H

#include <stdint.h>
#include <string.h>

#define IOT_PACKET_HEADER      0xAA
#define IOT_PACKET_MAX_PAYLOAD 8
#define IOT_PACKET_MIN_SIZE    5  // header + device_id + action + payload_len + checksum
#define IOT_PACKET_MAX_SIZE    (IOT_PACKET_MIN_SIZE + IOT_PACKET_MAX_PAYLOAD)

struct IotPacket {
    uint8_t device_id;
    uint8_t action;
    uint8_t payload_len;
    uint8_t payload[IOT_PACKET_MAX_PAYLOAD];
};

// Compute XOR checksum over all fields
static inline uint8_t iot_packet_checksum(const IotPacket* pkt) {
    uint8_t cs = IOT_PACKET_HEADER;
    cs ^= pkt->device_id;
    cs ^= pkt->action;
    cs ^= pkt->payload_len;
    for (uint8_t i = 0; i < pkt->payload_len && i < IOT_PACKET_MAX_PAYLOAD; i++) {
        cs ^= pkt->payload[i];
    }
    return cs;
}

// Encode a packet into a byte buffer. Returns the number of bytes written.
// buf must be at least IOT_PACKET_MAX_SIZE bytes.
static inline uint8_t iot_packet_encode(const IotPacket* pkt, uint8_t* buf) {
    uint8_t len = pkt->payload_len;
    if (len > IOT_PACKET_MAX_PAYLOAD) {
        len = IOT_PACKET_MAX_PAYLOAD;
    }

    buf[0] = IOT_PACKET_HEADER;
    buf[1] = pkt->device_id;
    buf[2] = pkt->action;
    buf[3] = len;
    memcpy(&buf[4], pkt->payload, len);
    buf[4 + len] = iot_packet_checksum(pkt);

    return 5 + len;
}

// Decode a byte buffer into a packet. Returns 0 on success, -1 on error.
static inline int8_t iot_packet_decode(const uint8_t* buf, uint8_t buf_len, IotPacket* pkt) {
    if (buf_len < IOT_PACKET_MIN_SIZE) {
        return -1;
    }
    if (buf[0] != IOT_PACKET_HEADER) {
        return -1;
    }

    pkt->device_id = buf[1];
    pkt->action = buf[2];
    pkt->payload_len = buf[3];

    if (pkt->payload_len > IOT_PACKET_MAX_PAYLOAD) {
        return -1;
    }
    if (buf_len < (uint8_t)(5 + pkt->payload_len)) {
        return -1;
    }

    memcpy(pkt->payload, &buf[4], pkt->payload_len);

    uint8_t expected_cs = iot_packet_checksum(pkt);
    uint8_t received_cs = buf[4 + pkt->payload_len];

    if (expected_cs != received_cs) {
        return -1;
    }

    return 0;
}

// Helper: create a simple packet with no payload
static inline void iot_packet_init(IotPacket* pkt, uint8_t device_id, uint8_t action) {
    pkt->device_id = device_id;
    pkt->action = action;
    pkt->payload_len = 0;
    memset(pkt->payload, 0, IOT_PACKET_MAX_PAYLOAD);
}

// Helper: create a packet with payload
static inline void iot_packet_init_with_payload(IotPacket* pkt, uint8_t device_id,
                                                 uint8_t action, const uint8_t* data,
                                                 uint8_t data_len) {
    pkt->device_id = device_id;
    pkt->action = action;
    pkt->payload_len = (data_len > IOT_PACKET_MAX_PAYLOAD) ? IOT_PACKET_MAX_PAYLOAD : data_len;
    memcpy(pkt->payload, data, pkt->payload_len);
    if (pkt->payload_len < IOT_PACKET_MAX_PAYLOAD) {
        memset(&pkt->payload[pkt->payload_len], 0, IOT_PACKET_MAX_PAYLOAD - pkt->payload_len);
    }
}

#endif

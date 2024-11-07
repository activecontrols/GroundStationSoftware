/*
GroundComms.h - Ground Station Communications Header file
Description: Header file to GroundComms.cpp. Wraps libmavskipper code to be more class-like the way other modules may expect it. Protocol used on the ground station.
Author: Vincent Wang, Francis Ozua
Created: 2024-9-12
*/

#ifndef GROUNDSTATIONCOMMS_H 
#define GROUNDSTATIONCOMMS_H 

#define FASTMAVLINK_SERIAL_WRITE_CHAR 1
#define FASTMAVLINK_IGNORE_WADDRESSOFPACKEDMEMBER
#define MAVLINK_MESSAGE_SIZE 1024

void fmav_serial_write_char(char c);

#include "./message_lib/pscom/pscom.h"
#include "telemetrymodel.h"
#include <QSerialPort>
#include <QByteArray>
#include <stdint.h>
#include <string>
#include <unordered_map>


int openSerialPort(const char* portname);
bool configureSerialPort(int fd, int speed);
int readMAVLinkMessage(int fd, char buffer[MAVLINK_MESSAGE_SIZE]);
int writeToSerialPort(int fd, const char* buffer, size_t size);

class GroundCommsManager {
public:
    GroundCommsManager();
    void init(QSerialPort* serial, int _udpfd, TelemetryModel* model);
    void spin(QByteArray buffer);
    void sendCommand(const std::string& command, float params[7], uint8_t target_system, uint8_t target_component, uint8_t confirmation); 

private:
    // Highest-level: handle all incoming messages/commands
    void processMessage(fmav_message_t *msg);
    void telemToModel(const fmav_control_system_state_t& telem_payload);

    // Internal Data
    int serialfd; // a file descriptor to the stream
    uint8_t sysid = 68; // from Vincent W's code
    uint8_t compid = 1; // from Vincent W's Code
    fmav_status_t status;
    fmav_message_t message;
    TelemetryModel* telemModel;

    std::unordered_map<std::string, uint16_t> commandMap;
    uint64_t timeOnStartup;
};

#endif

#include "GroundStationComms.h"
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>
#include <iomanip>
#include <QDebug>

#define LINUX

QSerialPort* global_serial;

void fmav_serial_write_char(char c) 
{
    global_serial->write(&c);
}

int readMAVLinkMessage(int fd, char buffer[MAVLINK_MESSAGE_SIZE])
{
    return read(fd, buffer, MAVLINK_MESSAGE_SIZE);
}

// Function to write data to the serial port
int writeToSerialPort(int fd, const char* buffer, size_t size)
{
    return write(fd, buffer, size);
}

void printTelem(const fmav_control_system_state_t& telem) {
  std::cout << std::fixed << std::setprecision(2); // Set precision for floats
    std::cout << "time_usec: " << telem.time_usec << '\n';
    std::cout << "x_acc: " << telem.x_acc << ", y_acc: " << telem.y_acc << ", z_acc: " << telem.z_acc << '\n';
    std::cout << "x_vel: " << telem.x_vel << ", y_vel: " << telem.y_vel << ", z_vel: " << telem.z_vel << '\n';
    std::cout << "x_pos: " << telem.x_pos << ", y_pos: " << telem.y_pos << ", z_pos: " << telem.z_pos << '\n';
    std::cout << "airspeed: " << telem.airspeed << '\n';
    std::cout << "vel_variance: [" << telem.vel_variance[0] << ", " << telem.vel_variance[1] << ", " << telem.vel_variance[2] << "]\n";
    std::cout << "pos_variance: [" << telem.pos_variance[0] << ", " << telem.pos_variance[1] << ", " << telem.pos_variance[2] << "]\n";
    std::cout << "q (quaternion): [" << telem.q[0] << ", " << telem.q[1] << ", " << telem.q[2] << ", " << telem.q[3] << "]\n";
    std::cout << "roll_rate: " << telem.roll_rate << ", pitch_rate: " << telem.pitch_rate << ", yaw_rate: " << telem.yaw_rate << '\n';
}

GroundCommsManager::GroundCommsManager() {}

void GroundCommsManager::init(QSerialPort* serial)
{
  global_serial = serial;
}

void GroundCommsManager::spin(QString buffer)
{
    qDebug() << "Spinning message\n";
    for (uint16_t i = 0; i < buffer.length(); i++) {
        char c = buffer[i].unicode();
        uint8_t res = fmav_parse_to_msg(&(this->message), &(this->status), c);
        if (res == FASTMAVLINK_PARSE_RESULT_OK) {
            this->processMessage(&(this->message));
        }
    }
}

void GroundCommsManager::sendCommand(const std::string& command, float params[7], uint8_t target_system, uint8_t target_component, uint8_t confirmation) 
{
  fmav_command_long_t payload;
  payload.command = commandMap[command];
  payload.param1 = params[0];
  payload.param2 = params[1];
  payload.param3 = params[2];
  payload.param4 = params[3];
  payload.param5 = params[4];
  payload.param6 = params[5];
  payload.param7 = params[6];
  payload.target_system = target_system;
  payload.target_component = target_component;
  payload.confirmation = 1;
  fmav_msg_command_long_encode_to_serial(
    this->sysid, this->compid, &payload, NULL
  );
}

void GroundCommsManager::processMessage(fmav_message_t *msg)
{
  qDebug() << "Processing message: ";
  switch (msg->msgid) {
    case FASTMAVLINK_MSG_ID_CONTROL_SYSTEM_STATE:
      qDebug() << "telemetry message\n";
      fmav_control_system_state_t telem_payload;
      fmav_msg_control_system_state_decode(&telem_payload, msg);
      printTelem(telem_payload);
      return;
    case FASTMAVLINK_MSG_ID_SYS_STATUS:
      qDebug() << "system status message\n";
      return;
    case FASTMAVLINK_MSG_ID_HEARTBEAT:
      qDebug() << "heartbeat message\n";
      return;
    case FASTMAVLINK_MSG_ID_CONTROLLER_STATUS:
      qDebug() << "controller status message\n";
      return;
  }

}

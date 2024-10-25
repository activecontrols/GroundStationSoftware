#include "GroundStationComms.h"
#include <cstring>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <iomanip>

#define LINUX

int global_fd;

void fmav_serial_write_char(char c) 
{
    writeToSerialPort(global_fd, &c, 1);
}

int openSerialPort(const char* portname)
{
#ifdef LINUX
    std::cout << "IN\n";
    int fd = open(portname, O_RDWR | O_NOCTTY | O_NDELAY);
    std::cout << fd << "\n";
    std::cout << "OUT\n";
    if (fd < 0) {
        std::cerr << "Error opening " << portname << ": "
             << strerror(errno) << "\n";
        return -1;
    }
    return fd;
#else
  return -1;
#endif
}

// Function to configure the serial port
bool configureSerialPort(int fd, int speed)
{
#ifdef LINUX
    struct termios tty;
    if (tcgetattr(fd, &tty) != 0) {
        std::cerr << "Error from tcgetattr: " << strerror(errno)
             << "\n";
        return false;
    }

    cfsetospeed(&tty, speed);
    cfsetispeed(&tty, speed);

    tty.c_cflag
        = (tty.c_cflag & ~CSIZE) | CS8; // 8-bit characters
    tty.c_iflag &= ~IGNBRK; // disable break processing
    tty.c_lflag = 0; // no signaling chars, no echo, no
                     // canonical processing
    tty.c_oflag = 0; // no remapping, no delays
    tty.c_cc[VMIN] = 0; // read doesn't block
    tty.c_cc[VTIME] = 5; // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF
                     | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag
        |= (CLOCAL | CREAD); // ignore modem controls,
                             // enable reading
    tty.c_cflag &= ~(PARENB | PARODD); // shut off parity
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        std::cerr << "Error from tcsetattr: " << strerror(errno)
             << "\n";
        return false;
    }
    return true;
#else
  return false;
#endif
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

void GroundCommsManager::init(const char* portname, const std::unordered_map<std::string, uint16_t>& map)
{
  commandMap = map;
  serialfd = openSerialPort(portname);
  if (serialfd < 0) {
    perror("Could not open serial port!");
    exit(1);
  }

  std::cout << "configured serial port\n";
  if (!configureSerialPort(serialfd, B9600)) {
      close(serialfd);
      perror("Could not configure serial port!");
      exit(1);
  }

  global_fd = serialfd;
}

void GroundCommsManager::spin() 
{
  char buffer[MAVLINK_MESSAGE_SIZE];
  int n = readMAVLinkMessage(serialfd, buffer);
    if (n < 0) {
        std::cerr << "Error reading from serial port: "
            << strerror(errno) << "\n";
    }
    else if (n > 0) {
        std::cout << "Read from serial port " << n << " Bytes\n";
    }

    for (uint16_t i = 0; i < n; i++) {
        char c = buffer[i];
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
  std::cout << "Received: ";
  switch (msg->msgid) {
    case FASTMAVLINK_MSG_ID_CONTROL_SYSTEM_STATE:
      std::cout << "telemetry message\n";
      fmav_control_system_state_t telem_payload;
      fmav_msg_control_system_state_decode(&telem_payload, msg);
      printTelem(telem_payload);
      return;
    case FASTMAVLINK_MSG_ID_SYS_STATUS:
      std::cout << "system status message\n";
      return;
    case FASTMAVLINK_MSG_ID_HEARTBEAT:
      std::cout << "heartbeat message\n";
      return;
    case FASTMAVLINK_MSG_ID_CONTROLLER_STATUS:
      std::cout << "controller status message\n";
      return;
  }

}

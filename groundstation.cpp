#include <stdlib.h>
#include <time.h>
#include <string>
#include <unordered_map>
#include <pthread.h>
#include <unistd.h>

#include "GroundStationComms.h"
/*
groundstation.cpp 
Description: Runs the groundstation software
Author: Francis Ozua
*/


#define MYLED 32
#define PORTNAME "/dev/tty.usbmodem110956801"
GroundCommsManager comms;



int main(int argc, char* argv[]) {
  srand(time(NULL));
  std::unordered_map<std::string, uint16_t> commands;
  commands["laugh"] = 100;
  commands["do a roll"] = 200;
  commands["get a W with a V"] = 300;
  comms.init(PORTNAME, commands);

  while (1) {
    comms.spin();
    sleep(1);
  }
}

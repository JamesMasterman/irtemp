#ifndef TEMP_LOGGER
#define TEMP_LOGGER

#include <stdint.h>
#include "application.h"
#include <PubSubClient.h>
#include "mqttlogger.h"

class TempLogger: public MQTTLogger
{

public:
  TempLogger();
  ~TempLogger();

public:
  void Send(double temp);

private:
  bool SendData(double temp);
};

#endif

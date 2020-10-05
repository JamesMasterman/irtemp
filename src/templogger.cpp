#include "templogger.h"


TempLogger::TempLogger()
{

}

TempLogger::~TempLogger()
{

}

void TempLogger::Send(double temp)
{
    if(!SendData(temp))
    {
      EnsureConnected();
      SendData(temp);
    }
}

bool TempLogger::SendData(double temp)
{
    // Prepare JSON payload
    snprintf(m_mqttPub, sizeof(m_mqttPub), "{\"temperature\":%.1f}", temp);

    // Send payload
    bool result = psClient->publish("v1/devices/me/telemetry", m_mqttPub);            // Topic, payload
    result = psClient->loop() && result;
    BlinkLED();
    return result;
}

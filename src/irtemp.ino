#include "templogger.h"
#include "tempreader.h"


//Thingsboard settings
const char THINGSBOARD_SERVER[] = "192.168.1.8";
const char DeviceAttributes[] = "{\"firmware_version\":\"1.5.2\",\"software_version\":\"1.0\"}";
#define THINGSBOARD_PORT 1883
#define TOKEN "nO8pt1o9xxt43FqMKsDK"

const unsigned long ONE_MIN_MS = 60*1000;
const unsigned long WATCHDOG_TIMEOUT_MS = 15*ONE_MIN_MS; //timeout for watchdog
const unsigned long LOOP_TIME_MS= 30000; //30 second send interval
const unsigned long WIFI_TIMEOUT_MS = 30*1000; //30 second timeout waiting for the wifi

STARTUP(WiFi.selectAntenna(ANT_INTERNAL));
ApplicationWatchdog wd(WATCHDOG_TIMEOUT_MS, System.reset);
SYSTEM_MODE(SEMI_AUTOMATIC);

TempLogger* logger;
TempReader* reader;

unsigned long lastSend;

void setup()
{
    //Serial.begin(9600);
    startWifi();
    reader = new TempReader();
    logger = new TempLogger();
    logger->Setup(THINGSBOARD_SERVER, THINGSBOARD_PORT, DeviceAttributes, TOKEN);
}

void startWifi()
{
  //Sync the time
  if(!WiFi.ready())
  {
     WiFi.on();
     WiFi.connect();
     waitFor(WiFi.ready, WIFI_TIMEOUT_MS);
  }
}

void loop()
{
  unsigned long start = millis();

  //Tell the watchdog we are still alive
  wd.checkin();

  startWifi();
  logger->Send(reader->GetTemp());

  //wait till next loop
  unsigned long readDiff = millis() - start;
  delay(LOOP_TIME_MS - readDiff);
}

void print()
{
  Serial.print("Temp ");
  Serial.println(reader->GetTemp());
}

/*
    Compiled for the NODEMCU-32S
 */

#include <esp_now.h>
#include <WiFi.h>

#define WIFI_CHANNEL 1
esp_now_peer_info_t slave;
uint8_t remoteMac[] = {0x36, 0x33, 0x33, 0x33, 0x33, 0x33};
const uint8_t maxDataFrameSize=250;
const esp_now_peer_info_t *peer = &slave;
uint8_t dataToSend[maxDataFrameSize];
byte cnt=0;

void setup()
{
  Serial.begin(115200);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  esp_now_init();
  delay(10);
  memcpy( &slave.peer_addr, &remoteMac, 6 );
  slave.channel = WIFI_CHANNEL;
  slave.encrypt = 0;
  esp_now_add_peer(peer);
}

void loop()
{
  for(cnt=0; cnt<maxDataFrameSize; cnt++)
  {
    dataToSend[cnt]++;
  }
  esp_now_send(slave.peer_addr, dataToSend, maxDataFrameSize);
  delay(10);
}

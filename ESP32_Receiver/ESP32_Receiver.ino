/*
    Compiled for the NODEMCU-32S
 */

#include <esp_now.h>
#include <WiFi.h>

#define WIFI_CHANNEL 1
uint8_t localCustomMac[] = {0x36, 0x33, 0x33, 0x33, 0x33, 0x33};
const byte maxDataFrameSize = 250;
byte cnt=0;

void setup()
{
  Serial.begin(115200);
  esp_base_mac_addr_set(localCustomMac);
  WiFi.mode(WIFI_AP_STA); 
  esp_now_init();
  delay(10);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
 
}

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
  Serial.println(data[0], DEC);
}

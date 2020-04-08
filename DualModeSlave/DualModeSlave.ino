/*

  Slave/Node:
    Receives a 100Byte ESPNOW data block, and repies with same
    MASTER ADDRESS[0x3C,0x3C,0x3C,0x3C,0x3C,0x30]
    SELF = [0x3C,0x3C,0x3C,0x3C,0x3C,0x31]
 */
extern "C" {
  #include "user_interface.h"
  #include <espnow.h>
}
byte localDevice[] = {0x3C,0x3C,0x3C,0x3C,0x3C,0x31};
void initVariant()
{
   wifi_set_opmode(STATIONAP_MODE);
   wifi_set_macaddr(STATION_IF, &localDevice[0]);
}

#include <ESP8266WiFi.h>
#define WIFI_CHANNEL 1
//MAC ADDRESS OF THE DEVICE YOU ARE SENDING TO
byte remoteDevice[6] = {0x3C,0x3C,0x3C,0x3C,0x3C,0x30};
const byte dataLength=200;
byte cnt=0;
byte rcvData[dataLength];
long timerData[3];

void setup()
{
  Serial.begin(115200);
  Serial.print("\r\n\r\nDevice MAC: ");
  //WiFi.mode(WIFI_AP_STA);
  //WiFi.begin();
  Serial.println(WiFi.macAddress());
  Serial.println("\r\nESP_Now Dual Mode Transmitter + Receiver [SLAVE].\r\n");
  esp_now_init();
  delay(10);
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(remoteDevice, ESP_NOW_ROLE_CONTROLLER, WIFI_CHANNEL, NULL, 0);

  esp_now_register_recv_cb([](uint8_t *mac, uint8_t *data, uint8_t len)
  {
    esp_now_send(remoteDevice, data, len);
    //Serial.printf("Received\t %d\r\n", data[0]);
    //memcpy(txrxData, data, len );
  });
}  

void loop()
{
  yield();
}

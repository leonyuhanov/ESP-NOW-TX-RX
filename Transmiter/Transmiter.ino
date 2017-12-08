#include <ESP8266WiFi.h>
extern "C" {
  #include <espnow.h>
}

#define WIFI_CHANNEL 1

//MAC ADDRESS OF THE DEVICE YOU ARE SENDING TO
byte remoteMac[] = {0x36, 0x33, 0x33, 0x33, 0x33, 0x33};
const byte dataLength=7;
byte cnt=0;
byte rcvData[dataLength];
byte result;

void setup()
{
  Serial.begin(115200);
  //Serial.print("\r\n\r\nDevice MAC: ");
  //Serial.println(WiFi.macAddress());
  //Serial.println("\r\nESP_Now Controller.");
  WiFi.disconnect();
  esp_now_init();
  delay(10);
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(remoteMac, ESP_NOW_ROLE_COMBO, WIFI_CHANNEL, NULL, 0);
}  

void loop()
{
  for(cnt=0; cnt<dataLength; cnt++)
  {
    rcvData[cnt]++;
  }
  
  result = esp_now_send(remoteMac, rcvData, dataLength);
  Serial.println(result);
  delay(100);
}


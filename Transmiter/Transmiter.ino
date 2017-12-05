#include <ESP8266WiFi.h>
extern "C" {
  #include <espnow.h>
}

#define WIFI_CHANNEL 1

//MAC ADDRESS OF THE DEVICE YOU ARE SENDING TO
byte remoteMac[] = {0x60, 0x01, 0x94, 0x1D, 0x49, 0xBC};
const byte dataLength=7;
byte cnt=0;
byte rcvData[dataLength];

void setup()
{
  Serial.begin(115200);
  Serial.print("\r\n\r\nDevice MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.println("\r\nESP_Now Controller.");
  WiFi.disconnect();

  if (esp_now_init() != 0)
  {
    Serial.println("*** ESP_Now init failed");
    ESP.restart();
  }
  delay(10);
  
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  Serial.println(esp_now_add_peer(remoteMac, ESP_NOW_ROLE_COMBO, WIFI_CHANNEL, NULL, 0));
}  

void loop()
{
  if(rcvData[0]==255)
  {
    Serial.printf("\r\nBlock %i",rcvData[0]);
  }
  for(cnt=0; cnt<dataLength; cnt++)
  {
    rcvData[cnt]++;
  }
  esp_now_send(remoteMac, rcvData, dataLength);
  yield();
  
}


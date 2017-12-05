#include <ESP8266WiFi.h>
extern "C" {
  #include <espnow.h>
}

byte cnt=0;

void setup()
{
  Serial.begin(115200);
  Serial.print("\r\n\r\nDevice MAC: ");
  Serial.println(WiFi.macAddress());
  Serial.println("\r\nESP_Now Node.");
  WiFi.mode(WIFI_AP_STA);

  if (esp_now_init() != 0)
  {
    Serial.println("*** ESP_Now init failed");
    ESP.restart();
  }
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    
  esp_now_register_recv_cb([](uint8_t *mac, uint8_t *data, uint8_t len)
  {
    if(data[0]==255)
    {
      for(cnt=0; cnt<len; cnt++)
      {
        Serial.print(data[cnt], DEC);
        Serial.print("\t");
      }
      Serial.print("\r\n");
    }
  });
}

void loop()
{
  
}


/*

  Master/Server:
    Sends a 100Byte ESPNOW data block, and awaits a response
    SLAVE ADDRESS[84:F3:EB:B3:66:CC]
    SELF=68:C6:3A:9F:77:88
 */
#include <ESP8266WiFi.h>
extern "C" {
  #include <espnow.h>
}

#define WIFI_CHANNEL 1

//MAC ADDRESS OF THE DEVICE YOU ARE SENDING TO
byte remoteDevice[6] = {0x84, 0xF3, 0xEB, 0xB3, 0x66, 0xCC};
const byte dataLength=100;
byte cnt=0;
byte txrxData[dataLength];
long timerData[3];

void setup()
{
  Serial.begin(115200);
  //Serial.print("\r\n\r\nDevice MAC: ");
  //WiFi.mode(WIFI_STA);
  //WiFi.begin();
  //Serial.println(WiFi.macAddress());
  Serial.println("\r\nESP_Now Dual Mode Transmitter + Receiver [MASTER].\r\n");
  esp_now_init();
  delay(10);
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_add_peer(remoteDevice, ESP_NOW_ROLE_CONTROLLER, WIFI_CHANNEL, NULL, 0);

  esp_now_register_recv_cb([](uint8_t *mac, uint8_t *data, uint8_t len)
  {
    timerData[1] = micros();
    timerData[2] = timerData[1]-timerData[0];
    Serial.printf("\tReceived [%d]\tTook\t[%d]micros\r\n", data[0], timerData[2]);
    memcpy(txrxData, data, len );
  });
}  

void loop()
{
  timerData[0] = micros();
  esp_now_send(remoteDevice, txrxData, dataLength);
  Serial.printf("\tSent [%d]\r\n", txrxData[0]);
  delay(500);
  txrxData[0]++;
}


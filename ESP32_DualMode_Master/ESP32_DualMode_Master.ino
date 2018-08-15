/*
    Compiled for the NODEMCU-32S
 */

#include <esp_now.h>
#include <WiFi.h>

#define WIFI_CHANNEL 1
esp_now_peer_info_t slave;
uint8_t remoteMac[] = {0x30, 0xAE, 0xA4, 0x27, 0xCE, 0xAD};
const uint8_t maxDataFrameSize=200;
const esp_now_peer_info_t *peer = &slave;
uint8_t dataToSend[maxDataFrameSize];
byte cnt=0;

void setup()
{
  Serial.begin(115200);
  Serial.print("\r\n\r\n");
  
  WiFi.mode(WIFI_STA);
  Serial.println( WiFi.macAddress() );
  WiFi.disconnect();
  if(esp_now_init() == ESP_OK)
  {
    Serial.println("ESP NOW INIT!");
  }
  else
  {
    Serial.println("ESP NOW INIT FAILED....");
  }
  
  
  memcpy( &slave.peer_addr, &remoteMac, 6 );
  slave.channel = WIFI_CHANNEL;
  slave.encrypt = 0;
  if( esp_now_add_peer(peer) == ESP_OK)
  {
    Serial.println("Added Peer!");
  }

  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop()
{
  for(cnt=0; cnt<maxDataFrameSize; cnt++)
  {
    dataToSend[cnt]++;
  }
  if( esp_now_send(slave.peer_addr, dataToSend, maxDataFrameSize) == ESP_OK)
  {
    Serial.printf("\r\nSuccess Sent Value->\t%d", dataToSend[0]);
  }
  else
  {
    Serial.printf("\r\nDID NOT SEND....");
  }
  delay(250);
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.print(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
  Serial.printf("\r\nReceived\t%d Bytes\t%d", data_len, data[0]);
}

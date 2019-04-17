/*
    Compiled for the NODEMCU-32S
 */

#include <esp_now.h>
#include <WiFi.h>

#define WIFI_CHANNEL 1
esp_now_peer_info_t slave;
//30:AE:A4:21:B4:89
uint8_t remoteMac[] = {0x30, 0xAE, 0xA4, 0x21, 0xB4, 0x89};
const uint8_t maxDataFrameSize=250;
const esp_now_peer_info_t *peer = &slave;
uint8_t dataToSend[maxDataFrameSize];
byte cnt=0;
long timers[3];

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
    timers[0] = micros();
    //Serial.printf("\r\nSuccess Sent Value->\t%d", dataToSend[0]);
  }
  else
  {
    Serial.printf(".");
  }
  delay(10);
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  //Serial.print("\r\nLast Packet Send Status:\t");
  //Serial.print(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
  if(data[0] == dataToSend[0])
  {
    timers[1] = micros();
    timers[2] = timers[1]-timers[0];
    Serial.printf("\r\nReceived\t%d Bytes val\t%d\tin %d micros", data_len, data[0], timers[2]);
  }
  else
  {
    Serial.printf("\r\nReceived\t%d Bytes\t%d", data_len, data[0]);
  }
}

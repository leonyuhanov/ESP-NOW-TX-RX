/*
    Compiled for the NODEMCU-32S
 */

#include <esp_now.h>
#include <WiFi.h>

#define WIFI_CHANNEL 1

uint8_t masterDeviceMac[] = {0x30, 0xAE, 0xA4, 0x27, 0xA9, 0x48};
esp_now_peer_info_t master;
const esp_now_peer_info_t *masterNode = &master;
const byte maxDataFrameSize = 200;
uint8_t dataToSend[maxDataFrameSize];
byte cnt=0;
esp_err_t sendResult;

void setup()
{
  Serial.begin(115200);
  Serial.print("\r\n\r\n");
  WiFi.mode(WIFI_AP); 
  Serial.println( WiFi.softAPmacAddress() );
  WiFi.disconnect();
  if(esp_now_init() == ESP_OK)
  {
    Serial.println("ESPNow Init Success!");
  }
  else
  {
    Serial.println("ESPNow Init Failed....");
  }

  //Add the master node to this slave node
  memcpy( &master.peer_addr, &masterDeviceMac, 6 );
  master.channel = WIFI_CHANNEL;
  master.encrypt = 0;
  master.ifidx = ESP_IF_WIFI_AP;
  //Add the remote master node to this slave node
  if( esp_now_add_peer(masterNode) == ESP_OK)
  {
    Serial.println("Added Master Node!");
  }
  else
  {
    Serial.println("Master Node could not be added...");
  }
  
  esp_now_register_recv_cb(OnDataRecv);
  esp_now_register_send_cb(OnDataSent);
  
}

void loop()
{
 yield();
}

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len)
{
  Serial.printf("\r\nReceived\t%d Bytes\t%d", data_len, data[0]);
  memcpy( dataToSend, data, data_len );
  
  sendResult = esp_now_send(master.peer_addr, dataToSend, maxDataFrameSize);
  if (sendResult == ESP_OK) {
    Serial.println("Success");
  } else if (sendResult == ESP_ERR_ESPNOW_NOT_INIT) {
    // How did we get so far!!
    Serial.println("ESPNOW not Init.");
  } else if (sendResult == ESP_ERR_ESPNOW_ARG) {
    Serial.println("Invalid Argument");
  } else if (sendResult == ESP_ERR_ESPNOW_INTERNAL) {
    Serial.println("Internal Error");
  } else if (sendResult == ESP_ERR_ESPNOW_NO_MEM) {
    Serial.println("ESP_ERR_ESPNOW_NO_MEM");
  } else if (sendResult == ESP_ERR_ESPNOW_NOT_FOUND) {
    Serial.println("Peer not found.");
  } 
    else if (sendResult == ESP_ERR_ESPNOW_IF) {
    Serial.println("Interface Error.");
  }   else {
    Serial.printf("\r\nNot sure what happened\t%d", sendResult);
  }
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.print(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

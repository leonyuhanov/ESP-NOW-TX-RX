# ESP-NOW-TX-RX
A very basic TX and RX demo for the ESP-NOW Protocol for the ESP8266 &amp; ESP32

# DUAL Mode RX/TX on 2 devices
DualModeMaster : Has code for a master/server that sends a PING with a 100Byte data packet to the slave and prints the time in micros for it to return
DualModeSlave : Has code for a slave/node that waits for a PING with a 100Byte data packet and returns same

# Setup Instructions FOR the ESP8266
If you are using Arduino IDE you need to do the following before compiling:
1. Make sure you have the LATEST espnow.h file get it form here https://github.com/esp8266/Arduino/blob/d24a358817f0c11f7087b3c8acbf24629b15998f/tools/sdk/include/espnow.h and replace what you have in 
C:\Users\YOUR_USER_NAME\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.3.0\tools\sdk\include

2. Open the file C:\Users\YOUR_USER_NAME\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.3.0\platform.txt
find the line that starts with "compiler.c.elf.libs" add the following(without talking marks) to the END OF THE LINE and save "-lespnow"

# Things I found deep in the rabbit hole
- Espressif docs state that the maximum payload per frame is 250 bytes. On the ESP8266 I found that 200 bytes is the real maximum. Anything over 200 bytes will return an error. On the ESP32 you CAN send 250 bytes. 
- Broadcasting does not work in the sense that you would expect it to. In the ESP32 branch of this code, you can add 1 peer with a mac adrress of FF:FF:FF:FF:FF:FF and any data sent to that peer SHOULD theoreticaly transmit to ALL devices on that chanel. This is not the case on the ESP8266. You can iether add a bunch of peers and cycle though them to send the same data OR set each peers MAC address to the be the same VIA:

```
 extern "C"{
   #include <espnow.h>
   #include "user_interface.h"
 }
 uint8_t mac[] = {0x36, 0x33, 0x33, 0x33, 0x33, 0x33};
 void initVariant()
 {
   wifi_set_macaddr(STATION_IF, &mac[0]);
 }
```
- Espressif docs state that sending data to "NULL" is also a broadcast, however this does NOT work for the ESP8266, But DOES work on the ESP32

- ESP-Now Seems to work between devices. I have testes an ESP8266 as a TX to an ESP32 as an RX, but there seemed to be iether dropped frames or delays in receiveing frames


# ESP-NOW-TX-RX
A very basic TX and RX demo for the ESP-NOW Protocol for the ESP8266 &amp; ESP32

If you are using Arduino IDE you need to do the following before compiling:
1. Make sure you have the LATEST espnow.h file get it form here https://github.com/esp8266/Arduino/blob/d24a358817f0c11f7087b3c8acbf24629b15998f/tools/sdk/include/espnow.h and replace what you have in 
C:\Users\YOUR_USER_NAME\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.3.0\tools\sdk\include

2. Open the file C:\Users\YOUR_USER_NAME\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.3.0\platform.txt
find the line that starts with "compiler.c.elf.libs" add the following(without talking marks) to the END OF THE LINE and save "-lespnow"

HAVE FUN

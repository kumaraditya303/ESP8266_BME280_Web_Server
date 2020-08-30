# ESP8266 Weather Station [![HitCount](http://hits.dwyl.com/kumaraditya303/ESP8266_BME280_Web_Server.svg)](http://hits.dwyl.com/kumaraditya303/ESP8266_BME280_Web_Server)
**Reads the temperature and humidity values from BME280 sensor, create a beautiful chart of the data on a webserver whose data is stored on SPIFFS memory.**
 
### Change these lines as per yours:

```cpp  
const char *ssid = "REPLACE_WITH_YOUR_SSID"; //replace with your SSID
const char *password = "REPLACE_WITH_YOUR_PASSWORD"; // replace with your Password
```

### For SPI Communication- Uncomment the following lines:  
```c
/*#include <SPI.h>
#define BME_SCK 14
#define BME_MISO 12
#define BME_MOSI 13
#define BME_CS 15*/
```

#### For Hardware SPI Communication- Uncomment the following lines:
      
```c
Adafruit_BME280 bme(BME_CS); // use this for hardware SPI
```

#### For Software SPI Communication- Uncomment the following lines:
```c
Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // use this for software SPI
```
      
#### Comment the following lines for SPI:
```c
#include <Wire.h>    // use this for I2C
Adafruit_BME280 bme; // use this for I2C
```

# Parts list:
[NodeMCU](https://amzn.to/397GzNe)  
[BME280 Sensor](https://amzn.to/2xlIAII)  
[Jumper Wires](https://amzn.to/2U9lWMz)  
  

**Download [ESPAsyncWebServer library](https://github.com/me-no-dev/ESPAsyncWebServer/archive/master.zip)**
  

**Download [ESPAsyncTCP library](https://github.com/me-no-dev/ESPAsyncTCP/archive/master.zip)**
  

**Download [ESP8266 Filesystem Uploader](https://github.com/esp8266/arduino-esp8266fs-plugin/releases/download/0.5.0/ESP8266FS-0.5.0.zip)**


**Download [Project file](https://github.com/rahuladitya303/ESP8266_BME280_Web_Server/releases/download/1.0/ESP8266_BME280_Web_Server.zip)**

  
# Project made and maintained by [Kumar Aditya](https://github.com/rahuladitya303/)

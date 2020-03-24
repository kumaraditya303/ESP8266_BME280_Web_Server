/*
  Project made and maintained by Kumar Aditya

  ESP8266 Weather Station
  Reads the temperature and humidity values from BME280 sensor, create a beautiful chart of the data 
  on a webserver whose data is stored on SPIFFS memory.
  
  Change these lines as per yours:
    const char *ssid = "REPLACE_WITH_YOUR_SSID";         // replace with your SSID
    const char *password = "REPLACE_WITH_YOUR_PASSWORD"; // replace with your Password

  For SPI Communication- Uncomment the following lines:
    #include <SPI.h>
    #define BME_SCK 14
    #define BME_MISO 12
    #define BME_MOSI 13
    #define BME_CS 15

    For Hardware SPI Communication- Uncomment the following lines:
      Adafruit_BME280 bme(BME_CS); // use this for hardware SPI

    For Software SPI Communication- Uncomment the following lines:
      Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // use this for software SPI
      
  & Comment the following lines:
    #include <Wire.h>    // use this for I2C
    Adafruit_BME280 bme; // use this for I2C

  Parts list:
  NodeMCU :
  https://amzn.to/397GzNe
  BME280 Sensor:
  https://amzn.to/2xlIAII
  Jumper Wires:
  https://amzn.to/2U9lWMz
  
  The source code can be found at:
  https://github.com/rahuladitya303/ESP8266_BME280_Web_Server/
  
  Download ESPAsyncWebServer library :
  https://github.com/me-no-dev/ESPAsyncWebServer/archive/master.zip

  Download ESPAsyncTCP library :
  https://github.com/me-no-dev/ESPAsyncTCP/archive/master.zip

  Download ESP8266 Filesystem Uploader :
  https://github.com/esp8266/arduino-esp8266fs-plugin/releases/download/0.5.0/ESP8266FS-0.5.0.zip
  
*/

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

/*#include <SPI.h>
  #define BME_SCK 14
  #define BME_MISO 12
  #define BME_MOSI 13
  #define BME_CS 15*/
//Adafruit_BME280 bme(BME_CS); // use this for hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // use this for software SPI

#include <Wire.h>    // use this for I2C
Adafruit_BME280 bme; // use this for I2C

const char *ssid = "REPLACE_WITH_YOUR_SSID";         // replace with your SSID
const char *password = "REPLACE_WITH_YOUR_PASSWORD"; // replace with your Password

AsyncWebServer server(80); // start AsyncWebServer as server at port 80

String readBME280Temperature() // returns temperature reading from BME280 as String
{
  float t = bme.readTemperature();
  if (isnan(t))
  {
    Serial.println("Failed to read from BME280 sensor!");
    return "";
  }
  else
  {
    Serial.println(t);
    return String(t);
  }
}

String readBME280Humidity() // returns humidity reading from BME280 as String
{
  float h = bme.readHumidity();
  if (isnan(h))
  {
    Serial.println("Failed to read from BME280 sensor!");
    return "";
  }
  else
  {
    Serial.println(h);
    return String(h);
  }
}

void setup()
{
  Serial.begin(115200); // change baudrate as per your need
  // start I2C communication
  bool status = bme.begin(0x76);
  if (!status)
  {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1)
      ;
  }

  // Initialize SPIFFS
  if (!SPIFFS.begin())
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print("Connecting to WiFi..");
    Serial.print(".");
  }
  Serial.print("\nConnected to the WiFi network: ");
  Serial.print(WiFi.SSID());
  Serial.print("IP address:");
  Serial.print(WiFi.localIP());

  // send index.html file from SPIFFS
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html");
  });
  // send style.css file from SPIFFS
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });
  // send script.js file from SPIFFS
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/script.js", "text/javascript");
  });
  // send BME280 temperature
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", readBME280Temperature().c_str());
  });
  // send BME280 humidity
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send_P(200, "text/plain", readBME280Humidity().c_str());
  });

  server.begin(); // begin server at port 80
}

void loop()
{
}

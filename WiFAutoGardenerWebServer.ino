/*
    This project is intended to upload IoT gardening measurements backend
    Device registration logic is included with unique token generated


*/

//including display for 8266
//https://www.teachmemicro.com/1-3-i2c-oled-arduino-esp8266-tutorial/

#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "M&P-2.4"  //Default wifi station
#define STAPSK  "Budapest2020"
#endif


int HSOIL_PIN       =         2;      //ADC used to measure Soil Humidity
int HUMTEMPAIR_PIN  =         14;      //GPIO #4 used to measure Air Humidity and Temperature
int LIGHT_PIN       =         13;      //GPIO #4 used to measure Light Intensity



pinMode(HUMTEMPAIR_PIN, INPUT);
pinMode(HSOIL_PIN, INPUT);
pinMode(LIGHT_PIN, INPUT);


float hsoil =0.0;  //Soil Humidity level
float lux = 0.0; // Calculating light intensity
float hair= 0.0; //Analog channel moisture read
float temp= 0.0 //Ambient temperature

const char* ssid = STASSID;
const char* password = STAPSK;



// prepare LED
  pinMode(LED_BUILTIN, OUTPUT);//to review
  digitalWrite(LED_BUILTIN, 0);

//prepare Inputs



// Create an instance of the server
// specify the port to listen on as an argument
//WiFiServer server(80);

void loop() {
  Serial.begin(115200);

  

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));

  // Start the server
  //server.begin();
  //Serial.println(F("Server started"));

  // Print the IP address
  Serial.println(WiFi.localIP());

  h = dht.readHumidity();    //Read humidity level
  t = dht.readTemperature(); //Read temperature in celcius

  //Reads sensors values




  //Sends them to server via http
















//sleeps to save some battery

  ESP.deepSleep(30e6); //restarts after 30 seconds
}



/*
    This project is intended to upload IoT gardening measurements backend
    Device registration logic is included with unique token generated

    This sketch demonstrates how to set up a simple HTTP-like server.
    The server will set a GPIO pin depending on the request
      http://server_ip/gpio/0 will set the GPIO2 low,
      http://server_ip/gpio/1 will set the GPIO2 high
    server_ip is the IP address of the ESP8266 module, will be
    printed to Serial when the module is connected.
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



pinMode(TEMP_PIN, INPUT);
pinMode(HSOIL_PIN, INPUT);
pinMode(HAIR_PIN, INPUT);
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




















  ESP.deepSleep(30e6); //restarts after 30 seconds
}



void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  //if (!client) {
  //  return;
  //}
  //Serial.println(F("new client"));

  client.setTimeout(5000); // default is 1000

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(F("request: "));
  Serial.println(req);

  // Match the request
  int val;
  if (req.indexOf(F("/gpio/0")) != -1) {
    val = 0;
  } else if (req.indexOf(F("/gpio/1")) != -1) {
    val = 1;
  } else {
    Serial.println(F("invalid request"));
    val = digitalRead(LED_BUILTIN);
  }

  // Set LED according to the request
  digitalWrite(LED_BUILTIN, val);

  // read/ignore the rest of the request
  // do not client.flush(): it is for output only, see below
  while (client.available()) {
    // byte by byte is not very efficient
    client.read();
  }
  







  // Match the request, to review
  int value = LOW;
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  if (request.indexOf("/Up=ON") != -1)  {

     f = (h * 1.8) + 32;        //Temperature converted to Fahrenheit
     reading = analogRead(Raw);           //Analog pin reading output voltage by water moisture rain sensor
     percentage = (reading/1024) * 100;   //Converting the raw value in percentage

    if (reading<=110){  // If less mositure in soil start the motor otherwise stop
    digitalWrite(Solenoid, HIGH);
    value = HIGH;
    }
    else {
    digitalWrite(Solenoid, LOW);
    value = LOW;
    }
    
  }

 
  // Send the response to the client
  // it is OK for multiple small client.print/write,
  // because nagle algorithm will group them into one single packet
  client.print(F("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now "));
  client.print((val) ? F("high") : F("low"));
  client.print(F("<br><br>Click <a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/1'>here</a> to switch LED GPIO on, or <a href='http://"));
  client.print(WiFi.localIP());
  client.print(F("/gpio/0'>here</a> to switch LED GPIO off.</html>"));
  client.print("Soil Humidity Percentage =");
  client.print(percentage);
  client.print("%");
  client.println("<br><br>");
  if(value == HIGH) 
    client.println("Motor/Pump Operational");
   else 
    client.print("Motor/Pump at Halt");
  client.println("<br><br>");
  client.println("<a href=\"/Up=ON\"\"><button>Update = Temperature  Humidity Moisture Values</button></a><br />"); 
  client.println("<a href=\"/Solenoid=ON\"\"><button>Motor Pump On </button></a>");
  client.println("<a href=\"/Solenoid=OFF\"\"><button>Motor Pump Off </button></a><br />"); 
  client.println("</html>");
  delay(1);
  // The client will actually be *flushed* then disconnected
  // when the function returns and 'client' object is destroyed (out-of-scope)
  // flush = ensure written data are received by the other side
  Serial.println(F("Disconnecting from client"));



  ESP.deepSleep(30e6); //restarts after 30 seconds
}

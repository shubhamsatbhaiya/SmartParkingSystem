/*
 *  This is code for esp8266 wifi module -by JIIT_RSATECH TEAM FOR DELOITTE TECHNOUTSAV COMPETITION
 *  
 *  
 *  
 *
 */
#include <ESP8266WiFi.h>
const char* ssid     = "sj";//THE SSID FOR WIFI YOU CONNECT OR HOTSPOT OF MOBILE 
const char* password = "shubhamjain";//PASSWORD FOR THE WIFI TO BE STORED HERE
const char* host = "bossiot.netai.net";//THE WEBSITE NAME OF YOUR SERVER
String line;
char data[20];
void setup() {
  Serial.begin(9600);
  pinMode(0,INPUT);//INPUT THE IR SENSORS IN 0&2 PIN OF MODULE
  pinMode(2,INPUT);
  delay(10);
  
  // We start by connecting to a WiFi network
  WiFi.begin(ssid, password);
  Serial.println("connecting to network");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  Serial.println("connected");
  Serial.println(WiFi.localIP());
  //Serial.println(WiFi.localIP());
}
void loop() {
  int i=digitalRead(0);
  int j=digitalRead(2);
  delay(1000);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    return;
  }
  ///-----------------
   
   String ir1= String(i);//TYPECASTING 
   String ir2= String(j);
 
    
   //=================================
  
  // We now create a URI for the request
  String url = "/serverupload.php?slot1="+ir1+"&slot2="+ir2;
  Serial.println(url);
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      client.stop();
      return;
    }
  } 
  // Read all the lines of the reply from server and print them to Serial
  
}



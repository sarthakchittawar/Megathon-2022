#include <PubSubClient.h>
#include <WiFi.h>
#include "HTTPClient.h"
#include <ArduinoJson.h>

#define pin1 15
#define pin2 16
#define pin3 17

DHT dht(dht_dpin, DHTTYPE);
Servo servo1;

char* ssid = "Sarthak's Galaxy M52 5G";
char* password = "12345678";
String cse_ip = "192.168.209.231";
String cse_port = "8080";
String server = "http://" + cse_ip + ":" + cse_port + "/~/in-cse/in-name/";
String ae = "Entity";
String cnt = "Pothole";


void createCI(String &val)
{
  HTTPClient http;
  http.begin(server + ae + "/" + cnt + "/");
  http.addHeader("X-M2M-Origin", "admin:admin");
  http.addHeader("Content-Type", "application/json;ty=4");
  delay(1000);
  int code = http.POST("{\"m2m:cin\": {\"cnf\":\"application/json\",\"con\": " + String(val) + "}}");

  Serial.println(code);
  if (code == -1) {
  Serial.println("UNABLE TO CONNECT TO THE SERVER");
  }
  http.end();
  
}

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(112500);
  WiFi.begin(ssid, password);
  
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  digitalWrite(pin1, 0);
  digitalWrite(pin2, 0);
  digitalWrite(pin3, 0);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to Wifi..");
  }
  Serial.println("Connected to the WiFi network.");

  Serial.println(WiFi.localIP());

}

struct pixel
{
  int magnitude;
  int spatial_frequency;
  int phase;
};

int checkPothole(struct pixel p)
{
  // here we use CARLA simulator and its CV algorithms to check if its a pothole
  // An alternative is to use the 'Sobel Edge Detection Algorithm'
  return 1;
}

void loop() {
  // put your main code here, to run repeatedly:

    struct pixel img[1080][1920];
    for(int i=0; i<1080; i++)
    {
      for(int j=0; j < 1920; j++)
      {
        img[i][j]->magnitude = analogRead(pin1);
        img[i][j]->spatial_frequency = analogRead(pin2);
        img[i][j]->phase = analogRead(pin3);

        // refresh pixel command
      }
    }
    
    int val1 = checkPothole(img);
    
    cnt = "Pothole";
    createCI(val1);

}

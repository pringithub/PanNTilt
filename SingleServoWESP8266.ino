/*
 * This file moves a servo controlled by a potentiometer 
 * 
 * File created by Phil Ring
 */ 

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h> 

#define SERVO_PIN   5 // change
#define POT_PIN     7 // change?

Servo myservo;  
 
MDNSResponder mdns;

// Replace with your network credentials
const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

ESP8266WebServer server(80);

String webPage = "";


int curAngle = 0;

int moveToAngle(Servo servo, int angle, int pos, int step=1) {
  //error checking for now
  if (angle < 0 || angle > 180) return 0;

  if (pos < angle) {
	for(; pos <= angle; pos += step) {                                  
      servo.write(pos);               
      delay(15);                        
    }
  } else {
    for(; pos >= angle; pos -= step) {                                
      servo.write(pos);               
      delay(15);                        
    }
  }

  return pos;
}

// scaled between 0 and 180
int scalePotVal(int potVal) {
  return potVal; // scale somehow lol 
}

void servoHandler(int buttonVal) {
    server.send(200, "text/html", webPage);
    int desiredAngle = buttonVal;
    if (desiredAngle != curAngle) { // save processing, only write on change
      curAngle = moveToAngle(myservo, desiredAngle, curAngle);
	}
    delay(1000);
}

void setup() 
{ 
  myservo.attach(SERVO_PIN);  
  myservo.write(0);               
  delay(15);

  webPage += "<h1>ESP8266 Web Server</h1>";
  webPage += "<p>Servo <a href=\"0deg\"><button>O deg</button></a>&nbsp;";
  webPage += "<a href=\"45deg\"><button>45 deg</button>&nbsp;";
  webPage += "<a href=\"90deg\"><button>90 deg</button>&nbsp;";
  webPage += "<a href=\"135deg\"><button>135 deg</button>&nbsp;";
  webPage += "<a href=\"180deg\"><button>180 deg</button></a></p>";
  
  delay(1000);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
 

  // Servo handlers
  server.on("/0deg", serverHandler(0));
  server.on("/45deg", serverHandler(45));
  server.on("/90deg", serverHandler(90));
  server.on("/135deg", serverHandler(135));
  server.on("/180deg", serverHandler(180));

} 
 
void loop() 
{ 
  server.handleClient();
} 


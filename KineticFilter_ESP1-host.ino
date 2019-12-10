#include <Stepper.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WiFiUdp.h>

const char* ssid = "filterNetwork";
const char* password = "1123581321";

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);

WiFiUDP udp; 

int stepsPerRev = 2048;
int dir = 1;
int dir2 = 1;
int dir3 = 1;
int stepCount = 0;
int stepCount2 = 0;
int stepCount3 = 0;

//int joystickX = 34;

int potPin = 35;
int potPin2 = 34;
int potPin3 = 32;

Stepper mystepper(stepsPerRev, 15,0,2,4);
//Stepper mystepper2(stepsPerRev, 32,25,33,26);
Stepper mystepper2(stepsPerRev, 23,21,22,19);
Stepper mystepper3(stepsPerRev, 16,5,17,18);
//Stepper mystepper4(stepsPerRev, 19,22,21,23);

void setup() {
  Serial.begin(115200);

  //pinMode(joystickX, INPUT);
  //pinMode(potPin, INPUT);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet); 

  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:

//  int stickValX = analogRead(joystickX);

//  if (dir > 0) 
//  {
//    mystepper.step(5); //1/360th of a rev
//  }
//  else 
//  {
//    mystepper.step(-5);
//  }

//  if (stickValX > 2800) 
//  {
//    mystepper.step(5);
//  }
//  else if (stickValX < 2500)
//  {
//    mystepper.step(-5);
//  }

  int potVal = analogRead(potPin);

  int potVal2 = analogRead(potPin2);
  int potVal3 = analogRead(potPin3);

  Serial.println(String(potVal) + " " + String(potVal2) + " " + String(potVal3));
  

  if (dir > 0) 
  {
    mystepper.step(5); //1/360th of a rev
  }
  else 
  {
    mystepper.step(-5);
  }

  delay(2);

  if (dir2 > 0) 
  {
    mystepper2.step(5); //1/360th of a rev
  }
  else 
  {
    mystepper2.step(-5);
  }

  delay(2);

   if (dir3 > 0) 
  {
    mystepper3.step(5); //1/360th of a rev
  }
  else 
  {
    mystepper3.step(-5);
  }

  delay(2);

//  if (dir4 > 0) 
//  {
//    mystepper4.step(5); //1/360th of a rev
//  }
//  else 
//  {
//    mystepper4.step(-5);
//  }

  stepCount++;
  stepCount2++;
  stepCount3++;
  //stepCount4++;

  if (stepCount == 2500) 
  {
    stepCount = 0;
    dir = dir * -1;
  }

  if (stepCount2 == 2500) 
  {
    stepCount2 = 0;
    dir2 = dir2 * -1;
  }

  if (stepCount3 == 2500) 
  {
    stepCount3 = 0;
    dir3 = dir3 * -1;
  }

//  if (stepCount4 == 2500) 
//  {
//    stepCount4 = 0;
//    dir4 = dir4 * -1;
//  }
  
  //Serial.println(String(stepCount));
  //Serial.println(stepCount);

  udp.beginPacket("192.168.1.2", 5555);
 // udp.print(String(stepCount) + " " + String(stickValX));
  udp.print(String(stepCount));
  udp.endPacket();
  
  delay(10);

}

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

int initStepCount1, initStepCount2, initStepCount3;
float stepCount1, stepCount2, stepCount3;

int initPotVal1, initPotVal2, initPotVal3;

int padding = 50;

int potPin1 = 34;
int potPin2 = 35;
int potPin3 = 32;

bool firstLoop = true;

Stepper mystepper1(stepsPerRev, 16,5,17,18);
Stepper mystepper2(stepsPerRev, 15,0,2,4);
Stepper mystepper3(stepsPerRev, 23,21,22,19);

void setup() {
  Serial.begin(115200);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet); 

  server.begin();
}

void loop() {

  if (firstLoop) 
  {
     initPotVal1 = analogRead(potPin1);
     initPotVal2 = analogRead(potPin2);
     initPotVal3 = analogRead(potPin3);

     initStepCount1 = initPotVal1;
     initStepCount2 = initPotVal2;
     initStepCount3 = initPotVal3;

     stepCount1 = initPotVal1;
     stepCount2 = initPotVal2;
     stepCount3 = initPotVal3;

     firstLoop = false;
  }

  int potVal1 = analogRead(potPin1);
  int potVal2 = analogRead(potPin2);
  int potVal3 = analogRead(potPin3);

 // int potScale1 = map(potVal1, initPotVal - 2047.5, initPotVal + 2047.5, initStepCount1 - 1740, initStepCount1 + 1780);
  int potScale1 = map(potVal1, initPotVal1 - 2047.5, initPotVal1 + 2047.5, initStepCount1 - 1830, initStepCount1 + 1570);
  int potScale2 = map(potVal2, initPotVal2 - 2047.5, initPotVal2 + 2047.5, initStepCount2 - 1700, initStepCount2 + 1750);
  int potScale3 = map(potVal3, initPotVal3 - 2047.5, initPotVal3 + 2047.5, initStepCount3 - 1650, initStepCount3 + 1400);
  
  if (stepCount1 < (potScale1 - padding)) 
  {
    mystepper1.step(3); 
   // stepCount1 = stepCount1 + 1.1; 
   stepCount1++;
  }
  else if (stepCount1 > (potScale1 + padding))
  {
    mystepper1.step(-3);
    stepCount1--;
  }


  if (stepCount2 < (potScale2 - padding)) 
  {
    mystepper2.step(3); 
    stepCount2++; 
  }
  else if (stepCount2 > (potScale2 + padding))
  {
    mystepper2.step(-3);
    stepCount2--;
  }


  if (stepCount3 < (potScale3 - padding)) 
  {
    mystepper3.step(3); 
    stepCount3++;
  }
  else if (stepCount3 > (potScale3 + padding))
  {
    mystepper3.step(-3);
    stepCount3--;
  }

    Serial.println(String(potScale1) + " "  + String(stepCount1) + " " + String(potScale2) + " "  + String(stepCount2) + " " + String(potScale3) + " "  + String(stepCount3));
    //Serial.println(String(potVal1) + " "  + String(stepCount1) + " " + String(potVal2) + " "  + String(stepCount2) + " " + String(potVal3) + " "  + String(stepCount1));
    //Serial.println(String(potVal1) + " " + String(potVal2) + " " + String(potVal3));


  udp.beginPacket("192.168.1.2", 5555);
  udp.print(String(stepCount1) + " " + String(stepCount2) + " " + String(stepCount3));
  udp.endPacket();
  
  delay(3);

}

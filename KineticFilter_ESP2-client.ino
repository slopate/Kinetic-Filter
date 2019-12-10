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

int stepCount1 = 0;
int stepCount2 = 0;
int stepCount3 = 0;

int initPotVal1, initPotVal2, initPotVal3;

int potPin1 = 32;
int potPin2 = 35;
int potPin3 = 34;

int padding = 20;

bool firstLoop = true;

Stepper mystepper1(stepsPerRev, 23,21,22,19);
Stepper mystepper2(stepsPerRev, 15,0,2,4);
Stepper mystepper3(stepsPerRev, 16,5,17,18);


void setup() {
  Serial.begin(115200);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi...");
   }

  Serial.println("Connected");
  
}


void loop() {
  // put your main code here, to run repeatedly:

  int potVal1 = analogRead(potPin1);
  int potVal2 = analogRead(potPin2);
  int potVal3 = analogRead(potPin3);

  int potScale1 = map(potVal1, 0, 4096, -1000, 1000);
  int potScale2 = map(potVal2, 0, 4096, -1000, 1000);
  int potScale3 = map(potVal3, 0, 4096, -1000, 1000);
  
  if (stepCount1 < (potScale1 - padding)) 
  {
    mystepper1.step(3); 
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

  Serial.println(String(potScale1) + " "  + String(stepCount1) + " " + String(potScale2) + " "  + String(stepCount2) + " " + String(potScale3) + " "  + String(stepCount1));

  udp.beginPacket("192.168.1.2", 6666);
  udp.print(String(stepCount1) + " " + String(stepCount2) + " " + String(stepCount3));
  udp.endPacket();
  
  delay(7);

}

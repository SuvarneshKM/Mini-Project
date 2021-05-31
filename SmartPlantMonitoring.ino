// Viral Science www.viralsciencecreativity.com www.youtube.com/c/viralscience
// IOT Smart Plant Monitoring System
#define BLYNK_PRINT Serial   
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#define BLYNK_PRINT Serial

char auth[] ="----------------";               //Authentication code sent by Blynk
char ssid[] = "-------";                       //WiFi SSID
char pass[] = "-------";                       //WiFi Password

#define sensorPin D3 
int sensorState = 0;
int lastState = 0;
SimpleTimer timer;
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
   pinMode(sensorPin, INPUT);

  timer.setInterval(1000L, sendSensor);
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
   sensors.begin();
}
int sensor=0;
void sendTemps()
{
sensor=analogRead(A0);
Blynk.virtualWrite(V2,sensor);
delay(1000);
}
void loop()
{
  Blynk.run(); 
  timer.run(); 
  sendTemps();
  sensorState = digitalRead(sensorPin);
Serial.println(sensorState);

if (sensorState == 1 && lastState == 0) {
  Serial.println("needs water, send notification");
  Blynk.notify("Water your plants");
  lastState = 1;
  delay(1000);
//send notification
    
  } 
  else if (sensorState == 1 && lastState == 1) {
    //do nothing, has not been watered yet
  Serial.println("has not been watered yet");
  delay(1000);
  }
  else {
    //st
    Serial.println("does not need water");
    lastState = 0;
    delay(1000);
  }
  
  delay(100);
}

// Viral Science www.viralsciencecreativity.com www.youtube.com/c/viralscience
// IOT Smart Plant Monitoring System
#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "-------";              //Authentication code sent by Blynk
char ssid[] = "-----";                       //WiFi SSID
char pass[] = "-----";                       //WiFi Password

int sensor = 0;
int value = 0;
int motorPin = D5;

void setup()
{
  Serial.begin(115200);
  delay(100);
  Blynk.begin(auth, ssid, pass);
  pinMode(motorPin, OUTPUT);
  
}

void sendTemps()
{
  sensor = analogRead(A0);
  Blynk.virtualWrite(V2, sensor);
  delay(1000);
}

BLYNK_WRITE(V4){  // This function gets called each time something changes on the widget
  value = param.asInt();  // This gets the 'value' of the Widget as an integer
  Serial.println("value :");
  Serial.print(value);
}

void loop()
{
  Blynk.run();
  sendTemps();

  if(sensor<value){
    Serial.println("Dry : Turning on Motor");
    digitalWrite(motorPin, HIGH);
    Blynk.virtualWrite(V7, "Motor : ON");
    
    
  }
  else{
    Serial.println("Turning off Motor");
    digitalWrite(motorPin, LOW);
    Blynk.virtualWrite(V7, "Motor : OFF");
    
  }
}

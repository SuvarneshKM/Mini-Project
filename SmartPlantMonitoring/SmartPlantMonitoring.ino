#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "";              //Authentication code sent by Blynk
char ssid[] = "";                       //WiFi SSID
char pass[] = "";                       //WiFi Password

int sensor = 0;
int value = 0;
int motorPin = D5;

void setup()
{
  Serial.begin(115200);
  delay(100);
  Blynk.begin(auth, ssid, pass);
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, !LOW);
}

void send()
{
  sensor = analogRead(A0);
  sensor = abs(1024 - sensor);
  sensor = map(sensor, 0, 650, 0, 100);
  Serial.print("sensor : ");
  Serial.println(sensor);
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
  send();

  if(sensor<value){
    Serial.println("Dry : Turning on Motor");
    digitalWrite(motorPin, !HIGH);
    Blynk.virtualWrite(V7, "Motor : ON");
    
  }
  else{
    Serial.println("Turning off Motor");
    digitalWrite(motorPin, !LOW);
    Blynk.virtualWrite(V7, "Motor : OFF");
    
  }
}

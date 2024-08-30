#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


int white=7;
int yellow=8;
int green=11;
int blue=12;
int sensorPower = 6;
int sensorPin = A3;
int val = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

int lowerThreshold = 440;
int upperThreshold = 520;

void setup() {
pinMode(white,OUTPUT);
pinMode(yellow,OUTPUT);
pinMode(green,OUTPUT);
pinMode(blue,OUTPUT);
pinMode(sensorPower,OUTPUT);
digitalWrite(sensorPower, LOW);

Serial.begin(9600);
lcd.begin(16,2);  // Turn on the blacklight and print a message.
lcd.backlight();
}

void loop() {
  int sensor = readsensor();
  Serial.print("Sensor value: ");
  Serial.println(sensor);

 


  if(sensor<= 50){
    digitalWrite(white,LOW);
    digitalWrite(yellow,LOW);
    digitalWrite(green,LOW);
    digitalWrite(blue,HIGH);

    lcd.clear();
    lcd.print("Level: EMPTY!");
  
    delay(1000);
  }

  else if(sensor > 50 && sensor<=lowerThreshold){
    digitalWrite(white,LOW);
    digitalWrite(yellow,LOW);
    digitalWrite(green,HIGH);
    digitalWrite(blue,LOW);

    lcd.clear();
    lcd.print("Level: LOW!");
    delay(100);
  }
  else if(sensor>lowerThreshold && sensor<=upperThreshold){ 
    digitalWrite(yellow,HIGH);
    digitalWrite(white,LOW);
    digitalWrite(green,LOW);
    digitalWrite(blue,LOW);
    //delay(100);
    lcd.clear();
    lcd.print("Level: MEDIUM!");
    delay(100);
  }
  else if(sensor>=upperThreshold){
  digitalWrite(green,LOW);
  digitalWrite(white,HIGH);
  digitalWrite(yellow,LOW);
  digitalWrite(blue,LOW);
 
  lcd.clear();
  lcd.print("Level: HIGH!");
  delay(100);
 
  }

  //else if(sensor>660){
  //  digitalWrite(blue,HIGH);
  //  digitalWrite(white,LOW);
  //  digitalWrite(yellow,LOW);
  //  digitalWrite(green,LOW);
 
  //  lcd.clear();
  //  lcd.print("Level: VERY HIGH!");
  //  delay(1000);
  //}
 
}

int readsensor(){
  digitalWrite(sensorPower, HIGH);
  delay(10);
  val = analogRead(sensorPin);
  digitalWrite(sensorPower, LOW);
  return val;
}

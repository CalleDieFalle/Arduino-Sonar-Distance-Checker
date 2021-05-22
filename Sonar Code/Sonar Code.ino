#include "SR04.h"
#define trigPin 7
#define echoPin 6
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
SR04 sr04 = SR04(echoPin, trigPin);
 
long distance;
 
const int redPin = 3;
const int greenPin = 4;
const int bluePin = 5;
 
void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
 
  lcd.init();
  lcd.backlight();
  lcd.print("123456");
 
  Serial.begin(9600);
}
 
void loop() {
  distance = sr04.Distance();
  distance = clamp(distance, 0, 50);
  //printToScreen(distance);
  lcd.setCursor(0, 0);
  lcd.print(distance);
  lcd.print(" cm  ");
  checkDistance(distance);
}
 
int clamp(int VAL, int min, int max){
    if(VAL <= min) {
    VAL = min;
    } else if(VAL >= max) {
    VAL = max;
    }
    return VAL;
}
 
void checkDistance(long distance) {
  if (distance >= 0 && distance <= 15) {
    Red(255);
  } else if (distance >= 16 && distance < 33) {
    Green(255);
  } else {
    Blue(255);
  }
}
 
void printToScreen(long TARGET) {
  Serial.print(TARGET);
  Serial.println(" cm");
}
 
void Red(int VAL) {
  analogWrite(redPin, VAL);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, 0);
}
void Green(int VAL) {
  analogWrite(redPin, 0);
  analogWrite(greenPin, VAL);
  analogWrite(bluePin, 0);
}
void Blue(int VAL) {
  analogWrite(redPin, 0);
  analogWrite(greenPin, 0);
  analogWrite(bluePin, VAL);
}
#include<Servo.h>/ 
#include <LiquidCrystal.h> 


 
const int temperaturePin = 0;  

//buzzer
const int buzzer = 12;  

//Gas Sensor
int gasSensorPin=A1; 
int sensorval; 

//Doors
Servo servo1,servo2;
int servo1Pin=11;
int servo2Pin=10;

//RGB LED
int red_led=9; 
int green_led=8; 

//LCD
LiquidCrystal lcd(7, 6, 2, 3, 4, 5); 

//reset button
int buttonstate = 0;
const int resetbtn = 13;
int repeat = 0;

void setup()
{
  pinMode(buzzer, OUTPUT);
  
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo1.write(90);
  servo2.write(90);
  
  pinMode(red_led,OUTPUT);
  pinMode(green_led,OUTPUT);
  pinMode(resetbtn,INPUT);
  //Serial.begin(9600);
  
  lcd.begin(16,2);//initialisation of 16*2 LCD
}

void loop()
{
  	//for buzzer and tmp36 temp sensor
 	float voltage, degreesC;
  	voltage = getVoltage(temperaturePin);
	degreesC = (voltage - 0.5) * 100.0;
	
  	sensorval=analogRead(gasSensorPin);
  	//Serial.print(sensorval);
 	buttonstate = digitalRead(resetbtn);
  
  if(buttonstate == HIGH) {
  	repeat = 0;
  }  
  
  	
  	if(degreesC>37 || sensorval>700 || repeat == 1)
  	{
      repeat = 1;
      
      tone(buzzer, 800, 800);
      
      servo1.write(0);
      servo2.write(0);
      
      lcd.clear();
      lcd.setCursor(0,0);//row 0 column 0
  	  lcd.print("DANGER!!");
      lcd.setCursor(0,1);//row 1 column 0
      lcd.print("VACATE Building!");
      
      digitalWrite(red_led,HIGH);
      digitalWrite(green_led,LOW);
      
      delay(1000);
      tone(buzzer,600,800);
      digitalWrite(red_led,LOW);
      delay(400);
  	}
  	else{
      servo1.write(90);
      servo2.write(90);
      delay(1000);
      
      digitalWrite(green_led,HIGH);
      digitalWrite(red_led,LOW);
      
      lcd.clear();
  	  lcd.setCursor(0,0);//column 0 row 0
  	  lcd.print("SAFE");
      lcd.setCursor(6,0);//column 6 row 0
      lcd.print(degreesC);
      lcd.print("C");
      lcd.setCursor(0,1);
      lcd.print("Gas Conc.:");
      lcd.print(sensorval);
  }
  
}
float getVoltage(int pin)
{
  
  return (analogRead(pin) * 0.004882814);
}

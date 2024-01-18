#include <Servo.h>

// DC motor
int onOffSwitchPin = 2;
int enablePin = 3;
int input1Pin = 6;
int input2Pin = 5;
int potInputPin = A0;
int lightSensorInputPin = A1;

int onOffSwitchStatus = 0;
int prevOnOffSwitchStatus = 0;
int enabled = 0;
int motorSpeed = 0;
int lightSensorVal = 0;

// Servo motor
Servo myservo;
int servoOutputPin = 11;
int pos = 178;
int servoAtMax = 0;

int tiltSensorPin = 10;

void setup()
{
  Serial.begin(9600);
  
  // DC motor
  pinMode(onOffSwitchPin, INPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(input1Pin, OUTPUT);
  pinMode(input2Pin, OUTPUT);
  
  digitalWrite(enablePin, LOW);
  
  // Servo motor
  myservo.attach(servoOutputPin);
  myservo.write(pos);  

  pinMode(tiltSensorPin, INPUT);
  pinMode(servoOutputPin, OUTPUT);
}

void loop()
{
  // DC motor
  onOffSwitchStatus = digitalRead(onOffSwitchPin);
  delay(5);
  
  motorSpeed = analogRead(potInputPin) / 20;
  delay(5);
  
  lightSensorVal = analogRead(lightSensorInputPin) / 4;
  delay(5);

  if(onOffSwitchStatus != prevOnOffSwitchStatus){
    if(onOffSwitchStatus == HIGH){
      enabled = !enabled;
    }
  }
  
  digitalWrite(input1Pin, LOW);
  digitalWrite(input2Pin, HIGH);
  
  if(enabled == 1 && lightSensorVal > 82){ 
    analogWrite(enablePin, motorSpeed);  
  }else{
    analogWrite(enablePin, 0);
    enabled = 0;
  }
  
  Serial.print("lightSensorVal: ");
  Serial.print(lightSensorVal);

  prevOnOffSwitchStatus = onOffSwitchStatus;
  
  // Servo motor
  if(digitalRead(tiltSensorPin) == LOW && servoAtMax == 0){
    analogWrite(enablePin, 0);  // Emergency stop for DC motor
    enabled = 0;

    for (pos = 180; pos > 10; pos -= 1) {
      myservo.write(pos);        		
      delay(2);              		
    }
    servoAtMax = 1;

  }
  
  Serial.print(", tilt switch: ");
  Serial.print(digitalRead(tiltSensorPin));

  Serial.print(", enabled: ");
  Serial.println(enabled);
}





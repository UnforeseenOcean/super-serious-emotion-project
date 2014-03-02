#include <Wave.h>
#include <Servo.h>      // include the servo library

Servo servoMotor; // creates an instance of the servo object to control a servo
int servoPin = 2; // Control pin for servo motor
int buttonPin = 8;
int buttonState;

int maxangle = 90;
int minangle = 0;
int angle = maxangle;
int anglespeed = -1;
int targetangle = maxangle;

boolean playing = false;

Wave openDelayWave(2000, 1, .01, 2000, 0);
Wave openWave(maxangle, 1, .01, 90, 0);
Wave openSpeedWave(3, 1, .01, 30, 3);

Wave angleWave(80, 1, .1, 10, 70);


void setup() { 
  Serial.begin(9600);       // initialize serial communications
  servoMotor.attach(servoPin);
  servoMotor.write(angle);
  //servoMotor.detach();
  pinMode(buttonPin, INPUT);
} 

void loop() {
  buttonState = digitalRead(buttonPin);
  openAgain();
  if (buttonState == HIGH && playing != true) {
    startPlay();
  }
}

void startPlay() {
  playing = true;
  openAgain();
  //openBoxArtfully();
  //slamBox();
  //playing = false;

}

void closeBox() {
  servoMotor.attach(servoPin);
  while (angle < maxangle) {
    angle += 1;
    moveBox(angle, 30);
  }
  servoMotor.detach();
}

void slamBox() {
  servoMotor.attach(servoPin);
  angle = maxangle;
  moveBox(angle, 30);
}

void openBox() {
  servoMotor.attach(servoPin);
  while (angle > minangle) {
    angle -= 1;
    moveBox(angle, 30);
  }  
  servoMotor.detach();
}

void openBoxArtfully() {
  servoMotor.attach(servoPin);
  while (angle > minangle) {
    targetangle = openWave.wave();
    Serial.println(targetangle);
    
    while (angle > targetangle) {
      angle -= 1;
      moveBox(angle, openSpeedWave.wave());
    }
    slamBox();
    float d = openDelayWave.wave();
    Serial.print("delay:");
    Serial.println(d);
    delay(d);
  }
  servoMotor.detach();
}

void openAgain() {
  angle = angleWave.wave();
  Serial.println(angle);
  moveBox(angle, 10);
  
  if (millis() > 4000) {
    angleWave.a = 30;
  }
}

void moveBox(int angle, int d) {
  servoMotor.write(angle);
  delay(d);
}

//void toggleBox() {
//  if (angle > maxangle || angle < minangle) {
//    anglespeed = anglespeed * -1;
//    delay(1200);
//  }
//  angle += anglespeed;
//  servoMotor.write(angle);
//
//  delay(30);
//
//}







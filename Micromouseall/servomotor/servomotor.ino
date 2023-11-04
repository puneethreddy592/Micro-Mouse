#include <Servo.h>
Servo servo;
int ServoPin=9;


void setup() {
  // put your setup code here, to run once:
  servo.attach(ServoPin);
  servo.write(60);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  while(true){
    servo.write(180);
    Serial.println(180);
    delayMicroseconds(500);
    servo.write(0);
    Serial.println(0);
    delayMicroseconds(1000);
    
  }
}

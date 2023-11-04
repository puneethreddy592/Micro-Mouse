// Define the motor control pins
#define trigl 10
#define echol 12
#define trigr 9
#define echor 8
#define trigf 2
#define echof 7
#define Rm1 4
#define Rm3 5
#define Lm2 6
#define Lm4 3
#define ena 11

void setup() {
  // Set the motor control pins as OUTPUT
  pinMode(Rm1, OUTPUT);
  pinMode(Rm3, OUTPUT);
  pinMode(Lm2, OUTPUT);
  pinMode(Lm4, OUTPUT);
  pinMode(trigl, OUTPUT);
  pinMode(echol, INPUT);
  pinMode(trigr, OUTPUT);
  pinMode(echor, INPUT);
  pinMode(trigf, OUTPUT);
  pinMode(echof, INPUT);

  // Set the motor enable pin as OUTPUT
  pinMode(ena, OUTPUT);

  // Initialize the serial communication
  Serial.begin(9600);
}
int Lside() {
  digitalWrite(trigl, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigl, LOW);
  int t = pulseIn(echol, HIGH);
  int d = t * 0.034 / 2;
  return d;
}

int Fside() {
  digitalWrite(trigf, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigf, LOW);
  int t = pulseIn(echof, HIGH);
  int d = t * 0.034 / 2;
  return d;
}

int Rside() {
  digitalWrite(trigr, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigr, LOW);
  int t = pulseIn(echor, HIGH);
  int d = t * 0.034 / 2;
  return d;
}

void moveForward() {
  int L=0;
  int R=0;
  // while(1)
  // {
  // //int shapee = checkShape();
  // L=Lside();
  // R=Rside();
  // if(R>L){
  //  digitalWrite(Rm1, HIGH);
  //  digitalWrite(Rm3, LOW);
  //  analogWrite(Lm2, 235);
  //  analogWrite(Lm4, 0);
  //  int d =2*(R-L);
  //  d=105-d;
  //  //delay(10);
  //  Serial.print("R");
  //  Serial.println(d);

  //  analogWrite(ena, d);
  // }else if(L>R){
  // digitalWrite(Rm1, HIGH);
  // digitalWrite(Rm3, LOW);
  // analogWrite(Lm2, 235);
  // analogWrite(Lm4, 0);
  // int d=2*(L-R);
  // d=127+d;
  // //delay(10);
  // Serial.print("L");
  // Serial.println(d);
  // analogWrite(ena,d);
  // }else{
   digitalWrite(Rm1, HIGH);
   digitalWrite(Rm3, LOW);
   analogWrite(Lm2, 235);
   analogWrite(Lm4, 0);
   analogWrite(ena, 80);
   
  //}
  // if(shapee !=8 || shapee !=5){
  //   break;
  // }
//}
  // digitalWrite(Rm1, HIGH);
  // digitalWrite(Rm3, LOW);
  // analogWrite(Lm2, 235);
  // analogWrite(Lm4, 0);
  // analogWrite(ena, 120);

}

// void moveForward() {
//   // Set both motors to move forward at full speed
//   digitalWrite(Rm1, HIGH);
//   digitalWrite(Rm3, LOW);
//   digitalWrite(Lm2, HIGH);
//   digitalWrite(Lm4, LOW);

//   // Set the enable pin to control the right motor's speed
//   analogWrite(ena, 127);
// }

void turnRight() {
  // Set motor A to stop
  digitalWrite(Rm1, LOW);
  digitalWrite(Rm3, LOW);

  // Set motor B to move forward (turn right) at full speed
  digitalWrite(Lm2, HIGH);
  digitalWrite(Lm4, LOW);

  // Set the enable pin to control the right motor's speed
  analogWrite(ena, 127);
}

void turnLeft() {
  // Set motor B to stop
  digitalWrite(Lm2, LOW);
  digitalWrite(Lm4, LOW);

  // Set motor A to move forward (turn left) at full speed
  digitalWrite(Rm1, HIGH);
  digitalWrite(Rm3, LOW);

  // Set the enable pin to control the right motor's speed
  analogWrite(ena, 127);
}

void uTurn() {
  // Set both motors to move in opposite directions (U-turn) at full speed
  digitalWrite(Rm1, HIGH);
  digitalWrite(Rm3, LOW);
  digitalWrite(Lm2, LOW);
  digitalWrite(Lm4, HIGH);

  // Set the enable pin to control the right motor's speed
  analogWrite(ena, 118);
}

void stopMotors() {
  // Stop both motors
  digitalWrite(Rm1, LOW);
  digitalWrite(Rm3, LOW);
  digitalWrite(Lm2, LOW);
  digitalWrite(Lm4, LOW);

  // Set the enable pin to turn off the right motor
  analogWrite(ena, 0);
}

void loop() {
  // Move forward for a certain duration
  moveForward();
  delay(3000); // 3 seconds (adjust as needed)

  // Turn right
  // turnRight();
  // delay(950); // 1 second (adjust as needed)

  // // Stop the motors

  // // Move forward for a certain duration
  // moveForward();
  // delay(3000); // 3 seconds (adjust as needed)

  // // Turn left
  // turnLeft();
  // delay(800); // 1 second (adjust as needed)

  // // Stop the motors

  // // Perform a U-turn
  // uTurn();
  // delay(800); // 2 seconds (adjust as needed)

  // // Stop the motors

  // You can add more code or behavior here if needed
}

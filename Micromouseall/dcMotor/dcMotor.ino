
const int motor1EnablePin = 9;  // PWM pin for motor 1 speed control
const int motor1Pin1 = 2;      // Control pin 1 for motor 1
const int motor1Pin2 = 3;      // Control pin 2 for motor 1

// Motor control pins for Motor 2
//const int motor2EnablePin = 10; // PWM pin for motor 2 speed control
const int motor2Pin1 = 4;      // Control pin 1 for motor 2
const int motor2Pin2 = 5;      // Control pin 2 for motor 2

void setup() {
  // Set motor control pins as outputs
  pinMode(motor1EnablePin, OUTPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  
  pinMode(motor2EnablePin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
}

void loop() {
  // Run motor 1 forward and motor 2 backward
  motorControl(motor1EnablePin, 255, HIGH, LOW);  // Motor 1 full speed, forward
  motorControl(motor2EnablePin, 200, LOW, HIGH);  // Motor 2 medium speed, reverse
  delay(2000);

  // Stop both motors
  motorControl(motor1EnablePin, 0, LOW, LOW);     // Motor 1 stop
  motorControl(motor2EnablePin, 0, LOW, LOW);     // Motor 2 stop
  delay(1000);

  // Run motor 1 backward and motor 2 forward
  motorControl(motor1EnablePin, 150, LOW, HIGH);  // Motor 1 medium speed, reverse
  motorControl(motor2EnablePin, 180, HIGH, LOW);  // Motor 2 high speed, forward
  delay(2000);

  // Stop both motors
  motorControl(motor1EnablePin, 0, LOW, LOW);     // Motor 1 stop
  motorControl(motor2EnablePin, 0, LOW, LOW);     // Motor 2 stop
  delay(1000);
}

// Function to control the motor
void motorControl(int enablePin, int speed, int dir1, int dir2) {
  analogWrite(enablePin, speed);  // Set the motor speed using PWM
  digitalWrite(motor1Pin1, dir1); // Set the motor direction
  digitalWrite(motor1Pin2, dir2); // Set the motor direction
}
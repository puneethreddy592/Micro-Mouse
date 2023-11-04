// Motor control pins
#define Rm1 4
#define Rm3 5
#define Lm2 6
#define Lm4 3
#define ena 11

void setup() {
  // Set motor control pins as outputs
  pinMode(Rm1, OUTPUT);
  pinMode(Rm3, OUTPUT);
  pinMode(Lm2, OUTPUT);
  pinMode(Lm4, OUTPUT);
  pinMode(ena, OUTPUT);

  // Initially, stop the motors
  stopMotors();
}

void loop() {
  // Move forward
  moveForward();
  delay(2000);  // Move forward for 2 seconds

  // Stop the motors
  //stopMotors();
  //r();

  // You can add more actions or maneuvers here
}

void moveForward() {
  // Set motor direction to move forward
  digitalWrite(Rm1, HIGH);
  digitalWrite(Rm3, LOW);
  digitalWrite(Lm2, HIGH);
  digitalWrite(Lm4, LOW);

  // Set motor speed using PWM (adjust duty cycle as needed)
  analogWrite(ena, 115);  // Adjust the PWM value (0-255) for motor speed
}

void stopMotors() {
  // Stop the motors by setting all motor pins to LOW
  digitalWrite(Rm1, LOW);
  digitalWrite(Rm3, LOW);
  digitalWrite(Lm2, LOW);
  digitalWrite(Lm4, LOW);
}
void r(){
  digitalWrite(Rm1, HIGH);
  digitalWrite(Rm3, LOW);
  digitalWrite(Lm2, LOW);
  digitalWrite(Lm4, LOW);
  // analogWrite(ena, 127);
  delay(800);
  // Set motor speed using PWM (adjust duty cycle as needed)
  
}
  

//The device works on principle of vector addition and vector space 
#define Rm1 4 //right motor
#define Rm3 5 //right motor
#define Lm2 6 //left motor
#define Lm4 3 //left motor
#define ena 11
#define trigl 10 // Left side ultrasound sensor trigpin
#define echol 12 // Left side ultrasound sensor echopin
#define trigr 9  // Right side ultrasound sensor trigpin
#define echor 8  // Right side ultrasound sensor echopin
#define trigf 2  // Front side ultrasound sensor trigpin
#define echof 7  // Front side ultrasound sensor echopin

void setup() {
  Serial.begin(9600);
  pinMode(trigl, OUTPUT);
  pinMode(echol, INPUT);
  pinMode(trigr, OUTPUT);
  pinMode(echor, INPUT);
  pinMode(trigf, OUTPUT);
  pinMode(echof, INPUT);
}

void loop() {
  // Left sensor
  long durationl, distancel;
  digitalWrite(trigl, LOW);
  delayMicroseconds(2);
  digitalWrite(trigl, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigl, LOW);
  durationl = pulseIn(echol, HIGH);
  distancel = (durationl / 2) / 29.1; // Convert to centimeters

  // Right sensor
  long durationr, distancer;
  digitalWrite(trigr, LOW);
  delayMicroseconds(2);
  digitalWrite(trigr, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigr, LOW);
  durationr = pulseIn(echor, HIGH);
  distancer = (durationr / 2) / 29.1; // Convert to centimeters

  // Front sensor
  long durationf, distancef;
  digitalWrite(trigf, LOW);
  delayMicroseconds(2);
  digitalWrite(trigf, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigf, LOW);
  durationf = pulseIn(echof, HIGH);
  distancef = (durationf / 2) / 29.1; // Convert to centimeters

  Serial.print("Left Distance: ");
  Serial.print(distancel);
  Serial.print(" cm\t");

  Serial.print("Right Distance: ");
  Serial.print(distancer);
  Serial.print(" cm\t");

  Serial.print("Front Distance: ");
  Serial.print(distancef);
  Serial.println(" cm");

  delay(1000); // Delay for one second before the next reading
 
    //analogWrite(Rm1,235);
    //analogWrite(Rm3,0);
    //analogWrite(Lm2,245);
    //analogWrite(Lm4,0);
  
}

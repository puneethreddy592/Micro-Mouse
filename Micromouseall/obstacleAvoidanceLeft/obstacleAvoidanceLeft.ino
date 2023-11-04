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

unsigned long nend, nstart;
void setup() {
  pinMode(trigl, OUTPUT);
  pinMode(echol, INPUT);
  pinMode(trigr, OUTPUT);
  pinMode(echor, INPUT);
  pinMode(trigf, OUTPUT);
  pinMode(echof, INPUT);
  pinMode(Rm1, OUTPUT);
  pinMode(Rm3, OUTPUT);
  pinMode(Lm2, OUTPUT);
  pinMode(Lm4, OUTPUT);
  pinMode(ena, OUTPUT);

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

int checkShape() {
  int leftDist = Lside();
  int rightDist = Rside();
  int frontDist = Fside();
  Serial.print("Left Distance: ");
  Serial.print(leftDist);
  Serial.print(" cm\t");

  Serial.print("Right Distance: ");
  Serial.print(rightDist);
  Serial.print(" cm\t");

  Serial.print("Front Distance: ");
  Serial.print(frontDist);
  Serial.println(" cm");

  if (leftDist > 15 && rightDist > 15 && frontDist > 10) {
    Serial.println("Rev T shape");
    return 1;
  } else if (leftDist > 15 && rightDist > 15 && frontDist <= 10) {
    Serial.println("T shape");
    return 2;
  } else if (leftDist < 15 && rightDist > 15 && frontDist <= 10) {
    Serial.println("JR shape");
    return 3;
  } else if (leftDist > 15 && rightDist < 15 && frontDist <= 10) {
    Serial.println("JL shape");
    return 4;
  } else if (leftDist > 15 && rightDist < 15 && frontDist > 10) {
    Serial.println("FL shape");
    return 5;
  } else if (leftDist < 15 && rightDist > 15 && frontDist > 10) {
    Serial.println("FR shape");
    return 6;
  } else if (leftDist < 15 && rightDist < 15 && frontDist < 4) {
    Serial.println("UT shape");
    return 7;
  } else {
    Serial.println("Forward");
    return 8;
  }
}

void moveForward() {
  int L=0;
  int R=0;
  while(1)
  {
  int shapee = checkShape();
  L=Lside();
  R=Rside();
  if(((R>3)&&(R<6))||((L<6)&&(3<L))){
   digitalWrite(Rm1, HIGH);
   digitalWrite(Rm3, LOW);
   analogWrite(Lm2, 235);
   analogWrite(Lm4, 0);
   analogWrite(ena, 80);
   delay(100);
   
  }
  else if(R>L){
   digitalWrite(Rm1, HIGH);
   digitalWrite(Rm3, LOW);
   analogWrite(Lm2, 235);
   analogWrite(Lm4, 0);
   int d =2*(R-L);
   d=105-d;
   //delay(10);
   Serial.print("R");
   Serial.println(d);

   analogWrite(ena, d);
  }else if(L>R){
  digitalWrite(Rm1, HIGH);
  digitalWrite(Rm3, LOW);
  analogWrite(Lm2, 235);
  analogWrite(Lm4, 0);
  int d=2*(L-R);
  d=127+d;
  //delay(10);
  Serial.print("L");
  Serial.println(d);
  analogWrite(ena,d);
  }else{digitalWrite(Rm1, HIGH);
   digitalWrite(Rm3, LOW);
   analogWrite(Lm2, 235);
   analogWrite(Lm4, 0);
   analogWrite(ena, 80);
  }
  if(shapee !=8 || shapee !=5){
    break;
  }
  
}
}
void justmovefwd(){
  digitalWrite(Rm1, HIGH);
  digitalWrite(Rm3, LOW);
  analogWrite(Lm2, 235);
  analogWrite(Lm4, 0);
  analogWrite(ena, 80);
}
void tr(){
  nstart=millis();
  nend=millis();
  while((nend-nstart)<=1025)
{
  digitalWrite(Rm1,LOW);
  digitalWrite(Rm3,LOW);
  analogWrite(Lm2,235);
  analogWrite(Lm4,0);
  nend=millis();
}
}
void tl(){
  nstart=millis();
  nend=millis();
  while((nend-nstart)<=800)
 {
  digitalWrite(Rm1,HIGH);
  digitalWrite(Rm3,LOW);
  digitalWrite(Lm2,LOW);
  digitalWrite(Lm4,LOW);
  nend=millis();
 }
}
void ut()// U turn
{
  nstart=millis();
nend=millis();
while((nend-nstart)<=850)
{
  digitalWrite(Rm1,HIGH);
  digitalWrite(Rm3,LOW);
  analogWrite(Lm2,0);                            
  analogWrite(Lm4,235);
  nend=millis();
}
}
void moveback(){
  digitalWrite(Rm1,LOW);
  digitalWrite(Rm3,HIGH);
  digitalWrite(Lm2,LOW);
  digitalWrite(Lm4,HIGH);
  analogWrite(ena, 120);
}
void utr() {
  int ld = 0;
  int rd = 0;
  int x = 1;

  while (x) {
    Serial.println("utr 1");

    // Read sensor values for the left and right sides
    ld = Lside();
    rd = Rside();

    if (ld < 15 || rd < 15) {
      if(rd>ld){
      digitalWrite(Rm1, LOW);  // Reverse right motor
      digitalWrite(Rm3, HIGH); // Reverse left motor
      digitalWrite(Lm2, LOW);
      digitalWrite(Lm4, HIGH);

      // Adjust the motor speed based on the sensor readings
      int d = 2*(rd - ld);  // Speed adjustment based on the difference
      d=127-d;
      analogWrite(ena, 127) ;  // You can adjust the speed control here
      }else{
       int d = (ld- rd);  
       d=d+127;
        analogWrite(ena, 127 );  
        delay(150);
      }
      Serial.println("utr 2");
    } else {
      // If both sensor readings are greater than or equal to 15, exit the loop
      x = 0;
      Serial.println("utr 3");
    }
  }

  // Stop the motors
  stopMotors();

  // Set motor control pins for a brief delay while moving backward
  digitalWrite(Rm1, LOW);  // Reverse right motor
  digitalWrite(Rm3, HIGH); // Reverse left motor
  digitalWrite(Lm2, LOW);
  digitalWrite(Lm4, HIGH);

  analogWrite(ena, 127 );  
  delay(150);
  

  // Stop the motors again
  stopMotors();

  // Decide whether to turn right or left based on the 'rd' value
  if (rd > 15) {
    turnRight();
  } else {
    turnLeft();
  }
}

void turnRight() {
  tr();
  while(((nend-nstart)/1000)<=0.5)
{
  digitalWrite(Rm1,HIGH);
  digitalWrite(Rm3,LOW);
  digitalWrite(Lm2,HIGH);
  digitalWrite(Lm4,LOW);
  analogWrite(ena, 120);
  nend=millis();
}
 //movebackforturn();
 moveback();
 delay(220);
}

void turnLeft() {
  tl();
  while(((nend-nstart)/1000)<=0.5)
{
  digitalWrite(Rm1,HIGH);
  digitalWrite(Rm3,LOW);
  digitalWrite(Lm2,HIGH);
  digitalWrite(Lm4,LOW);
  analogWrite(ena, 120);
  nend=millis();
}
 //movebackforturn();
 moveback();
 delay(220);
}
void uTurn() {
  ut();
  while(((nend-nstart)/1000)<=0.5)
{
  digitalWrite(Rm1,HIGH);
  digitalWrite(Rm3,LOW);
  digitalWrite(Lm2,HIGH);
  digitalWrite(Lm4,LOW);
  analogWrite(ena, 120);
  nend=millis();
}
}
void stopMotors() {
  // Stop the motors by setting all motor pins to LOW
  digitalWrite(Rm1, LOW);
  digitalWrite(Rm3, LOW);
  digitalWrite(Lm2, LOW);
  digitalWrite(Lm4, LOW);
}
void movebackforturn(){
  digitalWrite(Rm1,LOW);
  digitalWrite(Rm3,HIGH);
  digitalWrite(Lm2,LOW);
  digitalWrite(Lm4,HIGH);
  analogWrite(ena, 120);
  delay(150);

}

void loop() {
  int shape = checkShape();
  int L=0;
  if (shape == 8 || shape == 6) {
    stopMotors();
    moveForward();
  } else if (shape == 3) {
    stopMotors();
    delay(500);
    moveForward();
    delay(100);
    turnRight();
  } else if(shape ==1 || shape == 2 || shape == 5 || shape == 4){
    
    stopMotors();
    delay(500);
    moveForward();
    delay(100);
    int x=1;
    while(x){
    L=Lside();
    if(L<38&& L>30){
    justmovefwd();
    }else{turnLeft();
    x=0;
    }}
  }else {
    Serial.println("utr");
    stopMotors();
    delay(100);
    utr();
    
  } 

}

// Pin definitions
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

// Variables to store timing
unsigned long nend, nstart;

void setup() {
  // Pin mode setup
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

  // Initialize serial communication
  Serial.begin(9600);
}

// Function to measure distance on the left side
int Lside() {
  digitalWrite(trigl, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigl, LOW);
  int t = pulseIn(echol, HIGH);
  int d = t * 0.034 / 2;
  return d;
}

// Function to measure distance in the front
int Fside() {
  digitalWrite(trigf, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigf, LOW);
  int t = pulseIn(echof, HIGH);
  int d = t * 0.034 / 2;
  return d;
}

// Function to measure distance on the right side
int Rside() {
  digitalWrite(trigr, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigr, LOW);
  int t = pulseIn(echor, HIGH);
  int d = t * 0.034 / 2;
  return d;
}

// Function to determine shape based on distances
int shape() {
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

// Function to print distance values
void tellval() {
  int l = Lside();
  int r = Rside();
  int f = Fside();
  Serial.print("Left: ");
  Serial.print(l);
  Serial.print(" cm, Right: ");
  Serial.print(r);
  Serial.print(" cm, Front: ");
  Serial.print(f);
  Serial.println(" cm");
}

// Function to determine and print direction
void telldir() {
  int l = Lside();
  int r = Rside();
  if (l > r) {
    Serial.println("Turn left");
  } else if (r > l) {
    Serial.println("Turn right");
  } else {
    Serial.println("Go straight");
  }
}

// Function to move forward
void fwd() {
  digitalWrite(Rm1, HIGH);
  digitalWrite(Rm3, LOW);
  analogWrite(Lm2, 235);
  analogWrite(Lm4, 0);
  analogWrite(ena, 80);
}

// Function to make a right turn
void Tr() {
  nstart = millis();
  nend = millis();
  while ((nend - nstart) <= 1025) {
    digitalWrite(Rm1, LOW);
    digitalWrite(Rm3, LOW);
    analogWrite(Lm2, 235);
    analogWrite(Lm4, 0);
    nend = millis();
  }
}

// Function to make a left turn
void Tl() {
  nstart = millis();
  nend = millis();
  while ((nend - nstart) <= 800) {
    digitalWrite(Rm1, HIGH);
    digitalWrite(Rm3, LOW);
    digitalWrite(Lm2, LOW);
    digitalWrite(Lm4, LOW);
    nend = millis();
  }
}

// Function to make a U-turn
void uT() {
  nstart = millis();
  nend = millis();
  while ((nend - nstart) <= 850) {
    digitalWrite(Rm1, HIGH);
    digitalWrite(Rm3, LOW);
    analogWrite(Lm2, 0);
    analogWrite(Lm4, 235);
    nend = millis();
  }
}

// Function to stop the motors
void stop() {
  digitalWrite(Rm1, LOW);
  digitalWrite(Rm3, LOW);
  digitalWrite(Lm2, LOW);
  digitalWrite(Lm4, LOW);
}

// Function to change the value of v1 to v2
void valchange(int &v1, int v2) {
  v1 = v2;
}

// Function to make a right turn
void TurnR() {
  Tr();
  while (((nend - nstart) / 1000) <= 0.5) {
    digitalWrite(Rm1, HIGH);
    digitalWrite(Rm3, LOW);
    digitalWrite(Lm2, HIGH);
    digitalWrite(Lm4, LOW);
    analogWrite(ena, 120);
    nend = millis();
  }
  moveback();
  delay(220);
}

// Function to make a left turn
void TurnL() {
  Tl();
  while (((nend - nstart) / 1000) <= 0.5) {
    digitalWrite(Rm1, HIGH);
    digitalWrite(Rm3, LOW);
    digitalWrite(Lm2, HIGH);
    digitalWrite(Lm4, LOW);
    analogWrite(ena, 120);
    nend = millis();
  }
  moveback();
  delay(220);
}

// Function to make a U-turn
void TurnU() {
  uT();
  while (((nend - nstart) / 1000) <= 0.5) {
    digitalWrite(Rm1, HIGH);
    digitalWrite(Rm3, LOW);
    digitalWrite(Lm2, HIGH);
    digitalWrite(Lm4, LOW);
    analogWrite(ena, 120);
    nend = millis();
  }
}

// Function to move the robot backward
void moveback() {
  digitalWrite(Rm1, LOW);
  digitalWrite(Rm3, HIGH);
  digitalWrite(Lm2, LOW);
  digitalWrite(Lm4, HIGH);
  analogWrite(ena, 120);
}

// Function to return the remainder of val divided by 10
int modval(int val) {
  return val % 10;
}

// Function to return the absolute value of val
int absval(int val) {
  return abs(val);
}

// Function to move the robot in a direction except the specified one
void moveExcept(char dir) {
  if (dir == 'L') {
    TurnR();
  } else if (dir == 'R') {
    TurnL();
  } else {
    TurnU();
  }
}

// Function to find the direction the robot should go based on sensor readings
char finddir() {
  int l = Lside();
  int r = Rside();
  int f = Fside();
  if (f < 10) {
    if (l > r) {
      return 'L';
    } else {
      return 'R';
    }
  }
  return 'F';
}

// Function to guess the direction based on side sensor readings
char guessdir() {
  int l = Lside();
  int r = Rside();
  if (l > r) {
    return 'L';
  } else {
    return 'R';
  }
}

// Function to follow the determined direction
void follow() {
  while (true) {
    char dir = finddir();
    if (dir == 'F') {
      fwd();
    } else {
      moveExcept(dir);
    }
    delay(100);
  }
}

// Function to print loop values of left and right side sensors
void loopval() {
  int l = Lside();
  int r = Rside();
  Serial.print("Loop Left: ");
  Serial.print(l);
  Serial.print(" cm, Right: ");
  Serial.print(r);
  Serial.println(" cm");
}

void loop() {
  int shape = shape();
  int L = 0;
  if (shape == 8 || shape == 6) {
    stop();
    fwd();
  } else if (shape == 3) {
    stop();
    delay(500);
    fwd();
    delay(100);
    TurnR();
  } else if (shape == 1 || shape == 2 || shape == 5 || shape == 4) {
    stop();
    delay(500);
    fwd();
    delay(100);
    int x = 1;
    while (x) {
      L = Lside();
      if (L < 38 && L > 30) {
        fwd();
      } else {
        TurnL();
        x = 0;
      }
    }
  } else {
    Serial.println("TurnU");
    stop();
    delay(100);
    TurnU();
  }
}

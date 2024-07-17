<div align="center">
  <h1>Micro Mouse ( Maze solver )</h1>
</div>

### 📝 CODE EXPLANATION

<b> Definitions and Global Variables </b>

```cpp
#define Rm1 4 //right motor
#define Rm3 5 //right motor
#define Lm2 6 //left motor
#define Lm4 3 //left motor
#define trigl 10 //left side ultrasound sensor trigpin
#define echol 11 //left side ultrasound sensor echopin
#define trigr 9 //right side ultrasound sensor trigpin
#define echor 8 //right side ultrasound sensor echopin
#define trigf 2 //front side ultrasound sensor trigpin
#define echof 7 //front side ultrasound sensor echopin

int t, d, L = 10, R = 10, F = 8, z = 4, fwdl[50], indpt[50], ind = 0, sumval = 0, ci = 0, cj = 0, cindpt = 0, looper = 0, y, f = 4, g = 1;
/* 
t=time, d=distance , L=max left side distance,R=max right side distance,F=max front side distance, 
fwdl = distance moved , indpt note the lattice points where there were more than 1 path, 
ind is index of each stack ci,cj gives the count of i cap and j cap, 
cindpt = to count number of cind, looper to report the kind of loop,z variable changes on turning and accounts for direction of movement 
*/
char dir[50]; // to note the direction
unsigned long nend, nstart; // start and end time for turning

```

* This block defines constants for pin numbers and initializes global variables used throughout the program.
* t, d, L, R, F, z are variables for time, distance, and various distance thresholds.
* Arrays fwdl[] and indpt[] store distances and lattice points respectively.
* dir[] stores directions, and nstart, nend are used to measure time.
* Pins for motors and ultrasound sensors are defined.
<b> Ultrasound Sensor Functions </b>

```cpp
int Lside() {
  digitalWrite(trigl, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigl, LOW);
  t = pulseIn(echol, HIGH);
  d = t * 0.034 / 2;
  return d;
}

int Fside() {
  digitalWrite(trigf, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigf, LOW);
  t = pulseIn(echof, HIGH);
  d = t * 0.034 / 2;
  return d;
}

int Rside() {
  digitalWrite(trigr, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigr, LOW);
  t = pulseIn(echor, HIGH);
  d = t * 0.034 / 2;
  return d;
}

```
* These functions use ultrasound sensors to measure distances in three directions (left, front, right).
* They trigger the sensor, calculate the distance based on the time taken for the pulse, and return the distance in centimeters.

<b> Shape Recognition and Movement Functions </b>

```cpp
int shape() // returns the type of shape 
{
  if (Lside() > L && Rside() > R && Fside() > F) {
    Serial.println("Rev T shape");
    return 1;
  } else if (Lside() > L && Rside() > R && Fside() < F) {
    Serial.println("T shape");
    return 2;
  } else if (Lside() < L && Rside() > R && Fside() < F) {
    Serial.println("JR shape");
    return 3;
  } else if (Lside() > L && Rside() < R && Fside() < F) {
    Serial.println("JL shape");
    return 4;
  } else if (Lside() > L && Rside() < R && Fside() > F) {
    Serial.println("FL shape");
    return 5;
  } else if (Lside() < L && Rside() > R && Fside() > F) {
    Serial.println("FR shape");
    return 6;
  } else if (Lside() < L && Rside() < R && Fside() < F) {
    Serial.println("UT shape");
    return 7;
  } else {
    Serial.println("forward");
    return 8;
  }
}

int tellval(int a) // this function returns magnitude of movement, positive if i cap, j cap and negative -i cap, -j cap
{
  if (z == 4) {
    return a;
  } else if (z == 1) {
    return a;
  } else if (z == 2) {
    return -1 * a;
  } else if (z == 3) {
    return -1 * a;
  }
}

char telldir(int b) // depending on value of z it gives the direction
{
  if (b == 4) {
    return 'j';
  }
  if (b == 1) {
    return 'i';
  }
  if (b == 2) {
    return 'j';
  }
  if (b == 3) {
    return 'i';
  }
}

void fwd() // amount of forward movement
{
  nstart = millis();
  while (shape() == 8) {
    digitalWrite(Rm1, HIGH);
    digitalWrite(Rm3, LOW);
    analogWrite(Lm2, 235);
    analogWrite(Lm4, 0);
  }
  nend = millis();
  fwdl[ind] += tellval((nend - nstart) / 1000);
  dir[ind] = telldir(z);
}

void Tr() // right turn
{
  nstart = millis();
  nend = millis();
  while (((nend - nstart) / 1000) <= 0.15) {
    digitalWrite(Rm1, LOW);
    digitalWrite(Rm3, LOW);
    analogWrite(Lm2, 235);
    analogWrite(Lm4, 0);
    nend = millis();
  }
}

void Tl() // left turn
{
  nstart = millis();
  nend = millis();
  while (((nend - nstart) / 1000) <= 0.15) {
    digitalWrite(Rm1, HIGH);
    digitalWrite(Rm3, LOW);
    digitalWrite(Lm2, LOW);
    digitalWrite(Lm4, LOW);
    nend = millis();
  }
}

void uT() // U turn
{
  nstart = millis();
  nend = millis();
  while (((nend - nstart) / 1000) <= 0.15) {
    digitalWrite(Rm1, HIGH);
    digitalWrite(Rm3, LOW);
    analogWrite(Lm2, 0);
    analogWrite(Lm4, 235);
    nend = millis();
  }
}

void stop() // stops the device
{
  digitalWrite(Rm1, LOW);
  digitalWrite(Rm3, LOW);
  digitalWrite(Lm2, LOW);
  digitalWrite(Lm4, LOW);
}
```
* shape() determines the current shape based on sensor readings.
* tellval() and telldir() determine movement magnitude and direction based on z.
* fwd(), Tr(), Tl(), uT(), stop() perform forward movement, right turn, left turn, U-turn, and stop respectively.

<b> Turn and Loop Handling Functions </b>

```cpp
int valchange(int val) // since z++ in case of right turn and z-- in case of left turn and z-2 in case of u turn, 
{
  if (val > 4) {
    return 1;
  } else if (val < 1) {
    return 4;
  } else {
    return val;
  }
}

void TurnR() // along with right turn it moves for a time till both sides are obstructed, so it can sense the 1 cm thick wall or more
{
  ind++;
  Tr();
  z++;
  z = valchange(z);
  while (((nend - nstart) / 1000) <= 0.5) {
    digitalWrite(Rm1, HIGH);
    digitalWrite(Rm3, LOW);
    digitalWrite(Lm2, HIGH);
    digitalWrite(Lm4, LOW);
    nend = millis();
  }
}

void TurnL() // along with left turn it moves for a time till both sides are obstructed, so it can sense the 1 cm thick wall or more
{
  ind++;
  Tl();
  z--;
  z = valchange(z);
  while (((nend - nstart) / 1000) <= 0.5) {
    digitalWrite(Rm1, HIGH);
    digitalWrite(Rm3, LOW);
    digitalWrite(Lm2, HIGH);
    digitalWrite(Lm4, LOW);
    nend = millis();
  }
}

void TurnU() // along with U turn it moves for a time till both sides are obstructed, so it can sense the 1 cm thick wall or more
{
  ind++;
  uT();
  z = z - 2;
  z = valchange(z);
  while (((nend - nstart) / 1000) <= 0.5) {
    digitalWrite(Rm1, HIGH);
    digitalWrite(Rm3, LOW);
    digitalWrite(Lm2, HIGH);
    digitalWrite(Lm4, LOW);
    nend = millis();
  }
}

int loopval() // it returns the type of loop, 1st type if without opening and 2nd type with opening in between
{
  for (int x = ind; x >= 0; x--) {
    sumval += fwdl[x]; // vector addition in stack format from last cell
    if (sumval <= 5) { // allowance of error of 5 cm
      for (int y = ind; y >= x; y--) {
        if (dir[ind] == 'i') {
          ci += 1;
        } else {
          cj += 1;
        }
      }
      if (ci == cj) { // check same directions in loop
        for (y = ind; y >= x; y--) {
          if (indpt[y] > 0) {
            cindpt += 1;
          }
        }
        if (cindpt > 1) { // if more than 1 lattice point than it is 2nd kind
          return 2;
        } else {
          return 1;
        }
      }
    }
  }
  return 0;
}

int modval(int m) // returns absolute value
{
  if (m < 0) {
    return -1 * m;
  } else {
    return m;
  }
}

int absval(int val) // returns absolute value
{
  if (val < 0) {
    return -1 * val;
  } else {
    return val;
  }
}

```

* TurnR(), TurnL(), TurnU() execute turns and measure distance moved during turns.
* loopval(), modval(), absval() handle loop detection and absolute value calculations.

<b> Path Following Functions </b>

```cpp
void moveExcept() // it moves except returning back from where it has come
{
  if (shape() == 3) {
    TurnR();
    fwd();
  }
  while (shape() == 4) {
    TurnL();
    fwd();
  }
  while (shape() == 2 || shape() == 6) {
    TurnL();
    fwd();
  }
}

void finddir() // finds the next direction
{
  if (shape() == 1) {
    TurnR();
    fwd();
  }
  while (shape() == 5) {
    TurnR();
    fwd();
  }
  while (shape() == 8) {
    fwd();
  }
  if (shape() == 7) {
    TurnU();
    fwd();
  }
}

void guessdir() // guessing direction in case of no particular shape
{
  if (Fside() > F) {
    fwd();
  }
  if (Lside() > L) {
    TurnL();
    fwd();
  } else {
    TurnR();
    fwd();
  }
}

void follow() // overall follow path
{
  while (shape() == 1 || shape() == 5) {
    TurnR();
    fwd();
  }
  while (shape() == 3) {
    TurnR();
    fwd();
  }
  while (shape() == 4) {
    TurnL();
    fwd();
  }
  while (shape() == 2 || shape() == 6) {
    TurnL();
    fwd();
  }
  while (shape() == 8) {
    fwd();
  }
  if (shape() == 7) {
    TurnU();
    fwd();
  }
  if (loopval() == 1 || loopval() == 2) {
    stop();
  }
}

```

* moveExcept(), finddir(), guessdir(), follow() implement specific path following behaviors based on current shape and conditions.

<b> Setup and Loop Functions </b>

```cpp
void setup() {
  Serial.begin(9600);
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
}

void loop() {
  follow();
}
```
* setup() initializes pins for sensors and motors and starts serial communication.
* loop() is the main execution loop where the robot continuously follows the defined path.

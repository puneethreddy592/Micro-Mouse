int trigger_pin = 10;

int echo_pin = 11; 

int time;

int distance; 

void setup() {
   
  pinMode (trigger_pin, OUTPUT); 
  pinMode (echo_pin, INPUT);
  Serial.begin (9600);

}

void loop ( ) {

    digitalWrite (trigger_pin, LOW);

    delayMicroseconds (2); 

    digitalWrite (trigger_pin, HIGH);

    delayMicroseconds (10);

    digitalWrite (trigger_pin, LOW);

    pinMode(echo_pin, INPUT);

    time = pulseIn (echo_pin, HIGH);

    distance = time/58;

    Serial.println(distance);
    delay(1000);
}

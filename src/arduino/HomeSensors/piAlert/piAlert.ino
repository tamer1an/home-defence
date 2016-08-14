/* Pi PC */
#define piPin 6                 // PI PC

/* Sound Buzzer */
#define buzzerPin 12            // BUZZER

/* PIR sensor */
#define inputPin  2             // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

/* US sensor */
#define echoPin 7               // Echo Pin
#define trigPin 8               // Trigger Pin
int maximumRange = 200;         // Maximum range needed
int minimumRange = 0;           // Minimum range needed
long duration, distance;        // Duration used to calculate distance

void setup() {
  //Serial.begin (9600); ///////////////

  /* Pi PC */
  pinMode(piPin, OUTPUT); 

  /* Sound Buzzer */
  pinMode(buzzerPin, OUTPUT);

  /* US sensor */
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  /* PIR sensor */
  pinMode(inputPin, INPUT);  
  
  //delay(30000); //30seconds delay before start
}

void motionDetect(){
    // PIR SENSOR
  val = digitalRead(inputPin); 
  if (val == HIGH) {            
    if (pirState == LOW) {
      pirState = HIGH;
      digitalWrite(piPin, HIGH);
    }
  } else {
    if (pirState == HIGH) {
      pirState = LOW;
      digitalWrite(piPin, LOW);
    }
  }
}

void ultraSonic(){ 
  /*  UltraSonic Sensor */
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;

  if (distance >= maximumRange || distance <= minimumRange) {
    digitalWrite(piPin, LOW);
  } else {  
    digitalWrite(piPin, HIGH);  
  }
}

void loop() {
  ultraSonic();
  motionDetect();

  delay(50);
}

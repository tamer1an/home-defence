#include <IRremote.h>

/* LOGIC SWITCH */
int POWER = 1;

/* IR remote Sensor */
int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

/* RGB LED */
const int RED_PIN = 4;
//const int GREEN_PIN = 13;
const int BLUE_PIN = 10;

/* Define hardware connections Sound Sensor */
#define PIN_GATE_IN 3
#define IRQ_GATE_IN  0
#define PIN_ANALOG_IN A0

/* Pi PC */
#define piPin 6                 // PI PC

/* Sound Buzzer */
#define buzzerPin 12            // BUZZER

/* PIR sensor */
#define inputPin  9             // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int PIRval = 0;                    // variable for reading the pin status

/* US sensor */
#define echoPin 7               // Echo Pin
#define trigPin 8               // Trigger Pin
int maximumRange = 200;         // Maximum range needed
int minimumRange = 0;           // Minimum range needed
long duration, distance;        // Duration used to calculate distance


/* PIR SENSOR */
void motionDetect() {
  PIRval = digitalRead(inputPin);
  if (PIRval == HIGH) {
    if (pirState == LOW) {
      pirState = HIGH;
//      Serial.println("MOTION start");
      alarm();
    }
  } else {
    if (pirState == HIGH) {
//      Serial.println("MOTION end");
      pirState = LOW;
    }
  }
}


/*  UltraSonic Sensor */
void ultraSonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;

  if (distance >= maximumRange || distance <= minimumRange) {
//    Serial.println("US = -1");
//    digitalWrite(piPin, LOW);
  } else {
    if (distance > 3 && distance < 150) {
//      Serial.println("US");
        alarm();
    } else {
      
    }
  }
}

void alarm() {
//  Serial.println("ALARM 1");
  digitalWrite(piPin, HIGH);
  delay(2000);
  digitalWrite(piPin, LOW);
}

void setup() {
//  Serial.begin(9600);
//  Serial.flush();

  pinMode(RED_PIN, OUTPUT);
  //  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  /* configure input to interrupt sound sensor */
  pinMode(PIN_GATE_IN, INPUT);
  attachInterrupt(IRQ_GATE_IN, soundISR, CHANGE);

  /* Pi PC */
  pinMode(piPin, OUTPUT);

  /* Sound Buzzer */
  pinMode(buzzerPin, OUTPUT);

  /* US sensor */
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  /* PIR sensor */
  pinMode(inputPin, INPUT);

  /* IR Remote */
  irrecv.enableIRIn(); // Start the receiver

  delay(1000);
}


void soundISR() {
    if (POWER == 1){
//      Serial.println("SOUND");
      alarm();
    }     
}


void remote() {
  if (irrecv.decode(&results)) {
//    Serial.println(results.value);

    if (results.value == 16580863 && POWER == 1) {
      POWER = 0;
      digitalWrite(BLUE_PIN, LOW);
    } else if (results.value == 16580863) {
      POWER = 1;
      digitalWrite(RED_PIN, LOW);
    }
    irrecv.resume(); // Receive the next value
  }
}


void loop() {
  remote();
//  Serial.print("POWER ");
//  Serial.println(POWER);

  if (POWER) {
    digitalWrite(BLUE_PIN, HIGH);
    ultraSonic();
    motionDetect();
  } else {
    digitalWrite(RED_PIN, HIGH);
  }

  delay(100);
}


/*
 * 1
FFA25D
2
FF629D
3
FFE21D
4
FF22DD
5
FF02FD
6
FFC23D
7
FFE01F
8
FFA857
9
FF906F
10
FF6897
11
FF9867
12
FFB04F
13
FF30CF
14
FF18E7
15
FF7A85
16
FF10EF
17
FF38C7
18
FF5AA5
19
FF42BD
20
FF4AB5
21
FF52AD
 */

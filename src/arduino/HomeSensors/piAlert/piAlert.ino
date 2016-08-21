#include <IRremote.h>

/* LOGIC SWITCH */
int POWER = 1;
int POWER_US = 0;
int currentLed;

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
      Serial.println("MOTION start");
      alarm();
    }
  } else {
    if (pirState == HIGH) {
      Serial.println("MOTION end");
      pirState = LOW;
    }
  }
}


/*  UltraSonic Sensor */
void ultraSonic() {

  if (!POWER_US ){
    return;
  }
  
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
    if (distance > 3 && distance < 100) {
      Serial.println("US");
        alarm();
    } else {
      
    }
  }
}

void alarm() {
  Serial.println("ALARM 1");
  digitalWrite(piPin, HIGH);
  delay(2000);
  digitalWrite(piPin, LOW);
}

void setup() {
  Serial.begin(9600);
  Serial.flush();

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

  currentLed = BLUE_PIN;
}


void soundISR() {
    if (POWER == 1){
      Serial.println("SOUND");
//      alarm();


//      digitalWrite(piPin, HIGH);
//      delay(2000);
//      digitalWrite(piPin, LOW);

      
    }     
}


void remote() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value);

    if (results.value == 16580863 && POWER == 1) {
      POWER = 0;
      currentLed = BLUE_PIN;
    } else if (results.value == 16580863) {
      POWER = 1;
      currentLed = RED_PIN;    
    }

    if (results.value == 16593103 && POWER_US == 1) {
      POWER_US = 0;
    } else if (results.value == 16593103) {
      POWER_US = 1;   
    }
    
    digitalWrite(currentLed, LOW);       
    irrecv.resume(); // Receive the next value
  }
}


void loop() {
  remote();

  if (POWER) {
    currentLed = BLUE_PIN;
    ultraSonic();
    motionDetect();
  } else {
    currentLed = RED_PIN;    
  }
  
  digitalWrite(currentLed, HIGH);  

  if (!POWER_US){
    digitalWrite(currentLed, LOW);  
    delay(200);
    digitalWrite(currentLed, HIGH);  
  }
  
  delay(100);
}

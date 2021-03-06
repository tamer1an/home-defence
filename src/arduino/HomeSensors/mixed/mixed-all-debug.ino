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
void motionDetect(){
  PIRval = digitalRead(inputPin); 
  if (PIRval == HIGH) {            
    if (pirState == LOW) {
      pirState = HIGH;
      digitalWrite(piPin, HIGH);
      Serial.println(" motion ");
    }
  } else {
    if (pirState == HIGH) {
      pirState = LOW;
      
      Serial.println(" no motion ");
      digitalWrite(piPin, LOW);
    }
  }
}


/*  UltraSonic Sensor */
void ultraSonic(){ 

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;

  if (distance >= maximumRange || distance <= minimumRange) {
//    Serial.println("-1");
//    digitalWrite(ledPin, HIGH);
  } else {

    /* Send the distance to the computer using Serial protocol, and
      turn LED OFF to indicate successful reading. */
    Serial.println(distance);

    if(distance > 3 && distance < 90){
//      tone(buzzerPin, 349, 200); //{262, 294, 330, 349, 392, 440, 494, 523};
//      analogWrite(buzzerPin, 240);
    } else {
//      noTone(buzzerPin);
//      analogWrite(buzzerPin, 0);
    }      
 }
 
}


void setup() {
  Serial.begin(9600);
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

  //delay(7000);
}


void soundISR(){
  if(digitalRead(PIN_GATE_IN) == 1){
    digitalWrite(RED_PIN, "HIGH"); 
//    digitalWrite(piPin, "HIGH"); 
      Serial.println("gate : 1");   
  } else {
//    digitalWrite(piPin, HIGH); 
      Serial.println("gate : 0");
  }
  digitalWrite(piPin, HIGH); 
}


void remote(){
  if (irrecv.decode(&results)) {
//    Serial.println(results.value);
    
    if (results.value == 16580863 && POWER == 1){
      POWER = 0;
      digitalWrite(BLUE_PIN, LOW); 
    } else {
      POWER = 1;
      digitalWrite(RED_PIN, LOW); 
    }    
     irrecv.resume(); // Receive the next value
  }
}


void loop(){
  remote();
  
  if (POWER) {
    //Serial.println("ON");
    digitalWrite(BLUE_PIN, HIGH); 
    ultraSonic();
    motionDetect();
  } else {
    //Serial.println("OFF");
    digitalWrite(RED_PIN, HIGH); 
  }
  
  delay(30);
}

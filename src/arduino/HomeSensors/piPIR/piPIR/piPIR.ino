/* PIR sensor */
#define inputPin  2             // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int PIRval = 0;                    // variable for reading the pin status
#define piPin 7  

void setup() {
  Serial.begin(9600);
  Serial.flush();

  /* PIR sensor */
  pinMode(inputPin, INPUT);
}

void alarm() {
  Serial.println("ALARM 1");
  digitalWrite(piPin, HIGH);
  delay(2000);
  digitalWrite(piPin, LOW);
}

void loop() {
  PIRval = digitalRead(inputPin);
  if (PIRval == HIGH) {
    if (pirState == LOW) {
      pirState = HIGH;
      Serial.println("MOTION start");
      digitalWrite(piPin, HIGH); 
//      digitalWrite(piPin, LOW);
    } else {
//      digitalWrite(piPin, LOW);
//      Serial.println("MOTION start pirstate == HIGH");
    }
  } else {
    if (pirState == HIGH) {
      Serial.println("MOTION end");
      pirState = LOW;
      digitalWrite(piPin, LOW);
    } else {
      digitalWrite(piPin, LOW);
//      Serial.println("MOTION start pirstate == LOW");
    }
  }
  delay(10);
}

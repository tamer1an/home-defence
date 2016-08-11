//int soundDetectedPin = 10;    // Use Pin 10 as our Input
//int soundDetectedVal = HIGH; // This is where we record our Sound Measurement
//boolean bAlarm = false;
//
//unsigned long lastSoundDetectTime; // Record the time that we measured a sound
//
//int soundAlarmTime = 500; // Number of milli seconds to keep the sound alarm high


/*
 * For more information, see http://arduino.cc/en/Tutorial/Tone
*/
const int buzzerPin = 9;

/* PIR sensor tester */
int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

/*
  HC-SR04 Ping distance sensor:
  VCC to arduino 5v
  GND to arduino GND
  Echo to Arduino pin 7
  Trig to Arduino pin 8

  This sketch originates from Virtualmix: http://goo.gl/kJ8Gl
  Has been modified by Winkle ink here: http://winkleink.blogspot.com.au/2012/05/arduino-hc-sr04-ultrasonic-distance.html
  And modified further by ScottC here: http://arduinobasics.blogspot.com.au/2012/11/arduinobasics-hc-sr04-ultrasonic-sensor.html
  on 10 Nov 2012.
*/

//US sensor
#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin


//#define LEDPin 13 // Onboard LED

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
  pinMode(inputPin, INPUT);    // declare IR sensor as input
  pinMode(buzzerPin, OUTPUT);
//  pinMode (soundDetectedPin, INPUT); // input from the Sound Detection Module

  delay(30000); //30seconds delay before start
}

void loop() {
  /*  UltraSonic Sensor
   *  The following trigPin/echoPin cycle is used to determine the
    distance of the nearest object by bouncing soundwaves off of it. */
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  //Calculate the distance (in cm) based on the speed of sound.
  distance = duration / 58.2;

  if (distance >= maximumRange || distance <= minimumRange) {
    /* Send a negative number to computer and Turn LED ON
      to indicate "out of range" */
    Serial.println("-1");
    // digitalWrite(LEDPin, HIGH);
  } else {
    /* Send the distance to the computer using Serial protocol, and
      turn LED OFF to indicate successful reading. */
    Serial.println(distance);

    if(distance > 3 && distance < 90){
       tone(buzzerPin, 349, 200); //{262, 294, 330, 349, 392, 440, 494, 523};
    } else {
      noTone(buzzerPin);
    }
    
    // digitalWrite(LEDPin, LOW);
  }

  // PIR SENSOR
  val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {            // check if the input is HIGH
    //   digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      analogWrite(9, 240);
      delay(7000);
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    //    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH) {
      // we have just turned of
      Serial.println("Motion ended!");
      analogWrite(9, 0);
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }

//  // SoundSensor
//  soundDetectedVal = digitalRead(soundDetectedPin); // read the sound alarm time
//  //Serial.println(millis());
//  
//  if (soundDetectedVal == LOW) // If we hear a sound
//  {
//    lastSoundDetectTime = millis(); // record the time of the sound alarm
//    // The following is so you don't scroll on the output screen
//    if (!bAlarm){
//      Serial.println("LOUD, LOUD");
//      bAlarm = true;
//    }
//  }
//  else
//  {
//    if( (millis()-lastSoundDetectTime) > soundAlarmTime  &&  bAlarm){
//      Serial.println("quiet");
//      bAlarm = false;
//    }
//  }

  //Delay 50ms before next reading.
  delay(50);
}

////Alternative US calculations
//// See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
//
//long microsecondsToCentimeters(long microseconds) {
//  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
//  // The ping travels out and back, so to find the distance of the
//  // object we take half of the distance travelled.
//
//  return microseconds / 29 / 2;
//}

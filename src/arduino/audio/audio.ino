////Henry's Bench
////Arduino Sound Detection Sensor Module
//
//int soundDetectedPin = 10; // Use Pin 10 as our Input
//int soundDetectedVal = HIGH; // This is where we record our Sound Measurement
//boolean bAlarm = false;
//
//unsigned long lastSoundDetectTime; // Record the time that we measured a sound
//
//
//int soundAlarmTime = 500; // Number of milli seconds to keep the sound alarm high
//
//
//void setup ()
//{
//  Serial.begin(9600);  
//  pinMode (soundDetectedPin, INPUT) ; // input from the Sound Detection Module
//}
//void loop ()
//{
//  soundDetectedVal = digitalRead (soundDetectedPin) ; // read the sound alarm time
//  
//  if (soundDetectedVal == LOW) // If we hear a sound
//  {
//  
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
//}






/* Connections:
 * The Sound Detector is connected to the Adrduino as follows:
 * (Sound Detector -> Arduino pin)
 * GND → GND
 * VCC → 5V
 * Gate → Pin 2
 * Envelope → A0
 * 
 * Resources:
 * Additional library requirements: none
 * 
 * Development environment specifics:
 * Using Arduino IDe 1.0.5
 * Tested on Redboard, 3.3v/8MHz and 5v/16MHz ProMini hardware.
 * 
 * This code is beerware; if you see me (or any other SparkFun employee) at the
 * local, and you've found our code helpful, please buy us a round!
 * 
 * Distributed as-is; no warranty is given.
 ******************************************************************************/

 // Define hardware connections
#define PIN_GATE_IN 2
#define IRQ_GATE_IN  0
#define PIN_LED_OUT 13
#define PIN_ANALOG_IN A0

// soundISR()
// This function is installed as an interrupt service routine for the pin
// change interrupt.  When digital input 2 changes state, this routine
// is called.
// It queries the state of that pin, and sets the onboard LED to reflect that 
// pin's state.
void soundISR()
{
  int pin_val;

  pin_val = digitalRead(PIN_GATE_IN);
  digitalWrite(PIN_LED_OUT, pin_val);   
   Serial.print("irq: ");
   Serial.print(pin_val);
}

void setup()
{
  Serial.begin(9600);

  //  Configure LED pin as output
  pinMode(PIN_LED_OUT, OUTPUT);

  // configure input to interrupt
  pinMode(PIN_GATE_IN, INPUT);
  attachInterrupt(IRQ_GATE_IN, soundISR, CHANGE);

  // Display status
  Serial.println("Initialized");
}

void loop()
{
  int value;

  // Check the envelope input
  value = analogRead(PIN_ANALOG_IN);

  // Convert envelope value into a message
  Serial.print("Status: ");
   Serial.print(value);
  if(value <= 10)
  {
    Serial.println("Quiet.");
  }
  else if( (value > 10) && ( value <= 30) )
  {
    Serial.println("Moderate.");
  }
  else if(value > 30)
  {
    Serial.println("Loud.");
  }

  // pause for 1 second
  delay(1000);
}







//int led = 13;
//int threshold = 500; //Change This
//int volume;
//
//void setup() {                
//  Serial.begin(9600); // For debugging
//  pinMode(led, OUTPUT);     
//}
//
//void loop() {
//  
//  volume = analogRead(A0); // Reads the value from the Analog PIN A0
//  /*
//    //Debug mode
//    Serial.println(volume);
//    delay(100);
//  */
//  
//  if(volume>=threshold){
//    digitalWrite(led, HIGH); //Turn ON Led
//  }  
//  else{
//    digitalWrite(led, LOW); // Turn OFF Led
//  }
//
//}

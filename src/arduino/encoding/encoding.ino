/*
  Analog input

    Reads an analog input on analog in 0, and prints the value out.

    Created 24 March 2006
    by Tom Igoe
*/

int analogValue = 0;    // Variable to hold the analog value.

void setup() {
    // open the serial port at 9600 bit/s:
    Serial.begin(9600);
}

void loop() {
    // Read the analog input on pin 0:
    analogValue = analogRead(0);

    // Print it out in many formats:
    Serial.println(analogValue);       // print as an ASCII-encoded decimal
    Serial.println(analogValue, DEC);  // print as an ASCII-encoded decimal
    Serial.println(analogValue, HEX);  // print as an ASCII-encoded hexadecimal
    Serial.println(analogValue, OCT);  // print as an ASCII-encoded octal
    Serial.println(analogValue, BIN);  // print as an ASCII-encoded binary    

    // Delay 10 milliseconds before the next reading:
    delay(10);
}

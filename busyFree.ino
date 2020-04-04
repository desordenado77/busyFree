/*
Seven Segment Display info:

https://haneefputtur.com/7-segment-4-digit-led-display-sma420564-using-arduino.html

Button:

https://www.arduino.cc/en/tutorial/button

Blinky led:

https://www.arduino.cc/en/tutorial/blink
*/


#include "SevSeg.h"

SevSeg sevseg; //Instantiate a seven segment controller object

#define BUTTON      14
#define RED_LED     15
#define GREEN_LED   16

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(BUTTON, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  byte numDigits = 4;

  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};

  sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins); 
  // If your display is common anode type, please edit comment above line and uncomment below line
  // sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);
}

// the loop function runs over and over again forever
void loop() {
  static int free_or_busy;
  static int prevButtonState = LOW;
  int buttonState = digitalRead(BUTTON);

  if(buttonState == HIGH) {
    if(prevButtonState == LOW) {
      free_or_busy ^= 1;
    }
  }
  prevButtonState = buttonState;
  

  if(free_or_busy) {
    sevseg.setChars("FREE");
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
  }
  else {
    sevseg.setChars("BUSY");
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
  }

  sevseg.refreshDisplay(); // Must run repeatedly
  delay(1);
}

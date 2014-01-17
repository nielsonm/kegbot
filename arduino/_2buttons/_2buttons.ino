/*
  State change detection (edge detection)
 	
 Often, you don't need to know the state of a digital input all the time,
 but you just need to know when the input changes from one state to another.
 For example, you want to know when a button goes from OFF to ON.  This is called
 state change detection, or edge detection.
 
 This example shows how to detect when a button or button changes from off to on
 and on to off.
 	
 The circuit:
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 * LED attached from pin 13 to ground (or use the built-in LED on
   most Arduino boards)
 
 created  27 Sep 2005
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.
 	
 http://arduino.cc/en/Tutorial/ButtonStateChange
 
 */

// this constant won't change:
const int  button1Pin = 2;// the pin that the pushbutton is attached to
const int  button2Pin = 4;// the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int button1PushCounter = 0;   // counter for the number of button presses
int button2PushCounter = 0;   // counter for the number of button presses
int button1State = 0;         // current state of the button
int lastButton1State = 0;     // previous state of the button
int button2State = 0;         // current state of the button
int lastButton2State = 0;     // previous state of the button

void setup() {
  // initialize the button pin as a input:
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  // read the pushbutton input pin:
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  // compare the buttonState to its previous state
  if (button1State != lastButton1State) {
    // if the state has changed, increment the counter
    if (button1State == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      button1PushCounter++;
      Serial.println("on 1");
      Serial.print("number of button pushes:  ");
      Serial.println(button1PushCounter);
    } 
    else {
      // if the current state is LOW then the button
      // wend from on to off:
      //Serial.println("off"); 
    }
  }
  
  // compare the buttonState to its previous state
  else if (button2State != lastButton2State) {
    // if the state has changed, increment the counter
    if (button2State == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      button2PushCounter++;
      Serial.println("on 2");
      Serial.print("number of button pushes:  ");
      Serial.println(button2PushCounter);
    } 
    else {
      // if the current state is LOW then the button
      // wend from on to off:
      // Serial.println("off"); 
    }
  }
  
  // save the current state as the last state, 
  //for next time through the loop
  lastButton1State = button1State;
  lastButton2State = button2State;

  
  // turns on the LED every four button pushes by 
  // checking the modulo of the button push counter.
  // the modulo function gives you the remainder of 
  // the division of two numbers:
  if (button1PushCounter % 4 == 0 || button2PushCounter % 4 == 0) {
    digitalWrite(ledPin, HIGH);
  } else {
   digitalWrite(ledPin, LOW);
  }
  if (button1PushCounter >= 25 || button2PushCounter >= 20){
    softReset();
  }
  
}
void softReset(){
  asm volatile ("  jmp 0");
}









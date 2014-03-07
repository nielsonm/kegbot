#include <OneWire.h>

// this constant won't change:
const int  button1Pin = 8;// the pin that the pushbutton is attached to
const int  button2Pin = 4;// the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to
int DS18S20_Pin = 10; //DS18S20 Signal pin on digital 0

OneWire ds(DS18S20_Pin); // on digital pin 10

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
      float temp = getTemp();
      Serial.println(temp);
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
  // Testing softReset - DELETE ME!!!!
  if (button1PushCounter >= 25 || button2PushCounter >= 20){
    softReset();
  }
}
// Software reset function.
void softReset(){
  asm volatile ("  jmp 0");
}

float getTemp(){
 //returns the temperature from one DS18S20 in DEG KELVIN

 byte data[12];
 byte addr[8];

 if ( !ds.search(addr)) {
   //no more sensors on chain, reset search
   ds.reset_search();
   return -1000;
 }

 if ( OneWire::crc8( addr, 7) != addr[7]) {
   Serial.println("CRC is not valid!");
   return -1000;
 }

 if ( addr[0] != 0x10 && addr[0] != 0x28) {
   Serial.print("Device is not recognized");
   return -1000;
 }

 ds.reset();
 ds.select(addr);
 ds.write(0x44,1); // start conversion, with parasite power on at the end

 byte present = ds.reset();
 ds.select(addr);  
 ds.write(0xBE); // Read Scratchpad

 
 for (int i = 0; i < 9; i++) { // we need 9 bytes
  data[i] = ds.read();
 }
 
 ds.reset_search();
 
 byte MSB = data[1];
 byte LSB = data[0];

 float tempRead = ((MSB << 8) | LSB); //using two's compliment
 float TemperatureSum = tempRead / 16;
 TemperatureSum += 273.15;
 
 return TemperatureSum;
 
}


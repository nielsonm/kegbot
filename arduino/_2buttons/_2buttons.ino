#include <OneWire.h>

// which pin to use for reading the sensor? can use any pin!
#define FLOWSENSORPIN1 4
#define FLOWSENSORPIN2 8

int DS18S20_Pin = 10; //DS18S20 Signal pin on digital 10

OneWire ds(DS18S20_Pin); // on digital pin 10

// count how many pulses!
volatile uint16_t pulses1 = 0;
volatile uint16_t pulses2 = 0;

volatile uint16_t lastpulses = 0;

// track the state of the pulse pin
volatile uint8_t lastflowpinstate1;
volatile uint8_t lastflowpinstate2;
// you can try to keep time of how long it is between pulses
volatile uint32_t lastflowratetimer = 0;
// and use that to calculate a flow rate
volatile float flowrate1;
volatile float flowrate2;
// Interrupt is called once a millisecond, looks for any pulses from the sensor!
SIGNAL(TIMER0_COMPA_vect) {
  uint8_t one = digitalRead(FLOWSENSORPIN1);
  uint8_t two = digitalRead(FLOWSENSORPIN2);
  
  if (one != lastflowpinstate1 && one == HIGH) {
    //low to high transition!
    pulses1++;
  }
  
  if (two != lastflowpinstate2 && two == HIGH) {
    //low to high transition!
    pulses2++;
  }
  
  // Set the flow pin state to the last read.
  lastflowpinstate1 = one;
  lastflowpinstate2 = two;
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
  }
}

void setup() {
   Serial.begin(9600);
   Serial.print("Flow sensor test!");
   
   pinMode(FLOWSENSORPIN1, INPUT);
   digitalWrite(FLOWSENSORPIN1, HIGH);
   lastflowpinstate1 = digitalRead(FLOWSENSORPIN1);
   
   pinMode(FLOWSENSORPIN2, INPUT);
   digitalWrite(FLOWSENSORPIN2, HIGH);
   lastflowpinstate2 = digitalRead(FLOWSENSORPIN2);
   
   useInterrupt(true);
}

void loop(){ 

  Serial.print("Pulses: "); 
  Serial.println(pulses1, DEC); Serial.println(pulses2, DEC);
  
  // if a plastic sensor use the following calculation
  // Sensor Frequency (Hz) = 7.5 * Q (Liters/min)
  // Liters = Q * time elapsed (seconds) / 60 (seconds/minute)
  // Liters = (Frequency (Pulses/second) / 7.5) * time elapsed (seconds) / 60
  // Liters = Pulses / (7.5 * 60)
  
  //float liters1 = pulses1;
  //liters1 /= 7.5;
  //liters1 /= 60.0;
  
  //float liters2 = pulses2;
  //liters2 /= 7.5;
  //liters2 /= 60.0;

  // Print temperature in Kelvin.
  //float temp = getTemp();
  //Serial.println(temp);


  delay(1000);
}


// Software reset function.
void softReset(){
  asm volatile ("  jmp 0");
}
// Get temperature function.
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

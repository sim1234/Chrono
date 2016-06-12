/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/
#include "wiring_private.h"
#include "pins_arduino.h"

void printFloat(float value, int places) {
  // this is used to cast digits 
  int digit;
  float tens = 0.1;
  int tenscount = 0;
  int i;
  float tempfloat = value;

    // make sure we round properly. this could use pow from <math.h>, but doesn't seem worth the import
  // if this rounding step isn't here, the value  54.321 prints as 54.3209

  // calculate rounding term d:   0.5/pow(10,places)  
  float d = 0.5;
  if (value < 0)
    d *= -1.0;
  // divide by ten for each decimal place
  for (i = 0; i < places; i++)
    d/= 10.0;    
  // this small addition, combined with truncation will round our values properly 
  tempfloat +=  d;

  // first get value tens to be the large power of ten less than value
  // tenscount isn't necessary but it would be useful if you wanted to know after this how many chars the number will take

  if (value < 0)
    tempfloat *= -1.0;
  while ((tens * 10.0) <= tempfloat) {
    tens *= 10.0;
    tenscount += 1;
  }
  // write out the negative if needed
  if (value < 0)
    Serial.print('-');

  if (tenscount == 0)
    Serial.print(0, DEC);

  for (i=0; i< tenscount; i++) {
    digit = (int) (tempfloat/tens);
    Serial.print(digit, DEC);
    tempfloat = tempfloat - ((float)digit * tens);
    tens /= 10.0;
  }

  // if no places after decimal, stop now and return
  if (places <= 0)
    return;

  // otherwise, write the point and continue on
  Serial.print('.');  

  // now write out each decimal place by shifting digits one by one into the ones place and writing the truncated value
  for (i = 0; i < places; i++) {
    tempfloat *= 10.0; 
    digit = (int) tempfloat;
    Serial.print(digit,DEC);  
    // once written, subtract off that digit
    tempfloat = tempfloat - (float) digit; 
  }
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max) {
   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

volatile unsigned long D2_micros = 0;
volatile uint8_t D2_state = 0;
volatile unsigned long D3_micros = 0;
volatile uint8_t D3_state = 0;
void D2_ISR(){
  if (D2_state == 1){
    D2_micros = micros();
    D2_state = 2;
  }
}
void D3_ISR(){
  if (D3_state == 1){
    D3_micros = micros();
    D3_state = 2;
  }
}


unsigned long my_mpulse(uint8_t pin){
  uint8_t bit = digitalPinToBitMask(pin);
  uint8_t port = digitalPinToPort(pin);
  //  unsigned long width = 1; // keep initialization out of time critical area
  uint16_t width = 1;
  
  //while ((*portInputRegister(port) & bit) && width++);
  //noInterrupts();
  while ((*portInputRegister(port) & bit)) width++;
  //interrupts();
  return width;
}

unsigned long my_mpulse2(){
  D2_state = 1;
  D3_state = 1;
  //uint16_t t = 1;

  while (D2_state == 1 || D3_state == 1);
  D2_state = 0;
  D3_state = 0;
  //if (t == 0) return 0;
  return D3_micros - D2_micros;
}

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(2), D2_ISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), D3_ISR, FALLING);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  // print out the value you read:
  Serial.print("Potencjometr: ");
  printFloat(fmap(analogRead(A0), 0, 1023, 0.0, 5.0), 6);
  Serial.println("");
  Serial.print("Fotodioda:    ");
  printFloat(fmap(analogRead(A1), 0, 1023, 0.0, 5.0), 6);
  Serial.println("");
  Serial.print("Wyjscie:      ");
  printFloat(fmap(analogRead(A2), 0, 1023, 0.0, 5.0), 6);
  Serial.println("");
  Serial.println("");
  delay(1000);        // delay in between reads for stability
  //unsigned long a = micros();
  //unsigned long b = 0;//my_mpulse(A2);
  //unsigned long c = micros();
  //Serial.println(b);
  //Serial.println(c-a);
  //Serial.println("");
  Serial.println(my_mpulse2());
  //delay(100000);
}

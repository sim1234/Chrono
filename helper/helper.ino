

void setup() {
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  noInterrupts();
}

void my_delay(){
  int c = 2000+random(-500, 500);
  while (c) {
    c--;
    delayMicroseconds(1000);
  }
}

void loop() {
  
  //digitalWrite(11, LOW);
  //digitalWrite(11, HIGH);
  PORTB &= B11110111;
  //__asm__("nop\n\t");
  __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t"); // 1 us
  __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t"); // 1 us
  __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t"); // 1 us
  //delayMicroseconds(20);
  PORTB |= B00001000;
  
  delayMicroseconds(300);
  
  //digitalWrite(12, LOW);
  //digitalWrite(12, HIGH);
  PORTB &= B11101111;
  //__asm__("nop\n\t"); // 62.5 ns
  __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t"); // 1 us
  __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t"); // 1 us
  __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t"); // 1 us
  //delayMicroseconds(20);
  PORTB |= B00010000;
  
  //my_delay();
  //for (int x=0; x<500; x++){
  //  delayMicroseconds(1000);
  //}
  delayMicroseconds(1000);

  //digitalWrite(12, LOW);
  //digitalWrite(12, HIGH);
  PORTB &= B11101111;
  //__asm__("nop\n\t"); // 62.5 ns
  __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t"); // 1 us
  __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t"); // 1 us
  __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t"); // 1 us
  //delayMicroseconds(20);
  PORTB |= B00010000;
  
  delayMicroseconds(300);
  
  //digitalWrite(11, LOW);
  //digitalWrite(11, HIGH);
  PORTB &= B11110111;
  //__asm__("nop\n\t"); // 62.5 ns
  __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t"); // 1 us
  __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t"); // 1 us
  __asm__("nop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\tnop\n\t"); // 1 us
  //delayMicroseconds(20);
  PORTB |= B00001000;
  
  //my_delay();
  delayMicroseconds(1000);
  
}

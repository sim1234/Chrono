

void setup() {
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
}


void loop() {
  digitalWrite(11, LOW);
  digitalWrite(11, HIGH);
  //PORTC &= B11110111;
  //PORTC |= B00001000;
  delayMicroseconds(200-11);
  digitalWrite(12, LOW);
  digitalWrite(12, HIGH);
  //PORTC &= B11101111;
  //PORTC |= B00010000;
  delay(3000+random(-500, 500));
}

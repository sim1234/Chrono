//
// Created by Szymon on 19.06.2016.
//

#include "menu.h"


bool readButton(uint8_t pin) {
    if (!digitalRead(pin)){
        while (!digitalRead(pin)){ 
            delay(10);
        }
        return 1;
    }
    return 0;
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}



Menu::Menu(PCD8544 *display) {
    this->display = display;
    pinMode(this->BTN_PLUS,  INPUT_PULLUP);
    pinMode(this->BTN_MINUS, INPUT_PULLUP);
    pinMode(this->BTN_NEXT,  INPUT_PULLUP);
    //this->refresh();
    start_measurement();

}

void Menu::processIO() {
    /*
    if (readButton(this->BTN_PLUS)){
        this->mass += this->mass_step;
        this->refresh();
    }
    if (readButton(this->BTN_MINUS) && this->mass > this->mass_step){
        this->mass -= this->mass_step;
        this->refresh();
    }
     */
    /*
    if (!measurement_running()){
        this->measurement = get_measurement();
        stop_measurement();
        this->refresh();
        delay(500);
        start_measurement();
    }
     */
    if (!measurement_running()){
        long m = abs(get_measurement());
        if (get_time(m) >= 0.0001 && get_time(m) <= 1.0 && get_measurement() < 0.0) { // Reduce noise
            this->display->ledON();
            this->measurement = m;
            stop_measurement();
            this->refresh();
            digitalWrite(13, LOW);
            Serial.print("{\"time\": ");
            Serial.print(get_time(this->measurement)*1000000.0);
            Serial.print(", \"mass\": ");
            Serial.print(this->mass);
            Serial.print(", \"distance\": ");
            Serial.print(this->dist*1000.0);
            Serial.println("}");
            delay(100); // 500
            start_measurement();
            /*Serial.print("V0=");
            Serial.print(fmap(float(analogRead(A0)), 0.0, 1023.0, 0.0, 5000.0));
            Serial.println("mV");
            Serial.print("V1=");
            Serial.print(fmap(float(analogRead(A1)), 0.0, 1023.0, 0.0, 5000.0));
            Serial.println("mV");
            Serial.println("");*/
            this->last_measurement_running2 = 0;
            this->display->ledOFF();
       } else {
          stop_measurement();
          start_measurement();
          this->last_measurement_running2 = 0;
       }
    }
    if (measurement_running2()) {
        if (this->last_measurement_running2 == 0){
            this->last_measurement_running2 = millis();
            digitalWrite(13, HIGH);
        } else if (this->last_measurement_running2 + 1000 < millis()) { // Restart measurement
            start_measurement();
            digitalWrite(13, LOW);
            this->last_measurement_running2 = 0;
        }
    }
    if (readButton(this->BTN_PLUS)) {
        this->mass += this->mass_step;
        this->refresh();
    }
    if (readButton(this->BTN_MINUS)) {
        this->mass -= this->mass_step;
        this->refresh();
    }
}

void Menu::refresh() {
    char a[10];

    this->display->clear();

    this->display->gotoXY(0, 0);
    this->display->string("M=");
    dtostrf(this->mass/1000.0, 8, 3, a);
    this->display->string(a);
    this->display->string("g");

    this->display->gotoXY(0, 1);
    this->display->string("T=");
    dtostrf(get_time(this->measurement)*1000000.0, 8, 1, a);
    this->display->string(a);
    this->display->string("us");

    this->display->gotoXY(0, 2);
    this->display->string("V=");
    dtostrf(get_speed(this->dist, this->measurement), 8, 2, a); // 7
    this->display->string(a);
    //this->display->string("m/s");
    this->display->character((unsigned char)0x80);
    this->display->character(' ');

    this->display->gotoXY(0, 3);
    this->display->string("E=");
    dtostrf(get_energy(this->mass/1000000.0, this->dist, this->measurement), 8, 2, a);
    this->display->string(a);
    this->display->string("J ");


}



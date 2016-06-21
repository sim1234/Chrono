//
// Created by Szymon on 19.06.2016.
//

#include "menu.h"


bool readButton(uint8_t pin) {
    if (!digitalRead(pin)){
        while (!digitalRead(pin)){
            delay(1);
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
    pinMode(this->BTN_PLUS,  INPUT);
    pinMode(this->BTN_MINUS, INPUT);
    pinMode(this->BTN_NEXT,  INPUT);
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
        this->measurement = get_measurement();
        stop_measurement();
        this->refresh();
        delay(100); // 500
        start_measurement();
        digitalWrite(13, LOW);
        this->last_measurement_running2 = 0;
    }
    if (measurement_running2()) {
        if (this->last_measurement_running2 == 0){
            this->last_measurement_running2 = millis();
            digitalWrite(13, HIGH);
        } else if (this->last_measurement_running2 + 2000 < millis()) { // Restart measurement
            start_measurement();
            digitalWrite(13, LOW);
            this->last_measurement_running2 = 0;
        }
    }
}

void Menu::refresh() {
    char a[10];

    this->display->clear();

    this->display->gotoXY(0, 0);
    this->display->string("M=");
    dtostrf(mass, 9, 3, a);
    this->display->string(a);
    this->display->string("g");

    this->display->gotoXY(0, 1);
    this->display->string("T=");
    dtostrf(get_time(this->measurement), 9, 3, a);
    this->display->string(a);
    this->display->string("s");

    this->display->gotoXY(0, 2);
    this->display->string("V=");
    dtostrf(get_speed(dist, this->measurement), 9, 3, a); // 7
    this->display->string(a);
    //this->display->string("m/s");
    this->display->character((unsigned char)0x80);

    this->display->gotoXY(0, 3);
    this->display->string("E=");
    dtostrf(get_energy(mass, dist, this->measurement), 9, 3, a);
    this->display->string(a);
    this->display->string("J");


}



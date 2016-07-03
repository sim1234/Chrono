//
// Created by Szymon on 19.06.2016.
//

#ifndef CHRONO_MENU_H
#define CHRONO_MENU_H

#include "Arduino.h"

#include "PCD8544.h"
#include "measurement.h"

class Menu {
private:
    PCD8544* display;

    uint8_t BTN_PLUS = 4;
    uint8_t BTN_MINUS = 5;
    uint8_t BTN_NEXT = 6;

    float mass = 530.0;  // mg
    float dist = 0.1;  // m
    float mass_step = 10.0; // mg
    long measurement = 0;

    unsigned long last_measurement_running2 = 0;

public:
    Menu(PCD8544* display);
    void refresh();
    void processIO();

};

#endif //CHRONO_MENU_H

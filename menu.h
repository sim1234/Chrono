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

    uint8_t BTN_PLUS = 10;
    uint8_t BTN_MINUS = 11;
    uint8_t BTN_NEXT = 12;

    float mass = 0.1;  // g
    float dist = 0.1;  // m
    float mass_step = 0.01;
    long measurement = 0;

    unsigned long last_measurement_running2 = 0;

public:
    Menu(PCD8544* display);
    void refresh();
    void processIO();

};

#endif //CHRONO_MENU_H

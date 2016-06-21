//
// Created by Szymon on 19.06.2016.
//

#ifndef CHRONO_MEASUREMENT_H
#define CHRONO_MEASUREMENT_H

#include "Arduino.h"

#include "eRCaGuy_Timer2_Counter.h"


void init_measurement(int PIN_2 = 2, int PIN_3 = 3);
void start_measurement();
void stop_measurement();
long get_measurement();
bool measurement_running();
bool measurement_running2();
long measurement();

float get_time(long count);
float get_speed(float distance, long count);
float get_energy(float mass, float distance, long count);

long test();



#endif //CHRONO_MEASUREMENT_H

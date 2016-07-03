//
// Created by Szymon on 19.06.2016.
//

#include "measurement.h"


// State: (D2_state, D3_state)
// 0 - waiting for interrupt
// 1 - disabled, got no interrupt
// 2 - disabled, got interrupt

volatile unsigned long D2_count = 0;
volatile uint8_t D2_state = 1;
volatile unsigned long D3_count = 0;
volatile uint8_t D3_state = 1;

void D2_ISR() {
    if (!D2_state){
        //D2_count = micros();
        D2_count = timer2.get_count();
        D2_state = 2;
    }
}

void D3_ISR() {
    if (!D3_state){
        //D3_count = micros();
        D3_count = timer2.get_count();
        D3_state = 2;
    }
}

void init_measurement(int PIN_2, int PIN_3) {
    attachInterrupt(digitalPinToInterrupt(PIN_2), D2_ISR, RISING); // FALLING
    attachInterrupt(digitalPinToInterrupt(PIN_3), D3_ISR, RISING); // FALLING
    timer2.setup();
}

void start_measurement() {
    D2_state = 0;
    D3_state = 0;
}

bool measurement_running() {
    return D2_state == 0 || D3_state == 0;
    //return D2_state == 0;
}

bool measurement_running2() {
    return measurement_running() && (D2_state == 2 || D3_state == 2);
}

void stop_measurement() {
    D2_state = 1;
    D3_state = 1;
}

long get_measurement() {
    return D3_count - D2_count;
}

long measurement() {
    start_measurement();
    //uint16_t t = 1;
    while (measurement_running()); // Wait for measurement to happen
    stop_measurement();
    //if (t == 0) return 0;
    return get_measurement();
}

float get_time(long count) {
    return float(count) * 0.0000005;
}

float get_speed(float distance, long count) {
    return distance / get_time(count);
}

float get_energy(float mass, float distance, long count) {
    return mass * sq(get_speed(distance, count)) / 2.0;
}

long test() {
    start_measurement();
    while (D2_state == 0);
    stop_measurement();
    return D2_count;
}

/*
#include "wiring_private.h"
#include "pins_arduino.h"
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
*/


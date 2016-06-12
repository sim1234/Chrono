//
// Mods by Jim Park
// jim(^dOt^)buzz(^aT^)gmail(^dOt^)com
// Modified by Szymon on 12.06.2016.
//
// Handler for Nokia 3310 LCD
// It is modded from the original
// http://playground.arduino.cc/Code/PCD8544

#include "PCD8544.h"


PCD8544::PCD8544(int PIN_RESET, int PIN_SCE, int PIN_SCLK, int PIN_DC, int PIN_SDIN, int PIN_LED,
                 int LCD_X, int LCD_Y, int LCD_CMD, int LCD_C, int LCD_D)
{
    this->PIN_RESET = PIN_RESET;
    this->PIN_SCE = PIN_SCE;
    this->PIN_SCLK = PIN_SCLK;
    this->PIN_DC = PIN_DC;
    this->PIN_SDIN = PIN_SDIN;
    this->PIN_LED = PIN_LED;
    this->LCD_X = LCD_X;
    this->LCD_Y = LCD_Y;
    this->LCD_CMD = LCD_CMD;
    this->LCD_C = LCD_C;
    this->LCD_D = LCD_D;
};

void PCD8544::initialise() {
    pinMode(this->PIN_SCE,   OUTPUT);
    pinMode(this->PIN_RESET, OUTPUT);
    pinMode(this->PIN_DC,    OUTPUT);
    pinMode(this->PIN_SDIN,  OUTPUT);
    pinMode(this->PIN_SCLK,  OUTPUT);

    digitalWrite(this->PIN_RESET, LOW);
    // delay(1);
    digitalWrite(this->PIN_RESET, HIGH);

    this->write(this->LCD_CMD, 0x21 );  // LCD Extended Commands.
    this->write(this->LCD_CMD, 0xBf );  // Set LCD Vop (Contrast). //B1
    this->write(this->LCD_CMD, 0x04 );  // Set Temp coefficent. //0x04
    this->write(this->LCD_CMD, 0x14 );  // LCD bias mode 1:48. //0x13
    this->write(this->LCD_CMD, 0x0C );  // LCD in normal mode. 0x0d for inverse
    this->write(this->LCD_C, 0x20);
    this->write(this->LCD_C, 0x0C);
}

void PCD8544::character(const char character) {
    this->write(this->LCD_D, 0x00);
    for (int index = 0; index < 5; index++) {
        this->write(this->LCD_D, ASCII_MAP[character - 0x20][index]);
    }
    this->write(this->LCD_D, 0x00);
}

void PCD8544::string(const char *characters) {
    while (*characters) {
        this->character(*characters++);
    }
}

void PCD8544::clear() {
    for (int index = 0; index < this->LCD_X * this->LCD_Y / 8; index++) {
        this->write(this->LCD_D, 0x00);
    }
}

void PCD8544::write(char dc, char data) {
    digitalWrite(this->PIN_DC, dc);
    digitalWrite(this->PIN_SCE, LOW);
    shiftOut(this->PIN_SDIN, this->PIN_SCLK, MSBFIRST, data);
    digitalWrite(this->PIN_SCE, HIGH);
}

void PCD8544::ledON() {
    if (this->PIN_LED) {
        digitalWrite(this->PIN_LED, HIGH);
    }
}

void PCD8544::ledOFF() {
    if (this->PIN_LED) {
        digitalWrite(this->PIN_LED, LOW);
    }
}

// gotoXY routine to position cursor
// x - range: 0 to 84
// y - range: 0 to 5
void PCD8544::gotoXY(int x, int y) {
    this->write(0, 0x80 | x);  // Column.
    this->write(0, 0x40 | y);  // Row.

}

void PCD8544::line() {
    unsigned char  j;
    for(j=0; j<84; j++) // top
    {
        this->gotoXY(j, 0);
        this->write(1, 0x01);
    }
    for(j=0; j<84; j++) //Bottom
    {
        this->gotoXY(j, 5);
        this->write(1, 0x80);
    }

    for(j=0; j<6; j++) // Right
    {
        this->gotoXY(83, j);
        this->write(1, 0xff);
    }
    for(j=0; j<6; j++) // Left
    {
        this->gotoXY(0, j);
        this->write(1, 0xff);
    }
}


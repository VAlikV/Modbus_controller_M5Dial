#ifndef MAIN_SCREEN
#define MAIN_SCREEN

#include <Arduino.h>
#include <M5Dial.h>

void setupM5Dial();

void drawMenu(uint8_t selected);
void drawCursor(uint8_t selected);

#endif
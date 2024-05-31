#ifndef MAIN_SCREEN
#define MAIN_SCREEN

#include <Arduino.h>
#include <M5Dial.h>

void setupM5Dial();

void drawMainMenu(uint8_t main_menu_mode);
void drawCursor(uint8_t main_menu_mode);

void drawSettingMenu();

#endif
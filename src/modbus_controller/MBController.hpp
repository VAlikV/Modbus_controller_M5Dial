#ifndef MB_CONTROLLER
#define MB_CONTROLLER

#include <Arduino.h>
#include <SPIFFS.h>
#include <M5Dial.h>
#include <M5GFX.h>
//#include "../pictures/pictures_bitmap.hpp"


class MBController
{
private:

    M5GFX display_;

    uint16_t main_color_ = 0b1111101111000000; // Темнооранжевый
    uint16_t temp_color_ = 0b0000010010011111; // Голубой

    bool update_ = true; // Нужно ли обновлять экран

    int current_menu_ = 0;      // id текущего меню
    int main_menu_mode_ = 0;    // id выбранного элемента в главном меню

    long oldPosition_ = 0;       // Передыдущее состояние энкодера 
    long newPosition_ = 0;       // Текущее состояние энкодера

    const char* state_name_[16] = {
    "none", "touch", "touch_end", "touch_begin",
    "___",  "hold",  "hold_end",  "hold_begin",
    "___",  "flick", "flick_end", "flick_begin",
    "___",  "drag",  "drag_end",  "drag_begin"};    // Названия ивентов сенсора

    m5::touch_state_t prev_state_;       // Предыдущее состояние сенсора

    byte temperature_ = 10;

    bool transmit_ = false;
    unsigned long last_time_;

    void drawMainMenu();
    void selectAnimation(byte btn);

    void drawTempMenu();
    void setTemp(byte inc);
    void drawCursor();
    void sendTemperature();

    void drawPlayMenu();
    void drawBut();

public:

    MBController();

    void setupM5Dial();

    void updateM5Dial();

    void checkEncoder();
    void checkTouch();
    void checkButton();

    void updateScreen();

    void sendMessage();
};

#endif
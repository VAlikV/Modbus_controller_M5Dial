#ifndef MB_CONTROLLER
#define MB_CONTROLLER

#include <Arduino.h>
#include <M5Dial.h>

class MBController
{
private:
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

    void drawCursor();
    void drawMainMenu();

public:

    MBController();

    void setupM5Dial();
    void updateM5Dial();

    void checkEncoder();
    void checkTouch();

    void updateScreen();
};

#endif
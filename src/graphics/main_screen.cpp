#include "main_screen.hpp"

void setupM5Dial()
{
    auto cfg = M5.config();
    M5Dial.begin(cfg, true, false);
    M5Dial.Display.setTextColor(WHITE);
    M5Dial.Display.setTextDatum(middle_center);
    M5Dial.Display.setTextFont(&fonts::DejaVu24);
    M5Dial.Display.setTextSize(1);
}

void drawMainMenu(uint8_t main_menu_mode)
{
    uint8_t add_const[2] = {0, 0};
    add_const[main_menu_mode] = 5;

    M5Dial.Display.fillRect(0, M5Dial.Display.height()/2 - 27, M5Dial.Display.width(), 54, BLACK);
    M5Dial.Display.fillRect(M5Dial.Display.width()/4, M5Dial.Display.height()/8, M5Dial.Display.width()/2, 40, BLACK);

    M5Dial.Display.fillCircle(M5Dial.Display.width()*0.13, M5Dial.Display.height()/2, 20 + add_const[0], RED);
    //M5Dial.Display.drawString("A", M5Dial.Display.width()*0.13, M5Dial.Display.height()/2);

    M5Dial.Display.fillCircle(M5Dial.Display.width()*0.87, M5Dial.Display.height()/2, 20 + add_const[1], BLUE);
    //M5Dial.Display.drawString("B", M5Dial.Display.width()*0.8745, M5Dial.Display.height()/2);

    switch(main_menu_mode)
    {
        case 0:
            M5Dial.Display.drawString("Settings", M5Dial.Display.width()/2, M5Dial.Display.height()/8 + 20);
            break;
        case 1:
            M5Dial.Display.drawString("Start", M5Dial.Display.width()/2, M5Dial.Display.height()/8 + 20);
            break;
        default:
            M5Dial.Display.drawString("...", M5Dial.Display.width()/2, M5Dial.Display.height()/8 + 20);
            break;
    }

    drawCursor(main_menu_mode);
}

void drawCursor(uint8_t main_menu_mode)
{
    float angle[2] = {3.1415, 0};
    M5Dial.Display.fillCircle(M5Dial.Display.width()/2 + M5Dial.Display.width()*0.2*cos(angle[main_menu_mode]), M5Dial.Display.height()/2, 5, WHITE);
}

void drawSettingMenu()
{
    
}
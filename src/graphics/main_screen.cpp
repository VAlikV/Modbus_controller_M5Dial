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

void drawMenu(uint8_t selected)
{
    uint8_t add_const[2] = {0, 0};
    add_const[selected] = 5;
    M5Dial.Display.clear();
    M5Dial.Display.fillCircle(M5Dial.Display.width()*0.13, M5Dial.Display.height()/2, 20 + add_const[0], RED);
    //M5Dial.Display.drawString("A", M5Dial.Display.width()*0.13, M5Dial.Display.height()/2);

    M5Dial.Display.fillCircle(M5Dial.Display.width()*0.87, M5Dial.Display.height()/2, 20 + add_const[1], BLUE);
    M5Dial.Display.display();
    //M5Dial.Display.drawString("B", M5Dial.Display.width()*0.8745, M5Dial.Display.height()/2);
}

void drawCursor()
{

}
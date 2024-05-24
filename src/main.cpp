#include "graphics/main_screen.hpp"

bool update = true;

long oldPosition = 0;
long newPosition = 0;

void setup()
{
    setupM5Dial();
    drawMenu(0);
}

void loop() 
{
    //M5Dial.update();
    newPosition = M5Dial.Encoder.read();

    if (abs(newPosition - oldPosition) >= 4) {
        update = !update;
        if (update)
        {
            M5Dial.Speaker.tone(4000, 20);
            drawMenu(0);
        }
        else
        {
            M5Dial.Speaker.tone(8000, 20);
            drawMenu(1);
        }
        M5Dial.Display.drawString(String(newPosition), M5Dial.Display.width()/2, M5Dial.Display.height()/2);
        oldPosition = newPosition;
    }
    
}
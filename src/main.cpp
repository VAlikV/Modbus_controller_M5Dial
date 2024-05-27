#include "graphics/main_screen.hpp"

bool update = true;

long oldPosition = 0;
long newPosition = 0;

static constexpr const char* state_name[16] = {
    "none", "touch", "touch_end", "touch_begin",
    "___",  "hold",  "hold_end",  "hold_begin",
    "___",  "flick", "flick_end", "flick_begin",
    "___",  "drag",  "drag_end",  "drag_begin"};

static m5::touch_state_t prev_state;

void setup()
{
    setupM5Dial();
    drawMenu(0);
}

void loop() 
{
    M5Dial.update();
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

    auto t = M5Dial.Touch.getDetail();

    if (prev_state != t.state) {
        prev_state= t.state;
        M5Dial.Display.fillRect(M5Dial.Display.width()/2-40, M5Dial.Display.height()/2-27, 80, 54, BLACK);
        oldPosition = 0;
        M5Dial.Encoder.write(0);
        M5Dial.Display.drawString(String(oldPosition), M5Dial.Display.width()/2, M5Dial.Display.height()/2);
    }

}
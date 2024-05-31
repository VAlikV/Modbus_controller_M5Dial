#include "graphics/main_screen.hpp"

bool update = true;

byte current_menu = 0;
byte main_menu_mode = 0;

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
    drawMainMenu(0);
}

void loop() 
{
    M5Dial.update();

    // ----------------------------------------------------- Отрисовка

    if (update) // Экран
    {
        switch(current_menu)
        {
            case 0:
                drawMainMenu(main_menu_mode);
                break;
            default:
                current_menu = 0;
                break;
        }
        M5Dial.Display.drawString(String(newPosition), M5Dial.Display.width()/2, M5Dial.Display.height()/2);

        update = false;
    }

    // ----------------------------------------------------- Обработка энкодера

    newPosition = M5Dial.Encoder.read();

    if (newPosition - oldPosition >= 4) {  // Поворот энкодера
        M5Dial.Speaker.tone(8000, 20);

        switch(current_menu)
        {
            case 0:
                ++main_menu_mode;
                if (main_menu_mode > 1)
                {
                    main_menu_mode = 0;
                }
                else if (main_menu_mode < 0)
                {
                    main_menu_mode = 1;
                }
                break;
            default:
                current_menu = 0;
                break;
        }
        
        oldPosition = newPosition;
        update = true;
    }
    else if (newPosition - oldPosition <= -4)
    {
        M5Dial.Speaker.tone(4000, 20);

        switch(current_menu)
        {
            case 0:
                --main_menu_mode;
                if (main_menu_mode > 1)
                {
                    main_menu_mode = 0;
                }
                else if (main_menu_mode < 0)
                {
                    main_menu_mode = 1;
                }
                break;
            default:
                current_menu = 0;
                break;
        }
        
        oldPosition = newPosition;
        update = true;
    }

    // ----------------------------------------------------- Обработка касания сенсора
    
    auto t = M5Dial.Touch.getDetail();

    if (prev_state != t.state)
    {
        prev_state= t.state;
        oldPosition = 0;
        newPosition = 0;
        M5Dial.Encoder.write(0);
        update = true;
    }

}
#include "MBController.hpp"

MBController::MBController()
{
    // setupM5Dial();
} 

void MBController::setupM5Dial()
{
    auto cfg = M5.config();
    M5Dial.begin(cfg, true, false);
    M5Dial.Display.setTextColor(WHITE);
    M5Dial.Display.setTextDatum(middle_center);
    M5Dial.Display.setTextFont(&fonts::DejaVu24);
    M5Dial.Display.setTextSize(1);
}

void MBController::updateM5Dial()
{
     M5Dial.update();
}

void MBController::checkEncoder()
{
    newPosition_ = M5Dial.Encoder.read();

    if (newPosition_ - oldPosition_ >= 4) {  // Поворот энкодера
        M5Dial.Speaker.tone(8000, 20);

        switch(current_menu_)
        {
            case 0:
                ++main_menu_mode_;
                if (main_menu_mode_ > 1)
                {
                    main_menu_mode_ = 0;
                }
                else if (main_menu_mode_ < 0)
                {
                    main_menu_mode_ = 1;
                }
                break;
            default:
                current_menu_ = 0;
                break;
        }
        
        oldPosition_ = newPosition_;
        update_ = true;
    }
    else if (newPosition_ - oldPosition_ <= -4)
    {
        M5Dial.Speaker.tone(4000, 20);

        switch(current_menu_)
        {
            case 0:
                --main_menu_mode_;
                if (main_menu_mode_ > 1)
                {
                    main_menu_mode_ = 0;
                }
                else if (main_menu_mode_ < 0)
                {
                    main_menu_mode_ = 1;
                }
                break;
            default:
                current_menu_ = 0;
                break;
        }
        
        oldPosition_ = newPosition_;
        update_ = true;
    }
}

void MBController::checkTouch()
{
    auto t = M5Dial.Touch.getDetail();

    if (prev_state_ != t.state)
    {
        prev_state_ = t.state;
        oldPosition_ = 0;
        newPosition_ = 0;
        M5Dial.Encoder.write(0);
        update_ = true;
    }
}

void MBController::updateScreen()
{
    if (update_)
    {
        switch(current_menu_)
        {
            case 0:
                drawMainMenu();
                break;
            default:
                current_menu_ = 0;
                break;
        }
        M5Dial.Display.drawString(String(newPosition_), M5Dial.Display.width()/2, M5Dial.Display.height()/2);

        update_ = false;
    }
}



void MBController::drawCursor()
{
    float angle[2] = {3.1415, 0};
    M5Dial.Display.fillCircle(M5Dial.Display.width()/2 + M5Dial.Display.width()*0.2*cos(angle[main_menu_mode_]), M5Dial.Display.height()/2, 5, WHITE);
}

void MBController::drawMainMenu()
{
    uint8_t add_const[2] = {0, 0};
    add_const[main_menu_mode_] = 5;

    M5Dial.Display.fillRect(0, M5Dial.Display.height()/2 - 27, M5Dial.Display.width(), 54, BLACK);
    M5Dial.Display.fillRect(M5Dial.Display.width()/4, M5Dial.Display.height()/8, M5Dial.Display.width()/2, 40, BLACK);

    M5Dial.Display.fillCircle(M5Dial.Display.width()*0.13, M5Dial.Display.height()/2, 20 + add_const[0], RED);

    M5Dial.Display.fillCircle(M5Dial.Display.width()*0.87, M5Dial.Display.height()/2, 20 + add_const[1], BLUE);

    switch(main_menu_mode_)
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

    drawCursor();
}


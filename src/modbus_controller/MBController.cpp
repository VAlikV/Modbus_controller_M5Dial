#include "MBController.hpp"

MBController::MBController()
{
    // setupM5Dial();
} 

void MBController::setupM5Dial()
{
    auto cfg = M5.config();
    M5Dial.begin(cfg, true, false);

    //M5Dial.Display.begin();
    M5Dial.Display.setTextColor(WHITE);
    M5Dial.Display.setTextDatum(middle_center);
    M5Dial.Display.setTextFont(&fonts::DejaVu24);
    M5Dial.Display.setTextSize(1);

    M5Dial.Display.setBrightness(64);

    //delay(3000);
    SPIFFS.begin(true);

    // filesOpen();
}

void MBController::filesOpen()
{    
    // settings_picture_ = SPIFFS.open("/Setting.png");
    // if(!settings_picture_){
    //     Serial.println("Failed to open file!");
    //     return;
    // }
    // play_picture_ = SPIFFS.open("/Start.png");
    // if(!play_picture_){
    //     Serial.println("Failed to open file!");
    //     return;
    // }
    // temperature_picture_ = SPIFFS.open("/Temperature.png");
    // if(!temperature_picture_){
    //     Serial.println("Failed to open file!");
    //     return;
    // }
    // setup_picture_ = SPIFFS.open("/Setup.png");
    // if(!setup_picture_){
    //     Serial.println("Failed to open file!");
    //     return;
    // }
}

void MBController::updateM5Dial()
{
    M5Dial.update();
}

void MBController::checkEncoder()
{
    // newPosition_ = M5Dial.Encoder.read();

    // if (newPosition_ - oldPosition_ >= 4) {  // Поворот энкодера
    //     M5Dial.Speaker.tone(8000, 20);

    //     switch(current_menu_)
    //     {
    //         case 0:
    //             ++main_menu_mode_;
    //             if (main_menu_mode_ > 1)
    //             {
    //                 main_menu_mode_ = 0;
    //             }
    //             else if (main_menu_mode_ < 0)
    //             {
    //                 main_menu_mode_ = 1;
    //             }
    //             break;
    //         default:
    //             current_menu_ = 0;
    //             break;
    //     }
        
    //     oldPosition_ = newPosition_;
    //     update_ = true;
    // }
    // else if (newPosition_ - oldPosition_ <= -4)
    // {
    //     M5Dial.Speaker.tone(4000, 20);

    //     switch(current_menu_)
    //     {
    //         case 0:
    //             --main_menu_mode_;
    //             if (main_menu_mode_ > 1)
    //             {
    //                 main_menu_mode_ = 0;
    //             }
    //             else if (main_menu_mode_ < 0)
    //             {
    //                 main_menu_mode_ = 1;
    //             }
    //             break;
    //         default:
    //             current_menu_ = 0;
    //             break;
    //     }
        
    //     oldPosition_ = newPosition_;
    //     update_ = true;
    // }
}

void MBController::checkTouch()
{
    auto t = M5Dial.Touch.getDetail();

    if (prev_state_ != t.state)
    {
        if (state_name_[t.state] == "touch")
        {
            if ((t.x < M5Dial.Display.width()/2 - 5) && (t.y < M5Dial.Display.height()/2 - 5))
            {
                selectAnimation(1);
            }
            else if ((t.x < M5Dial.Display.width()/2 - 5) && (t.y > M5Dial.Display.height()/2 + 5))
            {
                selectAnimation(2);
            }
            else if ((t.x > M5Dial.Display.width()/2 + 5) && (t.y > M5Dial.Display.height()/2 + 5))
            {
                selectAnimation(3);
            }
            else
            {
                selectAnimation(0);
            }
        }
        prev_state_ = t.state;
        // update_ = true;
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

        update_ = false;
    }
}

void MBController::drawCursor()
{
    // float angle[2] = {3.1415, 0};
    // M5Dial.Display.fillCircle(M5Dial.Display.width()/2 + M5Dial.Display.width()*0.2*cos(angle[main_menu_mode_]), M5Dial.Display.height()/2, 5, WHITE);
}

void MBController::drawMainMenu()
{
    M5Dial.Display.drawPngFile(SPIFFS, "/Main_Temperature.png", 0, 0);
    //M5Dial.Display.drawPngFile(SPIFFS, "/Main_Temperature.png", 0, 0, M5Dial.Display.width(), M5Dial.Display.height(), 0, 0, 2, 2);
    M5Dial.Display.drawPngFile(SPIFFS, "/Main_Start.png", 0, 125);
    M5Dial.Display.drawPngFile(SPIFFS, "/Main_Setup.png", 125, 125);

    M5Dial.Display.drawString("MBC", 172, 68);
}

void MBController::selectAnimation(byte btn)
{
    switch (btn)
    {
        case 1:
            M5Dial.Display.fillRect(150,80,50,30, BLACK);
            M5Dial.Display.drawString("1", 172, 96);
            M5Dial.Speaker.tone(8000, 20);
            M5Dial.Display.drawPngFile(SPIFFS, "/Main_Temperature.png", 0, 0, M5Dial.Display.width(), M5Dial.Display.height(), 0, 0, 1.0435, 1.0435);
            delay(30);
            M5Dial.Display.drawPngFile(SPIFFS, "/Main_Cross.png", 0, 0);
            M5Dial.Display.drawPngFile(SPIFFS, "/Main_Temperature.png", 0, 0);

            break;

        case 2:
            M5Dial.Display.fillRect(150,80,50,30, BLACK);
            M5Dial.Display.drawString("2", 172, 96);
            M5Dial.Speaker.tone(7000, 20);
            M5Dial.Display.drawPngFile(SPIFFS, "/Main_Start.png", 0, 120, M5Dial.Display.width(), M5Dial.Display.height(), 0, 0, 1.0435, 1.0435);
            delay(30);
            M5Dial.Display.drawPngFile(SPIFFS, "/Main_Cross.png", 0, 0);
            M5Dial.Display.drawPngFile(SPIFFS, "/Main_Start.png", 0, 125);
            break;

        case 3:
            M5Dial.Display.fillRect(150,80,50,30, BLACK);
            M5Dial.Display.drawString("3", 172, 96);
            M5Dial.Speaker.tone(6000, 20);
            M5Dial.Display.drawPngFile(SPIFFS, "/Main_Setup.png", 120, 120, M5Dial.Display.width(), M5Dial.Display.height(), 0, 0, 1.0435, 1.0435);
            delay(30);
            M5Dial.Display.drawPngFile(SPIFFS, "/Main_Cross.png", 0, 0);
            M5Dial.Display.drawPngFile(SPIFFS, "/Main_Setup.png", 125, 125);

            break;

        default:
            M5Dial.Display.fillRect(150,80,50,30, BLACK);
            M5Dial.Display.drawString("...", 172, 96);
            M5Dial.Speaker.tone(4000, 20);
            delay(30);
            break;
    }
}
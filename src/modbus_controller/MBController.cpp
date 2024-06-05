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

    M5Dial.Display.setBrightness(64);
    delay(3000);

    if(!SPIFFS.begin(true)){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
    else 
    {
        Serial.println("A SPIFFS");
    }

    filesOpen();
}

void MBController::filesOpen()
{    
    settings_picture_ = SPIFFS.open("/Setting.png");
    if(!settings_picture_){
        Serial.println("Failed to open file!");
        return;
    }
    play_picture_ = SPIFFS.open("/Start.png");
    if(!play_picture_){
        Serial.println("Failed to open file!");
        return;
    }
    temperature_picture_ = SPIFFS.open("/Temperature.png");
    if(!temperature_picture_){
        Serial.println("Failed to open file!");
        return;
    }
    setup_picture_ = SPIFFS.open("/Setup.png");
    if(!setup_picture_){
        Serial.println("Failed to open file!");
        return;
    }
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
        if (state_name_[t.state] == "touch")
        {
            if ((t.x < M5Dial.Display.width()/2 - 5) && (t.y < M5Dial.Display.height()/2 - 5))
            {
                M5Dial.Display.fillRect(142, 83, 60, 25, BLACK);
                M5Dial.Display.drawString("1", 172, 96);
                selectAnimation(1);
            }
            else if ((t.x < M5Dial.Display.width()/2 - 5) && (t.y > M5Dial.Display.height()/2 + 5))
            {
                M5Dial.Display.fillRect(142, 83, 60, 25, BLACK);
                M5Dial.Display.drawString("2", 172, 96);
                selectAnimation(2);
            }
            else if ((t.x > M5Dial.Display.width()/2 + 5) && (t.y > M5Dial.Display.height()/2 + 5))
            {
                M5Dial.Display.fillRect(142, 83, 60, 25, BLACK);
                M5Dial.Display.drawString("3", 172, 96);
                selectAnimation(3);
            }
            else
            {
                M5Dial.Display.fillRect(142, 83, 60, 25, BLACK);
                M5Dial.Display.drawString("...", 172, 96);
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
    float angle[2] = {3.1415, 0};
    M5Dial.Display.fillCircle(M5Dial.Display.width()/2 + M5Dial.Display.width()*0.2*cos(angle[main_menu_mode_]), M5Dial.Display.height()/2, 5, WHITE);
}

void MBController::drawMainMenu()
{
    M5Dial.Display.fillRect(0, 0, M5Dial.Display.width()/2, M5Dial.Display.height(), BLACK);
    M5Dial.Display.fillRect(0, M5Dial.Display.height()/2, M5Dial.Display.width(), M5Dial.Display.height()/2, BLACK);

    //M5Dial.Display.

    M5Dial.Display.fillRect(0, 0, M5Dial.Display.width()/2 - 20, M5Dial.Display.height()/2 - 20, color_);
    M5Dial.Display.fillRoundRect(0, M5Dial.Display.height()/2 - 25, M5Dial.Display.width()/2 - 5, 20, 10, color_);
    M5Dial.Display.fillRoundRect(M5Dial.Display.width()/2 - 25, 0, 20, M5Dial.Display.height()/2 - 5, 10, color_);

    M5Dial.Display.fillRect(0, M5Dial.Display.height()/2 + 20, M5Dial.Display.width()/2 - 20, M5Dial.Display.height()/2 - 20, color_);
    M5Dial.Display.fillRoundRect(0, M5Dial.Display.height()/2 + 5, M5Dial.Display.width()/2 - 5, 20, 10, color_);
    M5Dial.Display.fillRoundRect(M5Dial.Display.width()/2 - 25, M5Dial.Display.height()/2 + 5, 20, M5Dial.Display.height()/2 - 5, 10, color_);

    M5Dial.Display.fillRect(M5Dial.Display.width()/2 + 20, M5Dial.Display.height()/2 + 20, M5Dial.Display.width()/2 - 20, M5Dial.Display.height()/2 - 20, color_);
    M5Dial.Display.fillRoundRect(M5Dial.Display.width()/2 + 5, M5Dial.Display.height()/2 + 5, M5Dial.Display.width()/2 - 5, 20, 10, color_);
    M5Dial.Display.fillRoundRect(M5Dial.Display.width()/2 + 5, M5Dial.Display.height()/2 + 5, 20, M5Dial.Display.height()/2 - 5, 10, color_);

    // M5Dial.Display.drawLine(0, M5Dial.Display.height()/2, M5Dial.Display.width(), M5Dial.Display.height()/2, WHITE);
    // M5Dial.Display.drawLine(M5Dial.Display.width()/2, 0, M5Dial.Display.width()/2, M5Dial.Display.height(), WHITE);

    //M5Dial.Display.drawBitmap(38, 28, 60, 60, TEST);
    //M5Dial.Display.drawJpgFile()
    //M5Dial.Display.drawPngFile(temperature_picture_, "/Temperature.png",0,0);
    M5Dial.Display.drawPng(&temperature_picture_, 38, 38, 100, 100);
    M5Dial.Display.drawPng(&play_picture_, 38, 141, 100, 100);
    M5Dial.Display.drawPng(&setup_picture_, 141, 141, 100, 100);

    M5Dial.Display.drawString("MBC", 172, 68);
}

void MBController::selectAnimation(byte btn)
{
    switch (btn)
    {
        case 1:

            M5Dial.Display.fillRoundRect(0, M5Dial.Display.height()/2 - 20, M5Dial.Display.width()/2, 20, 10, color_);
            M5Dial.Display.fillRoundRect(M5Dial.Display.width()/2 - 20, 0, 20, M5Dial.Display.height()/2, 10, color_);

            M5Dial.Speaker.tone(8000, 20);
            delay(80);

            M5Dial.Display.fillRect(0, M5Dial.Display.height()/2 - 18, M5Dial.Display.width()/2+2, 22, BLACK);
            M5Dial.Display.fillRect(M5Dial.Display.width()/2 - 18, 0, 22, M5Dial.Display.height()/2 - 2, BLACK);

            M5Dial.Display.fillRoundRect(0, M5Dial.Display.height()/2 - 25, M5Dial.Display.width()/2 - 5, 20, 10, color_);
            M5Dial.Display.fillRoundRect(M5Dial.Display.width()/2 - 25, 0, 20, M5Dial.Display.height()/2 - 5, 10, color_);

            // M5Dial.Display.fillRoundRect(0, 0, M5Dial.Display.width()/2 - 5, M5Dial.Display.height()/2 - 5, 10, color_);
            // M5Dial.Display.clearFileStorage();
            // M5Dial.Display.drawPng(&temperature_picture_, 38, 38, 100, 100);
            break;

        case 2:

            M5Dial.Display.fillRoundRect(0, M5Dial.Display.height()/2, M5Dial.Display.width()/2, 20, 10, color_);
            M5Dial.Display.fillRoundRect(M5Dial.Display.width()/2 - 20, M5Dial.Display.height()/2, 20, M5Dial.Display.height()/2, 10, color_);

            M5Dial.Speaker.tone(7000, 20);
            delay(80);

            M5Dial.Display.fillRect(0, M5Dial.Display.height()/2 - 2, M5Dial.Display.width()/2 + 2, 22, BLACK);
            M5Dial.Display.fillRect(M5Dial.Display.width()/2 - 18, M5Dial.Display.height()/2 - 2, 22, M5Dial.Display.height()/2+2, BLACK);

            M5Dial.Display.fillRoundRect(0, M5Dial.Display.height()/2 + 5, M5Dial.Display.width()/2 - 5, 20, 10, color_);
            M5Dial.Display.fillRoundRect(M5Dial.Display.width()/2 - 25, M5Dial.Display.height()/2 + 5, 20, M5Dial.Display.height()/2 - 5, 10, color_);
            break;

        case 3:

            M5Dial.Display.fillRoundRect(M5Dial.Display.width()/2, M5Dial.Display.height()/2, M5Dial.Display.width()/2, 20, 10, color_);
            M5Dial.Display.fillRoundRect(M5Dial.Display.width()/2, M5Dial.Display.height()/2, 20, M5Dial.Display.height()/2, 10, color_);

            M5Dial.Speaker.tone(6000, 20);
            delay(80);

            M5Dial.Display.fillRect(M5Dial.Display.width()/2-2, M5Dial.Display.height()/2-2, M5Dial.Display.width()/2+2, 22, BLACK);
            M5Dial.Display.fillRect(M5Dial.Display.width()/2-2, M5Dial.Display.height()/2-2, 22, M5Dial.Display.height()/2+2, BLACK);

            M5Dial.Display.fillRoundRect(M5Dial.Display.width()/2 + 5, M5Dial.Display.height()/2 + 5, M5Dial.Display.width()/2 - 5, 20, 10, color_);
            M5Dial.Display.fillRoundRect(M5Dial.Display.width()/2 + 5, M5Dial.Display.height()/2 + 5, 20, M5Dial.Display.height()/2 - 5, 10, color_);
            break;

        default:
            M5Dial.Speaker.tone(4000, 20);
            delay(80);
            break;
    }
}
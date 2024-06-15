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
    M5Dial.Display.setTextFont(&fonts::DejaVu12);
    M5Dial.Display.setTextSize(2);
    M5Dial.Display.setBrightness(64);

    SPIFFS.begin(true);

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
    switch (current_menu_)
    {
    case 1:
        newPosition_ = M5Dial.Encoder.read();
        if (newPosition_ - oldPosition_ >= 4) {  // Поворот энкодера
            M5Dial.Speaker.tone(4000, 20);
            setTemp(1);
            oldPosition_ = newPosition_;
        }
        else if (newPosition_ - oldPosition_ <= -4)
        {
            M5Dial.Speaker.tone(8000, 20);
            setTemp(-1);
            oldPosition_ = newPosition_;
        }
        break;
    default:
        break;
    }
    
}

void MBController::checkTouch()
{
    auto t = M5Dial.Touch.getDetail();

    if (prev_state_ != t.state)
    {
        if (state_name_[t.state] == "touch")
        {
            switch(current_menu_)
            {
                case 0:
                    if ((t.x < M5Dial.Display.width()/2 - 5) && (t.y < M5Dial.Display.height()/2 - 5))
                    {
                        selectAnimation(1);
                        update_ = true;
                        current_menu_ = 1;
                    }
                    else if ((t.x < M5Dial.Display.width()/2 - 5) && (t.y > M5Dial.Display.height()/2 + 5))
                    {
                        selectAnimation(2);
                        update_ = true;
                        current_menu_ = 2;
                    }
                    else if ((t.x > M5Dial.Display.width()/2 + 5) && (t.y > M5Dial.Display.height()/2 + 5))
                    {
                        selectAnimation(3);
                        update_ = true;
                        current_menu_ = 3;
                    }
                    else
                    {
                        selectAnimation(0);
                    }
                    break;
                case 1:
                    
                    break;
                default:
                    
                    break;
            }
        }
        prev_state_ = t.state;
    }
}

void MBController::checkButton()
{
    if ((current_menu_ != 0) && (M5Dial.BtnA.pressedFor(1000))) {
        current_menu_ = 0;
        update_ = true;
        M5Dial.Speaker.tone(3000, 20);
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
            case 1:
                drawTempMenu();
                break;
            default:
                current_menu_ = 0;
                break;
        }

        update_ = false;
    }
}

void MBController::drawMainMenu()
{
    M5Dial.Display.fillScreen(BLACK);
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

void MBController::drawTempMenu()
{
    M5Dial.Display.fillScreen(BLACK);
    M5Dial.Display.drawPngFile(SPIFFS, "/Temperature_button.png", 0, 0);
    M5Dial.Display.drawPngFile(SPIFFS, "/Temperature_colorbar.png", 0, 0);
    M5Dial.Display.drawPngFile(SPIFFS, "/Temp_for_temp.png", 20, 120);
    M5Dial.Display.drawPngFile(SPIFFS, "/Cels_for_temp.png", 180, 120);
    M5Dial.Display.drawString(String(temperature_), 120, 120, &fonts::FreeSans24pt7b); //FreeSans24pt7b Orbitron_Light_32
    drawCursor();
}

void MBController::setTemp(byte inc)
{
    byte temp = temperature_+inc;
    if ((temp <= 99) && (temp >= 0))
    {
        temperature_ = temp;
        M5Dial.Display.fillRect(60, 70, 120, 90, BLACK);
        M5Dial.Display.drawString(String(temperature_), 120, 120, &fonts::FreeSans24pt7b);
        drawCursor();
    }
}

void MBController::drawCursor()
{
    M5Dial.Display.fillCircle(90*cos((168 - 156*temperature_/99)*PI/180) + 120, -90*sin((168 - 156*temperature_/99)*PI/180) + 120, 5, WHITE);
    M5Dial.Display.drawPngFile(SPIFFS, "/Temperature_colorbar.png", 0, 0);
    M5Dial.Display.fillCircle(90*cos((168 - 156*temperature_/99)*PI/180) + 120, -90*sin((168 - 156*temperature_/99)*PI/180) + 120, 5, WHITE);
}
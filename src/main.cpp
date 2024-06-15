#include "modbus_controller/MBController.hpp"

MBController MBC = MBController();

void setup()
{
    MBC.setupM5Dial();
}

void loop() 
{
    MBC.updateM5Dial();
    MBC.updateScreen();
    MBC.checkEncoder();
    MBC.checkTouch();
    MBC.checkButton();
}

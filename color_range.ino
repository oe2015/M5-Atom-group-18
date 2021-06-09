#include "M5Atom.h"

int GRB_COLOR_BLUE = 0x0000ff;
int GRB_COLOR_WHITE = 0xffffff;
int GRB_COLOR_YELLOW = 0xffff00;
int GRB_COLOR_ORANGE = 0x59ff00;
int GRB_COLOR_RED = 0x00ff00;

float first = 11;
float second = 21;
float third = 31;
float fourth = 41;

float tempC = 0;
bool IMU6886Flag = false;

void setup() 
{
    M5.begin(true, false, true);
    delay(20);
    
    IMU6886Flag = M5.IMU.Init() == 0;

    if(!IMU6886Flag)
    {
        Serial.println("Error initializing the IMU! :-(");
    }
}

void loop() 
{
    if(IMU6886Flag)
    {
        M5.IMU.getTempData(&tempC);
        Serial.printf(" Temp : %.2f C \r\n", tempC);
        float tempF = tempC * 9 / 5 + 32;
        Serial.printf(" Temp : %.2f F \r\n", tempF);
    
        if(tempC < first)
        {
            fillDisplay(GRB_COLOR_BLUE);
        }
        else if(tempC >= first || tempC < second)
        {
            fillDisplay(GRB_COLOR_WHITE);
        }
        else if(tempC >= second || tempC < third)
        {
            fillDisplay(GRB_COLOR_YELLOW);
        }
        else if(tempC >= third || tempC < fourth)
        {
            fillDisplay(GRB_COLOR_ORANGE);
        }
        else if(tempC >= fourth)
        {
            fillDisplay(GRB_COLOR_RED);
        }
        
        delay(500);
        M5.update();
    }
}

void fillDisplay(int fillColor)
{
    M5.dis.drawpix(0, GRB_COLOR_BLUE);
    M5.dis.drawpix(1, GRB_COLOR_WHITE);
    M5.dis.drawpix(2, GRB_COLOR_YELLOW);
    M5.dis.drawpix(3, GRB_COLOR_ORANGE);
    M5.dis.drawpix(4, GRB_COLOR_RED);
    
    for(int i = 5; i < 25; i++)
    {
        M5.dis.drawpix(i, fillColor);
    }
}

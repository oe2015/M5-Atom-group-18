#include "M5Atom.h"
#include <stdlib.h>

using namespace std;

int WHITE = 0xffffff;
int BLACK = 0x000000;
int RED = 0x00ff00;
int ORANGE = 0x59ff00;
int YELLOW = 0xffff00;
int GREEN = 0xff0000;
int BLUE = 0x0000ff;
int PURPLE = 0x008080;

float first = 11;
float second = 21;
float third = 31;
float fourth = 41;

int activeColor = WHITE;

int colorSelection[] = {BLACK, WHITE};

int modeColors[] = {BLACK, PURPLE};

int black_screen[25] =
    {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0};

int zero[25] =
    {
        0, 0, 1, 1, 0,
        0, 1, 0, 0, 1,
        0, 1, 0, 0, 1,
        0, 1, 0, 0, 1,
        0, 0, 1, 1, 0};

int one[25] =
    {
        0, 0, 1, 0, 0,
        0, 1, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 1, 1, 1, 0};

int two[25] =
    {
        0, 1, 1, 1, 0,
        0, 0, 0, 0, 1,
        0, 0, 1, 1, 0,
        0, 1, 0, 0, 0,
        0, 1, 1, 1, 1};

int three[25] =
    {
        0, 1, 1, 1, 0,
        0, 0, 0, 0, 1,
        0, 0, 1, 1, 0,
        0, 0, 0, 0, 1,
        0, 1, 1, 1, 0};

int four[25] =
    {
        0, 1, 0, 1, 0,
        0, 1, 0, 1, 0,
        0, 1, 1, 1, 1,
        0, 0, 0, 1, 0,
        0, 0, 0, 1, 0};

int five[25] =
    {
        0, 1, 1, 1, 1,
        0, 1, 0, 0, 0,
        0, 1, 1, 1, 0,
        0, 0, 0, 0, 1,
        0, 1, 1, 1, 0};

int six[25] =
    {
        0, 0, 1, 1, 0,
        0, 1, 0, 0, 0,
        0, 1, 1, 1, 0,
        0, 1, 0, 0, 1,
        0, 0, 1, 1, 0};

int seven[25] =
    {
        0, 1, 1, 1, 1,
        0, 0, 0, 1, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0};

int eight[25] =
    {
        0, 0, 1, 1, 0,
        0, 1, 0, 0, 1,
        0, 0, 1, 1, 0,
        0, 1, 0, 0, 1,
        0, 0, 1, 1, 0};

int nine[25] =
    {
        0, 0, 1, 1, 0,
        0, 1, 0, 0, 1,
        0, 0, 1, 1, 1,
        0, 0, 0, 0, 1,
        0, 0, 1, 1, 0};

int dot[25] =
    {
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 0, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 0, 0, 0};

int F[25] =
    {
        1, 0, 1, 1, 1,
        0, 0, 1, 0, 0,
        0, 0, 1, 1, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0};

int C[25] =
    {
        1, 0, 0, 1, 1,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 1, 0, 0,
        0, 0, 0, 1, 1};

float tempC = 0;
bool IMU6886Flag = false;

float accX = 0;
float accY = 0;
float accZ = 0;

float scaledAccX = 0;
float scaledAccY = 0;
float scaledAccZ = 0;
float average = 1;

unsigned int updatedTime = 0;
unsigned int totalTime = 0;

float LOWTOL = 100;
float HIGHTOL = 900;

float tempCavg = 0.0;

float tempData[] = {0.0, 0.0, 0.0, 0.0, 0.0};
float tempSum = 0.0;

int  selectedMode = 1;

int modeselection = 1;

int *showDigit[10] = {zero, one, two, three, four, five, six, seven, eight, nine};

int *currentMode[10] = {zero, one, two, three, four, five};

bool modeChange = false;

bool tiltingOn = true;

char holding[10];

int timeLength = 500;

void setup() {
  M5.begin(true, false, true);
    delay(20);

    IMU6886Flag = M5.IMU.Init() == 0;

}

void fillDisplay(int fillColor)
{
    M5.dis.drawpix(0, BLUE);
    M5.dis.drawpix(1, WHITE);
    M5.dis.drawpix(2, YELLOW);
    M5.dis.drawpix(3, ORANGE);
    M5.dis.drawpix(4, RED);
    
    for(int i = 5; i < 25; i++)
    {
        M5.dis.drawpix(i, fillColor);
    }
}

void FillScreenColor(int fillColor)
{
    for (int i = 0; i < 25; i++)
    {
        M5.dis.drawpix(i, fillColor);
    }
}

void blankScreen()
{
    M5.dis.clear();
    drawArray(black_screen, colorSelection);
    delay(timeLength);
}

void showTemp(String temperature) {
  temperature.toUpperCase();

  int Length = temperature.length();

  for(int i = 0; i < Length; i++) {
    char Character = temperature.charAt(i);

    if (Character == '.')
    {
      blankScreen();
      M5.dis.clear();
      drawArray(dot, colorSelection);
      delay(timeLength);
    }
    else if (Character == '0')
    {
      blankScreen();
      M5.dis.clear();
      drawArray(zero, colorSelection);
      delay(timeLength);
    }
    else if (Character == '1')
    {
      blankScreen();
      M5.dis.clear();
      drawArray(one, colorSelection);
      delay(timeLength);
    }
    else if (Character == '2')
    {
      blankScreen();
      M5.dis.clear();
      drawArray(two, colorSelection);
      delay(timeLength);
    }
    else if (Character == '3')
    {
      blankScreen();
      M5.dis.clear();
      drawArray(three, colorSelection);
      delay(timeLength);
    }
    else if (Character == '4')
    {
      blankScreen();
      M5.dis.clear();
      drawArray(four, colorSelection);
      delay(timeLength);
    }
    else if (Character == '5')
    {
      blankScreen();
      M5.dis.clear();
      drawArray(five, colorSelection);
      delay(timeLength);
    }
    else if (Character == '6')
    {
      blankScreen();
      M5.dis.clear();
      drawArray(six, colorSelection);
      delay(timeLength);
    }
    else if (Character == '7')
    {
      blankScreen();
      M5.dis.clear();
      drawArray(seven, colorSelection);
      delay(timeLength);
    }
    else if (Character == '8')
    {
      blankScreen();
      M5.dis.clear();
      drawArray(eight, colorSelection);
      delay(timeLength);
    }
    else if (Character == '9')
    {
      blankScreen();
      M5.dis.clear();
      drawArray(nine, colorSelection);
      delay(timeLength);
    }
    else if (Character == 'C')
    {
      blankScreen();
      M5.dis.clear();
      drawArray(C, colorSelection);
      delay(timeLength);
    }
    else if (Character == 'F')
    {
      blankScreen();
      M5.dis.clear();
      drawArray(F, colorSelection);
      delay(timeLength);
    }
    else if (Character == ' ')
    {
      blankScreen();
    }
    
  }
}

void ColorRangeFunction(float tempF)
{
    if(tempC < first)
            {
              fillDisplay(BLUE);
            }
            else if(tempC >= first || tempC < second)
            {
              fillDisplay(WHITE);
            }
            else if(tempC >= second || tempC < third)
            {
              fillDisplay(YELLOW);
            }
            else if(tempC >= third || tempC < fourth)
            {
              fillDisplay(ORANGE);
            }
            else if(tempC >= fourth)
            {
              fillDisplay(RED);
            }
}

void GraphFunction()
{
    for (int i = 0; i < 5; i++)
    {
        M5.IMU.getTempData(&tempC);
        tempData[i] = tempC;
    }
    tempSum = 0;
    for (int i = 0; i < 5; i++)
    {
        tempSum += tempData[i];
    }

    float tempCavg = tempSum / 5.00;

    for (int i = 0; i < 5; i++)
    {
        tempData[i] = (tempData[i] - tempCavg) * 100.00;
    }
    for (int i = 0; i < 5; i++)
    {
        tempData[i] = tempData[i] + 2;
    }
    M5.dis.clear();
    M5.dis.drawpix(0, tempData[0], WHITE);
    M5.dis.drawpix(1, tempData[1], WHITE);
    M5.dis.drawpix(2, tempData[2], WHITE);
    M5.dis.drawpix(3, tempData[3], WHITE);
    M5.dis.drawpix(4, tempData[4], WHITE);
    delay(250);
}

void drawArray(int arr[], int colors[]) {
  for(int i=0; i < 25; i++) {
    M5.dis.drawpix(i, colors[arr[i]]);
  }
}

void loop() {

  if(IMU6886Flag) {
    String tempFstr = "";
    String tempCstr = "";
    
    M5.IMU.getTempData(&tempC);
    dtostrf(tempC, 4, 2, holding);
    tempCstr += holding;
    tempCstr += "C";
    float tempF = tempC * 9 / 5 + 32;
    dtostrf(tempF, 4, 2, holding);
    tempFstr += holding;
    tempFstr += "F";

    M5.IMU.getAccelData(&accX, &accY, &accZ);

    scaledAccX = accX * 1000;
    scaledAccY = accY * 1000;
    scaledAccZ = accZ * 1000;

    if (M5.Btn.wasPressed())
      {
        tiltingOn = false;
      }

    if (abs(scaledAccX) < LOWTOL && abs(scaledAccY) < LOWTOL && abs(scaledAccZ) > HIGHTOL && scaledAccZ > 0)
        {
            updatedTime = millis() / 1000.0;

            if (totalTime != updatedTime)
            {
                tempCavg = ((tempCavg * (average - 1)) + tempC) / average;
                average++;
            }

            totalTime = updatedTime;
            drawArray(black_screen, colorSelection);
          
        }

    else if (abs(scaledAccX) < LOWTOL && abs(scaledAccY) < LOWTOL && abs(scaledAccZ) > HIGHTOL && scaledAccZ < 0)
        {
            modeChange = false;

            if (tiltingOn)
            {
                drawArray(currentMode[ selectedMode], modeColors);
            }
            else
            {
                modeselection =  selectedMode;

                if (modeselection == 1)
                {
                    showTemp(tempCstr);
                }
                else if (modeselection == 2)
                {
                    if (tempCavg == 0.0)
                    {
                        tempCavg = tempC;
                    }
                    tempCstr = tempCavg;
                    tempCstr += "C";
                    showTemp(tempCstr);
                }
                else if (modeselection == 3)
                {
                    ColorRangeFunction(tempF);
                }
                else if (modeselection == 4)
                {
                    GraphFunction();
                }
                else if (modeselection == 5)
                {
                    showTemp(tempFstr);
                }
            }
        }

        else if (abs(scaledAccX) > HIGHTOL && abs(scaledAccY) < LOWTOL && abs(scaledAccZ) < LOWTOL && scaledAccX > 0)
        {
            tiltingOn = true;
            if (!modeChange)
            {
                 selectedMode++;
                if ( selectedMode > 5)
                {
                     selectedMode = 1;
                }
                else if ( selectedMode < 1)
                {
                     selectedMode = 5;
                }
            }
            modeChange = true;
            drawArray(currentMode[ selectedMode], modeColors);
        }

        else if (abs(scaledAccX) > HIGHTOL && abs(scaledAccY) < LOWTOL && abs(scaledAccZ) < LOWTOL && scaledAccX < 0)
        {
            tiltingOn = true;
            if (!modeChange)
            {
                selectedMode--;
                if ( selectedMode > 5)
                {
                     selectedMode = 1;
                }
                else if ( selectedMode < 1)
                {
                     selectedMode = 5;
                }
            }
            modeChange = true;
            drawArray(currentMode[selectedMode], modeColors);
        }
    }
    M5.update();
}

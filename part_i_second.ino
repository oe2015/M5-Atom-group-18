#include "M5Atom.h"
#include <FastLED.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Fonts/TomThumb.h>
#include <M5Atom.h>
#include <iostream>
#include <sstream>

uint32_t black_color = 0x000000;
int delay_period = 300;


using namespace std;

#ifndef PSTR

#define PSTR // Make Arduino Due happy

#endif

#define PIN 27

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PIN,

  NEO_MATRIX_TOP    + NEO_MATRIX_RIGHT +

  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,

  NEO_GRB            + NEO_KHZ800);

 

const uint16_t colors[] = {

  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

 int FSM = 0;

 int GRB_COLOR_PURPLE = 0x008080;

 float accX = 0;
 float accY = 0;
 float accZ = 0;

void setup() {
  M5.begin();
  
  M5.IMU.Init();
  
  matrix.begin();

  matrix.setTextWrap(false);

  matrix.setFont(&TomThumb);

  matrix.setBrightness(20);

  matrix.setTextColor(colors[0]);
}

int x = matrix.height();

int pass = 0;
float temp = 0;

void loop()
{
  switch (FSM)
    {
      case 0:
      {
        M5.dis.fillpix(black_color);
           if (M5.Btn.wasPressed())
        {
          Serial.println("dhdbhgh");
          FSM++;
          
        }
        break;
      }        

      case 1:
      {   
        Serial.println("dhdb");
        fillDisplay1(GRB_COLOR_PURPLE);
      
      if (M5.Btn.wasPressed())
        {

          while(FSM == 1) {
          
            string str; // a variable of str data type

            M5.IMU.getTempData(&temp);

            matrix.fillScreen(0);

            matrix.setCursor(x, matrix.height());

            Serial.println(temp);
  
            matrix.print(F("TEMP:"));
  
            matrix.print((temp));
  
            matrix.print(F("C"));

            if(--x < -60) {

              x = matrix.width();

              if(++pass >= 3) pass = 0;

              matrix.setTextColor(colors[pass]);

            }

            matrix.show();

            delay(130);

            M5.IMU.getAccelData(&accX, &accY, &accZ);

            if(accX < -0.6 || accX > 0.6) {
              FSM++;
              break;
            }
            break;
          }
          break;
        }
        break;
       }

      case 2:
      {
        fillDisplay2(GRB_COLOR_PURPLE);
      
      while(FSM==2)
      {
        M5.dis.fillpix(colors[1]); // turn on color
        delay(delay_period);
        M5.dis.fillpix(black_color); //turn off color
        delay(delay_period);
          if (M5.Btn.wasPressed())
        {
          FSM++;
          break;
        }
        break;
      }
      break;    
}

      case 3:
      {
        fillDisplay3(GRB_COLOR_PURPLE);
  
      while(FSM==3) {
 
  if (M5.Btn.wasPressed())
        {
          FSM++;
          break;
        }
 break;
  }
  break;
}



      case 4:
      {

        fillDisplay4(GRB_COLOR_PURPLE);
  
  while(FSM==4) {
  float accX, accY, accZ;
  int x, y;

  M5.IMU.getAccelData(&accX, &accY, &accZ);

  if (accZ < -0.1) 
  {
    M5.dis.fillpix(0xffffff);
    delay(500);
  }
else {
    {
        M5.dis.fillpix(colors[1]); // turn on color
        delay(delay_period);
        M5.dis.fillpix(black_color); //turn off color
        delay(delay_period);
        if (M5.Btn.wasPressed())
        {
          FSM++;
          break;
        }
        break;
      }
      break;
}
  delay(100);
  if (M5.Btn.wasPressed())
        {
          FSM++;
          break;
        }
 break;
  }
  break;
}

case 5:
{

        fillDisplay5(GRB_COLOR_PURPLE);
  
  FSM=0;
  break;
}

}
    //M5.update(); //always have this here

}

void fillDisplay1(int fillColor)
{
    M5.dis.drawpix(2, GRB_COLOR_PURPLE);
    M5.dis.drawpix(6, GRB_COLOR_PURPLE);
    M5.dis.drawpix(7, GRB_COLOR_PURPLE);
    M5.dis.drawpix(12, GRB_COLOR_PURPLE);
    M5.dis.drawpix(17, GRB_COLOR_PURPLE);
    M5.dis.drawpix(21, GRB_COLOR_PURPLE);
    M5.dis.drawpix(22, GRB_COLOR_PURPLE);
    M5.dis.drawpix(23, GRB_COLOR_PURPLE);
}

void fillDisplay2(int fillColor)
{
    M5.dis.drawpix(1, GRB_COLOR_PURPLE);
    M5.dis.drawpix(2, GRB_COLOR_PURPLE);
    M5.dis.drawpix(3, GRB_COLOR_PURPLE);
    M5.dis.drawpix(8, GRB_COLOR_PURPLE);
    M5.dis.drawpix(11, GRB_COLOR_PURPLE);
    M5.dis.drawpix(12, GRB_COLOR_PURPLE);
    M5.dis.drawpix(13, GRB_COLOR_PURPLE);
    M5.dis.drawpix(16, GRB_COLOR_PURPLE);
    M5.dis.drawpix(21, GRB_COLOR_PURPLE);
    M5.dis.drawpix(22, GRB_COLOR_PURPLE);
    M5.dis.drawpix(23, GRB_COLOR_PURPLE);
}

void fillDisplay3(int fillColor)
{
    M5.dis.drawpix(1, GRB_COLOR_PURPLE);
    M5.dis.drawpix(2, GRB_COLOR_PURPLE);
    M5.dis.drawpix(3, GRB_COLOR_PURPLE);
    M5.dis.drawpix(8, GRB_COLOR_PURPLE);
    M5.dis.drawpix(11, GRB_COLOR_PURPLE);
    M5.dis.drawpix(12, GRB_COLOR_PURPLE);
    M5.dis.drawpix(13, GRB_COLOR_PURPLE);
    M5.dis.drawpix(18, GRB_COLOR_PURPLE);
    M5.dis.drawpix(21, GRB_COLOR_PURPLE);
    M5.dis.drawpix(22, GRB_COLOR_PURPLE);
    M5.dis.drawpix(23, GRB_COLOR_PURPLE);
}

void fillDisplay4(int fillColor)
{
    M5.dis.drawpix(1, GRB_COLOR_PURPLE);
    M5.dis.drawpix(3, GRB_COLOR_PURPLE);
    M5.dis.drawpix(6, GRB_COLOR_PURPLE);
    M5.dis.drawpix(8, GRB_COLOR_PURPLE);
    M5.dis.drawpix(11, GRB_COLOR_PURPLE);
    M5.dis.drawpix(12, GRB_COLOR_PURPLE);
    M5.dis.drawpix(13, GRB_COLOR_PURPLE);
    M5.dis.drawpix(18, GRB_COLOR_PURPLE);
    M5.dis.drawpix(23, GRB_COLOR_PURPLE);
}

void fillDisplay5(int fillColor)
{
    M5.dis.drawpix(1, GRB_COLOR_PURPLE);
    M5.dis.drawpix(2, GRB_COLOR_PURPLE);
    M5.dis.drawpix(3, GRB_COLOR_PURPLE);
    M5.dis.drawpix(6, GRB_COLOR_PURPLE);
    M5.dis.drawpix(11, GRB_COLOR_PURPLE);
    M5.dis.drawpix(12, GRB_COLOR_PURPLE);
    M5.dis.drawpix(13, GRB_COLOR_PURPLE);
    M5.dis.drawpix(18, GRB_COLOR_PURPLE);
    M5.dis.drawpix(21, GRB_COLOR_PURPLE);
    M5.dis.drawpix(22, GRB_COLOR_PURPLE);
    M5.dis.drawpix(23, GRB_COLOR_PURPLE);
}

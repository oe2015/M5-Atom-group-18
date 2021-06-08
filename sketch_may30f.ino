#include <Adafruit_GFX.h>

#include <Adafruit_NeoMatrix.h>

#include <Adafruit_NeoPixel.h>

#include <Fonts/TomThumb.h>

#include <M5Atom.h>

#include <iostream>

#include <sstream>

using namespace std;

#ifndef PSTR

#define PSTR // Make Arduino Due happy

#endif

#define PIN 27

#define seconds 5000

 

// MATRIX DECLARATION:

// Parameter 1 = width of NeoPixel matrix

// Parameter 2 = height of matrix

// Parameter 3 = pin number (most are valid)

// Parameter 4 = matrix layout flags, add together as needed:

//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:

//     Position of the FIRST LED in the matrix; pick two, e.g.

//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.

//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal

//     rows or in vertical columns, respectively; pick one or the other.

//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed

//     in the same order, or alternate lines reverse direction; pick one.

//   See example below for these values in action.

// Parameter 5 = pixel type flags, add together as needed:

//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)

//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)

//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)

//   NEO_GRBW    Pixels are wired for GRBW bitstream (RGB+W NeoPixel products)

//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)

 

 

// Example for NeoPixel Shield.  In this application we'd like to use it

// as a 5x8 tall matrix, with the USB port positioned at the top of the

// Arduino.  When held that way, the first pixel is at the top right, and

// lines are arranged in columns, progressive order.  The shield uses

// 800 KHz (v2) pixels that expect GRB color data.


Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PIN,

  NEO_MATRIX_TOP    + NEO_MATRIX_RIGHT +

  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,

  NEO_GRB            + NEO_KHZ800);

 

const uint16_t colors[] = {

  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

 

void setup() 
{

  M5.begin();
  
  M5.IMU.Init();
  
  matrix.begin();

  matrix.setTextWrap(false);

  matrix.setFont(&TomThumb);

  matrix.setBrightness(20);

  matrix.setTextColor(colors[0]);

}

int x   = matrix.height();

int pass = 0;
int sum=0;
int count=1;
int averageTemp;
float temp = 0;

int currentMillis=millis();

void loop() 
{
  string str; // a variable of str data type
  // using the stringstream class to insert an int and
  // extract a string
  
  M5.IMU.getTempData(&temp);

   /* for (int i=0; i<seconds; i++)
  {
    M5.IMU.getTempData(&temp);
    sum = sum + temp;
  } */ 

  sum = sum + temp;

  if (seconds - currentMillis < 0)
  {
    averageTemp = sum / seconds;
  }

  //averageTemp = sum / seconds;
  
  matrix.fillScreen(0);

  matrix.setCursor(x, matrix.height());

  Serial.println(temp);
  
  matrix.print(F("TEMP:"));
  
  matrix.print((temp));
  
  matrix.print(F("C"));

  matrix.print(F("Average Temp:"));

  matrix.print((averageTemp));

  matrix.print(F("C"));

  if(--x < -60) {

    x = matrix.width();

    if(++pass >= 3) pass = 0;

    matrix.setTextColor(colors[pass]);

  }

  matrix.show();

  delay(130);

}

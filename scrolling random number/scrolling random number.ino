#include "M5Atom.h"
#include <FastLED.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Fonts/TomThumb.h>
#include <M5Atom.h>
using namespace std;
#ifndef PSTR
#define PSTR // Make Arduino Due happy
#endif
#define PIN 27
#define seconds 5000


Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PIN,
  NEO_MATRIX_TOP    + NEO_MATRIX_RIGHT +

  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,

  NEO_GRB            + NEO_KHZ800);
  
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };
uint32_t black_color = 0x000000;

void setup() 
{
  M5.begin(true, false, true);
  Serial.begin(115200);
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

int randomNumber;
void loop() 
{
  //matrix.fillScreen(0);
  matrix.setCursor(x, matrix.height());
    randomNumber = random(1, 7);
    matrix.println(randomNumber);
       delay(1000);

       M5.dis.fillpix(0xffffff);
       delay(500);
//    if(--x < -60) {
//    x = matrix.width();
//    if(++pass >= 3) pass = 0;
//    matrix.setTextColor(colors[pass]);
//    } 
  
    matrix.show();
    M5.update();

}

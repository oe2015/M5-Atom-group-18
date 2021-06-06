/**
 * MorseCode.ino
 *
 * By: Mike Klepper
 * Date: 26 April 2020
 *
 * Converts string stored in message into Morse code
 *
 * See blog post on patriot-geek.blogspot.com
 * for instructions.
 */

#include "M5Atom.h"

int GRB_COLOR_WHITE = 0xffffff;
int GRB_COLOR_BLACK = 0x000000;
int GRB_COLOR_RED = 0x00ff00;
int GRB_COLOR_ORANGE = 0xa5ff00;
int GRB_COLOR_YELLOW = 0xffff00;
int GRB_COLOR_GREEN = 0xff0000;
int GRB_COLOR_BLUE = 0x0000ff;
int GRB_COLOR_PURPLE = 0x008080;

int activeColor = GRB_COLOR_RED;

int colorList[] = {GRB_COLOR_BLACK, activeColor};

// Constants used in Farnsworth timing
// See https://morsecode.world/international/timing.html for details
int scale = 200;
int dotDuration = 1 * scale;
int dashDuration = 3 * scale;
int timeBetweenDotsAndDashes = 1 * scale;
int timeBetweenCharacters = 3 * scale;
int spaceDuration = 7 * scale;

String message = F("Trump 2020 Keep America Great");



int dot[25] = 
{
  0,0,0,0,0,
  0,0,0,0,0,
  0,0,1,1,0,
  0,0,1,1,0,
  0,0,0,0,0
};

int dash[25] = 
{
  0,0,0,0,0,
  0,0,0,0,0,
  1,1,1,1,1,
  1,1,1,1,1,
  0,0,0,0,0
};


char* letters[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",    // A-I
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",  // J-R 
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."          // S-Z
};

char* digits[] = {
  "-----", ".----", "..---", "...--", "....-", ".....",             // 0-5
  "-....", "--...", "---..", "----."                                // 6-9
};


void setup() 
{
  M5.begin(true, false, true);
  delay(20);
}


void loop() 
{
  displayMessageInMorseCode(message);
  finalAnimation();
  delay(2000);
}

void displayMessageInMorseCode(String message)
{
  message.toUpperCase();
  
  int msgLength = message.length();

  Serial.println("");

  for(int i = 0; i < msgLength; i++)
  {
    char currentChar = message.charAt(i);
    String morseCodeForCurrentChar;
    Serial.print(currentChar);
    Serial.print(" ");
    
    if(isAlpha(currentChar))
    {
      morseCodeForCurrentChar = letters[currentChar - 65];
      Serial.print(letters[currentChar - 65]);
      Serial.println(" - Alpha");

      displaySingleMorseCodeCharacter(morseCodeForCurrentChar);
    }
    else if(isDigit(currentChar))
    {
      morseCodeForCurrentChar = digits[currentChar - 48];
      Serial.print(digits[currentChar - 48]);
      Serial.println(" - Digit");

      displaySingleMorseCodeCharacter(morseCodeForCurrentChar);
    }
    else if(isSpace(currentChar))
    {
      Serial.println(" - Space");
      delay(spaceDuration);
    }
  }
}

void displaySingleMorseCodeCharacter(String morseCodeCharacter)
{
  int morseCodeLength = morseCodeCharacter.length();

  for(int i = 0; i < morseCodeLength; i++)
  {
    char currentDotOrDash = morseCodeCharacter.charAt(i);
    Serial.println(currentDotOrDash);

    if(currentDotOrDash == '.')
    {
      M5.dis.clear();
      drawArray(dot, colorList);
      delay(dotDuration);
    }
    else
    {
      M5.dis.clear();
      drawArray(dash, colorList);
      delay(dashDuration);
    }

    M5.dis.clear();
    delay(timeBetweenDotsAndDashes);
  }

  delay(timeBetweenCharacters);
  Serial.println("---------------------");
}


void drawArray(int arr[], int colors[])
{
  for(int i = 0; i < 25; i++)
  {
      M5.dis.drawpix(i, colors[arr[i]]);
  }
}

void fillDisplay(int fillColor)
{
  for(int i = 0; i < 25; i++)
  {
      M5.dis.drawpix(i, fillColor);
  }
}

void finalAnimation()
{
  delay(2000);
  
  M5.dis.clear();
  fillDisplay(GRB_COLOR_RED);
  delay(2000);
  fillDisplay(GRB_COLOR_WHITE);
  delay(2000);
  fillDisplay(GRB_COLOR_BLUE);
  delay(2000);
  M5.dis.clear();
}

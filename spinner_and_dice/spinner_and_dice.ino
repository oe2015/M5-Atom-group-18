#include "M5Atom.h"

int WHITE = 0xffffff;
int BLACK = 0x000000;
int RED = 0x00ff00;
int YELLOW = 0xffff00;
int GREEN = 0xff0000;
int BLUE = 0x0000ff;
int PURPLE = 0x008080;

int activeColor = RED;
//int x   = matrix.height();
  
  int pass = 0;
  float temp = 0, accelX=0, accelY=0, accelZ=0;

int colorList[] = {BLACK, activeColor};
int FSM=0;
int one[25] = 
{
  0,0,1,0,0,
  0,1,1,0,0,
  0,0,1,0,0,
  0,0,1,0,0,
  0,1,1,1,0
};

int two[25] = 
{
  0,1,1,1,0,
  0,0,0,0,1,
  0,0,1,1,0,
  0,1,0,0,0,
  0,1,1,1,1
};

int three[25] = 
{
  0,1,1,1,0,
  0,0,0,0,1,
  0,0,1,1,0,
  0,0,0,0,1,
  0,1,1,1,0
};

int four[25] = 
{
  0,1,0,1,0,
  0,1,0,1,0,
  0,1,1,1,1,
  0,0,0,1,0,
  0,0,0,1,0
};

int five[25] = 
{
  0,1,1,1,1,
  0,1,0,0,0,
  0,1,1,1,0,
  0,0,0,0,1,
  0,1,1,1,0
};

int six[25] = 
{
  0,0,1,1,0,
  0,1,0,0,0,
  0,1,1,1,0,
  0,1,0,0,1,
  0,0,1,1,0
};

int arrow[25] =
{
  0,0,1,0,0,
  0,1,1,1,0,
  1,0,1,0,1,
  0,0,1,0,0,
  0,0,1,0,0,
};

  int *displayNumbers[7] = { one, two, three, four, five, six, arrow };

void setup() 
{
  randomSeed(analogRead(0));
  M5.begin(true, false, true);
  M5.IMU.Init();
  delay(20);
}

void loop() 
{  
   switch (FSM)
    {
      case 0:
      {
        M5.IMU.getAccelData(&accelX, &accelY, &accelZ);
       if(accelX<=0 && accelY<=0)
  {
    int numberToShow = random(0, 6);

    Serial.println(numberToShow + 1);
    drawArray2(displayNumbers[numberToShow], colorList);
  }

  
    if (M5.Btn.wasPressed())
        {
          FSM++;
        }
      break;
      }
 

  case 1:
    {
    drawArray2(displayNumbers[6], colorList);

      if (M5.Btn.wasPressed())
        {
          FSM++;
        }
      break;
      }

 case 2:
{
  FSM=0;
  break;
}
    }
  delay(50);
  M5.update();
}

void drawArray2(int arr[], int colors[])
{
  for(int i = 0; i < 25; i++)
  {
      M5.dis.drawpix(i, colors[arr[i]]);
  }
}

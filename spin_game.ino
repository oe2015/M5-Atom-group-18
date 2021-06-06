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
  
  
  
  Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(5, 5, PIN,
  
    NEO_MATRIX_TOP    + NEO_MATRIX_RIGHT +
  
    NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  
    NEO_GRB            + NEO_KHZ800);
  
   
  
  const uint16_t colors[] = {
  
    matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };
  
   
  
  void setup() 
  {
  
    M5.begin(true,false,true);
    
    M5.IMU.Init();
    
    matrix.begin();
  
    matrix.setTextWrap(false);
  
    matrix.setFont(&TomThumb);
  
    matrix.setBrightness(20);
  
    matrix.setTextColor(colors[0]);
  
  }
  
  int x   = matrix.height();
  
  int pass = 0;
  float temp = 0;
  int FSM=0;
  float Xcoord, Ycoord, Zcoord;
  int random_no;
 float accelX,accelY,accelZ;
  

  
  void loop() 
  {
   
  switch (FSM)
  
    { 
//      case 0:
////
////      random_no= random(1,7);
////      matrix.print(random_no);
////      delay(1000);
//
//      M5.dis.fillpix(0xffffff);
////      delay(1000);
//      
////   M5.IMU.getGyroData(&Xcoord,&Ycoord,&Zcoord);
////    Serial.print("x: ");
////    Serial.println("X:");
////  Serial.println(Xcoord);
////  Serial.print("y: ");
////  Serial.println(Ycoord);
////  Serial.print("z: ");
////  Serial.println(Zcoord);


  case 0: 

     M5.IMU.getAccelData(&accelX, &accelY, &accelZ);
//     Serial.print("x: ");
   Serial.println("X:");
  Serial.println(accelX);

  if(accelX>0.40){

//    M5.dis.fillpix(0x000000);
    Serial.println("right");
//    delay(2000);
//    
  }

  else if (accelX<-0.40){
    M5.dis.fillpix(0x00ff00);
//    Serial.println("left");
//    delay(2000);
  }

//  else 
//    M5.dis.fillpix(0xff0000);
//    
//     delay(2000);
     

    }


  
  matrix.show();

  delay(1000);

}

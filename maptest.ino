#include "LedControl.h"
//Set up LED hardware
const int DISPLAYS = 1;
const int DATA_PIN = 11;
const int CLK_PIN  = 13;
const int CS_PIN   = 10;

byte gameMap[8] = {
  B11111111,
  B10111101,
  B11000011,
  B11000011,
  B11000011,
  B11000011,
  B10111101,
  B11111111
};

// connection to MAX7219 (data, clik, load, #of dispplay)
LedControl lc = LedControl(DATA_PIN,CLK_PIN,CS_PIN,DISPLAYS);

void drawMap(byte levelMap[] ){
  for( int i = 0; i < 8; i ++){
    lc.setRow(0,i,levelMap[i]);
  }
}

void setup() {
  ////wake up the MAX72XX from power-saving mode
  for(int i = 0; i < DISPLAYS; i++){
    lc.shutdown(i,false);
    //set a medium brightness for the Leds
    lc.setIntensity(i, 1);
    //Switch all Leds on the display off.
    lc.clearDisplay(i);
  }
  drawMap(gameMap);
  randomSeed(analogRead(0));
  pinMode(5,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(5)==0){
    setRandomMap();
  }
  redraw();
  delay(100);
}

void setRandomMap(){
  for(int i=0; i < sizeof(gameMap); i++){
    gameMap[i]= (byte) random(0,255);
  }
}

//Redraw the scene
void redraw(){
  lc.clearDisplay(0);
  drawMap(gameMap);
}

/*
   MapRenderTest
   This is the map rendering test for experience referencing arrays and parsing values as bytes
   1/2/2021 - Author: Jeremiah Garmatter
   Version 0.4
*/

//todo: load map function that takes in an array, array length and height and updates the LEVEL variable. MAP_Length and MAP_height
//todo: decide if we need to keep all of setlevelview and updatelevelview

//includes
#include "LedControl.h"

//LedControl interfaces with the MAX7219
//Parameters: int data_pin, int clock_pin, int load(CS)_pin, int displays
LedControl lc = LedControl(11, 13, 10, 1);

/*================================ Constants =================================*/
//const boolean LEVEL_FULL[16][16] = {
//  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
//};

//Array Limits
const int MAP_LENGTH    = 18;
const int MAP_HEIGHT    = 16;
const int SCREEN_LENGTH = 8;
const int SCREEN_HEIGHT = 8;

const boolean LEVEL[MAP_HEIGHT][MAP_LENGTH] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1},
  {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1},
  {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
  {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
  {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
  {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0},
  {1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0},
  {1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1},
  {1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
  {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
  {1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0},
  {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
  {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1},
  {1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1}
};

//Direction
const int UP    = 0;
const int DOWN  = 1;
const int LEFT  = 2;
const int RIGHT = 3;
const int NONE  = 4;

//Buttons
const int BUTTON_LEFT  = 2;
const int BUTTON_RIGHT = 3;
const int BUTTON_UP    = 4;
const int BUTTON_DOWN  = 5;

/*=========================== Global Variables ===============================*/
//The "eyes" of the player (this will be displayed on the matrix), it is simply an 8x8 section of the total LEVEL array
boolean levelView[SCREEN_HEIGHT][SCREEN_LENGTH];
//The top left corner of the view's coordinates
int levelViewX = 0;
int levelViewY = 0;
//Movement direction
int direction = NONE;

/*========================== Function Prototypes =============================*/
//This is mainly for the convenience of default parameters
//Not all functions are up here
void setLevelView(int startx = levelViewX, int starty = levelViewY);
void drawLevelView(int displayAddr = 0);

/*=============================== Setup ======================================*/
void setup() {
  // put your setup code here, to run once:
  //Wake up the display (address/display #(0-15), true/false)
  //set the LED brightness (address/display #(0-15), brightness #(0-15))
  //Turn off the LEDs (address/display #(0-15))
  lc.shutdown(0, false);
  lc.setIntensity(0, 8);
  lc.clearDisplay(0);

  Serial.begin(115200);
  Serial.print("\n");
  Serial.println("#=====  Starting Map Render Test  =====#");

  pinMode(BUTTON_LEFT , INPUT);
  pinMode(BUTTON_RIGHT, INPUT);
  pinMode(BUTTON_UP   , INPUT);
  pinMode(BUTTON_DOWN , INPUT);
  //Instantiate the levelView array and draw it to the display
  setLevelView();
  drawLevelView();
  delay(200);
}

/*=========================== Running Loop =====================================*/
void loop() {
  // put your main code here, to run repeatedly:
  if (checkButtons()) {
    updateLevelViewCoordinates();
    setLevelView();
    drawLevelView();
    delay(200);
  }
}

/*============================= Functions ====================================*/
//This will fill the levelView array with an 8x8 section of data from the LEVEL array
//startx and starty are the top left coordinates of the LEVEL Array
void setLevelView(int startx, int starty) {
  //from starty to starty + screen height
  //set levelview x through screen length to LEVEL[startx, startx+screen length]
  //continue to next y value

  if (isValidView(startx, starty)) {
    levelViewX = startx;
    levelViewY = starty;
  }

  Serial.println("Filling view array...");
  for ( int row = levelViewY, viewRow = 0; row < (levelViewY + SCREEN_HEIGHT); row++, viewRow++ ) {
    //Serial.println((String)"\nY coord: "+row+" View row: "+viewRow);
    for ( int column = levelViewX, viewColumn = 0; column < (levelViewX + SCREEN_LENGTH); column++, viewColumn++ ) {
      levelView[viewRow][viewColumn] = LEVEL[row][column];
      //Serial.print((String)"X coord: "+column+ " View column: "+viewColumn+" ");
    }
  }
  //Serial.println((String)"\nStarting x: "+levelViewX+" y: "+levelViewY);
  Serial.println("Done filling array");
}

//This will light up pixels on the display row-by-row
void drawLevelView(int displayAddr) {
  //Run through each value of levelView[][], converting rows to bytes
  //Once finished, draw with lc.setRow
  Serial.println("\nDrawing rows...");
  byte rowByte = 0;
  for ( int row = 0; row < SCREEN_HEIGHT; row++ ) {
    //Since we are parsing as array, 1-8 won't work, instead subtract 1 to get indexes 0-7
    for ( int column = SCREEN_LENGTH - 1; column >= 0; column-- ) {
      rowByte = rowByte | (levelView[row][column] << ((SCREEN_LENGTH - 1) - column));
    }
    lc.setRow(displayAddr, row, rowByte);
    rowByte = 0;
  }
  Serial.println("Done drawing");
}

//checks if a button is pressed, if so, update direction and return true,
//otherwise, return false
boolean checkButtons() {
  if (digitalRead(BUTTON_LEFT) == 0)
    direction = LEFT;
  else if (digitalRead(BUTTON_RIGHT) == 0)
    direction = RIGHT;
  else if (digitalRead(BUTTON_UP) == 0)
    direction = UP;
  else if (digitalRead(BUTTON_DOWN) == 0)
    direction = DOWN;
  else return false;
  return true;
}

//Changes the viewed section of the map
void updateLevelViewCoordinates() {
  int nextViewX = levelViewX, nextViewY = levelViewY;
  switch (direction) {
    case UP:    nextViewY = levelViewY - 1; break;
    case DOWN:  nextViewY = levelViewY + 1; break;
    case LEFT:  nextViewX = levelViewX - 1; break;
    case RIGHT: nextViewX = levelViewX + 1; break;
    case NONE:  break;
  }
  if ( isValidView(nextViewX, nextViewY) ) {
    levelViewX = nextViewX;
    levelViewY = nextViewY;
  }
  //Stop moving
  direction = NONE;
}

boolean isValidView(int viewx, int viewy) {
  if (viewx >= 0 && viewx + SCREEN_LENGTH <= MAP_LENGTH &&
      viewy >= 0 && viewy + SCREEN_HEIGHT <= MAP_HEIGHT) {
    return true;
  }
  return false;
}

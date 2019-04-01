#include <iostream>
#include <string.h>
#include <SDL2/SDL.h>
#include <fstream>  //debug purposes
#include "gbtiming.cpp"
using namespace std;

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 224;
const int MAX_NUM_TILES = 385;    //how many tiles fit in vram

const int LCD_WIDTH = 160;
const int LCD_HEIGHT = 144;

const int CPU_CLOCK = 4194300;
const float LCD_FRAMERATE = 59.7;

const int CYCLES_PER_SECOND = CPU_CLOCK / LCD_FRAMERATE;


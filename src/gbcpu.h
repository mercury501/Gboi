#include <iostream>
#include <string.h>
#include <SDL2/SDL.h>

#include <fstream>  //debug purposes

using namespace std;

const int VRAM_VIEWER_POS_X = 30;
const int VRAM_VIEWER_POS_Y = 50;

const int GBOI_POS_X = 30;
const int GBOI_POS_Y = 350;

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 224;
const int MAX_NUM_TILES = 385;    //how many tiles fit in vram

const int LCD_WIDTH = 160;
const int LCD_HEIGHT = 144;

const int TIMA = 0xff05;          // timer counts up at TMC hz
const int TMA = 0xff06;           // timer modulator, reset value for TIMA
const int TMC = 0xff07;           // 3 bit bit 2 is enabled 1 or disabled 0, 4096, 262144, 65536, 16384

const int CPU_CLOCK = 4194300;
const float LCD_FRAMERATE = 59.7;

const int CYCLES_PER_SECOND = CPU_CLOCK / LCD_FRAMERATE;


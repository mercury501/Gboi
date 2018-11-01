
#include "pch.h"
#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include "gbcpu.h"
#include "include/SDL.h"

using namespace std;



int main(int argc, char* argv[])
{
	gbcpu cpu;

	int w = 512;
	int h = 512;

	SDL_Window* window = NULL;

	bool loaded = 0;


	cpu.initialize();

	if (argc == 2) {
		while (!loaded) {

			loaded = cpu.load_bin_char(argv[1]);
			if (!loaded)
				cout << endl << "Insert a valid file path" << endl;

		}
	}

	else
	{

		while (!loaded) {
			cout << "Insert rom file path:  ";
			string filepath;
			cin >> filepath;

			loaded = cpu.load_binary(filepath);
			if (!loaded)
				cout << endl << "Insert a valid file path" << endl;
		}

	}

	//setup graphics
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow(
		"Gbotto Emulator by TDS",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		w, h, SDL_WINDOW_SHOWN
	);

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_RenderSetLogicalSize(renderer, w, h);

	SDL_Texture* sdlTexture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		256, 256); //screen pixel size

	while (1) {

		cpu.cycle();

	}

	return 0;
}


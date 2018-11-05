#include "include/SDL.h"

using namespace std;

const int SCREEN_WIDTH = 256;
const int SCREEN_HEIGHT = 224;



class gbcpu {
private:


	uint16_t gfx[SCREEN_WIDTH][SCREEN_HEIGHT][3];

	SDL_Window* window = NULL;
	SDL_Texture* texture = NULL;
	SDL_Renderer* renderer = NULL;

	uint8_t memory[0xffff];

	/*Flag register (F)bits:

	7	6	5	4	3	2	1	0
	Z	N	H	C	0	0	0	0

		Z - Zero Flag
		N - Subtract Flag
		H - Half Carry Flag
		C - Carry Flag
		0 - Not used, always zero
		*/

	uint16_t pc;
	uint16_t sp;
	uint32_t rhl;



	uint16_t ra, rb, rc, rd, re; //registers
	uint16_t sr;

	/*  Interrupt Enable Register
		-------------------------- - FFFF
		Internal RAM
		-------------------------- - FF80
		Empty but unusable for I / O
		-------------------------- - FF4C
		I / O ports
		-------------------------- - FF00
		Empty but unusable for I / O
		-------------------------- - FEA0
		Sprite Attrib Memory(OAM)
		-------------------------- - FE00
		Echo of 8kB Internal RAM
		-------------------------- - E000
		8kB Internal RAM
		-------------------------- - C000
		8kB switchable RAM bank
		-------------------------- - A000
		8kB Video RAM
		-------------------------- - 8000 --
		16kB switchable ROM bank |
		-------------------------- - 4000 |= 32kB Cartrigbe
		16kB ROM bank #0 |
		-------------------------- - 0000 --
		E000- FE00
			==
		C000 DE00


		*/

	uint8_t opcode;
	uint16_t operand[2];

	uint16_t bbaa() {

		return (operand[1] << 8) + operand[0];

	}

	/*uint16_t aabb()  {    

		return (operand[1] << 8) + operand[0];

	}*/  

	bool r_sr(char flg) {  //read status register
		switch (flg) {
		case 'c':
			return (sr & 0b00010000);

		case 'h':
			return (sr & 0b00100000);

		case 'n':
			return (sr & 0b01000000);

		case 'z':
			return (sr & 0b1000000);

		}
	}

	void w_sr(char flg, bool value) {  //write status register
		
		switch (flg) {
		case 'c':
			if (value) {
				sr = sr | 0b00010000;
			}
			else {
				sr = sr & 0b11101111;
			}
			break;

		case 'h':
			if (value) {
				sr = sr | 0b00100000;
			}
			else {
				sr = sr & 0b11011111;
			}
			break;

		case 'n':
			if (value) {
				sr = sr | 0b01000000;
			}
			else {
				sr = sr & 0b10111111;
			}
			break;

		case 'z':
			if (value) {
				sr = sr | 0b10000000;
			}
			else {
				sr = sr & 0b01111111;
			}
			break;

		}
		return;
	}

	void check_carry(uint16_t &value) {   
		if (value > 0xff) {
			w_sr('c', 1);
			value = value & 0x00ff;
			return;
		}
		else
			w_sr('c', 0);
		return;
	}

	void check_carry32(uint32_t &value) {
		if (value > 0xffff) {
			w_sr('c', 1);
			value = value & 0x00ffff;
			return;
		}
		else
			w_sr('c', 0);
		return;
	}

	void check_hcarry(uint16_t result, uint16_t anyoperand) {
		if ((result & 0xf) < (anyoperand & 0xf) || (result & 0xff) < (anyoperand & 0xff))
			w_sr('h', 1);
		else
			w_sr('h', 0);
		return;
	}

	void check_zero(uint16_t value) {
		if (value == 0) {
			w_sr('z', 1);
			return;
		}
		else
			w_sr('z', 0);
		return;
	}

	void set_subtract(bool value) {
		w_sr('s', value);
		return;
	}


	uint16_t r_rde() {
		uint16_t temp = 0;
		temp += re;
		temp += (rd << 8);   //TODO test double register action

		return temp;
	}

	void w_rde(uint16_t input) {
		re = input;
		rd = input >> 8;
		return;
	}

	uint16_t r_rbc() {
		uint16_t temp = 0;
		temp += rc;
		temp += (rb << 8);

		return temp;
	}

	void w_rbc(uint16_t input) {
		rc = input;
		rb = input >> 8;
		return;
	}

	uint16_t r_raf() {
		uint16_t temp = 0;
		temp += sr;
		temp += (ra << 8);

		return temp;
	}

	void w_raf(uint16_t input) {
		sr = input;
		ra = input >> 8;
		return;
	}


	void push8(uint8_t datos) { //TODO validate push pop
		memory[sp] = datos;
		sp--;
		return;
	}

	uint8_t pop8() {
		sp++;
		return memory[sp];
	}

	void push16(uint16_t dat) {
		push8(dat);
		push8(dat >> 8);
		return;
	}

	uint16_t pop16() {
		uint16_t temp = 0;
		temp = pop8();
		temp = temp << 8;
		temp += pop8();
		return temp;
	}




public:



	bool load_binary(string path) { //load rom starting at 0x200

		char cpath[200];
		strcpy_s(cpath, path.c_str());

		return load_bin_char(cpath);

	}

	bool load_bin_char(char strong[]) {
		unsigned char buffer[0x8100];

		FILE* rom = fopen(strong, "rb");

		fseek(rom, 0, SEEK_END); //seek the end of rom
		long rom_size = ftell(rom); //store the position in the file stream as its size
		rewind(rom); //rewind the rom like a VHS

		fread(buffer, rom_size, 1, rom);

		//load buffer in memory
		if (rom_size > 0x8000) {
			cout << endl << "Rom too big" << endl;
			return 0;
		}

		for (int i = 0; i < rom_size; i++)
			memory[i] = buffer[i];

		fclose(rom);
		//free(buffer);

		return 1;
	}

	void initialize() {

		for (int i = 0; i < 0x8100; i++)
			memory[i] = 0;

		soft_reset();

		return;

	}

	void soft_reset() {
		ra = 0;
		rb = 0;
		rc = 0;
		rd = 0;
		re = 0;  //registers
		rhl = 0;

		sr = 0; //status register

		sp = 0xdfff;
		pc = 0x100;

		return;

	}



	void cycle() {  //fetch, execute
		opcode = memory[pc];
		operand[0] = memory[pc + 1];
		operand[1] = memory[pc + 2];

		switch (opcode) {

		case 0x00:   //NOP
			pc += 1;
			break;

		case 0x01:  //LD bc bbaa
			w_rbc(bbaa());
			pc += 1;
			break;
			
		case 0x05: //05 DECrement B
			rb--;
			pc += 1;
			break;

		case 0x06: { //06 xx LD B,$xx
			rb = operand[0];
			pc += 2;
			break; }

		case 0x0e:   //0E xx LD C,$xx
			rc = operand[0];
			pc += 2;
			break;
		
		case 0x14:  //increment D
			rd++;
			pc += 1;
			break;

		case 0x15:  //decrement D
			rd--;
			pc += 1;
			break;

		case 0x16:  //load xx into D
			rd = operand[0];
			pc += 2;
			break;

		case 0x19:  //add de to hl
			rhl += r_rde();
			check_carry32(rhl);
			check_zero(rhl);
			set_subtract(0);
			check_hcarry(rhl, r_rde());
			pc += 1;
			break;

		case 0x1e:   //LD E $xx 
			re = operand[0];
			pc += 2;
			break;

		case 0x1f: {//Rotate Right A
			bool temp = r_sr('c');
			w_sr('c', bool((ra & 0x80) >> 8));
			ra = (ra * 2) + temp;
			pc += 1;
			break;
		}

		case 0x20: { //20 xx JR NZ,$xx
			if (!r_sr('z')) {
				if (operand[0] > 127)
					pc += operand[0];
				else
					pc -= operand[0];
			}
			else
				pc += 1;
			break;
		}

		case 0x21:   //21 bb aa LD HL,$aabb
			rhl = aabb();
			pc += 3;
			break;

		case 0x23:  //increment hl
			rhl++;
			pc += 1;
			break;

		case 0x32:  //32 LD (HL)-,A
			memory[rhl] = ra;
			rhl--;
			pc += 1;
			break;

		case 0x56: //copy (hl) to d
			rd = memory[rhl];
			pc += 1;
			break;

		case 0x5e:  //copy value pointed at by hl in e
			re = memory[rhl];
			pc += 1;
			break;

		case 0x5f: //copy a to e
			re = ra;
			pc += 1;
			break;
					
		case 0x7a:  //copy d to a
			ra = rd;
			pc += 1;
			break;

		case 0x82:  //add d to a
			ra += rd;
			check_carry(ra);
			check_zero(ra);
			set_subtract(0);
			check_hcarry(ra, rd);
			pc += 1;
			break;

		case 0x87: {  //double a
			uint16_t temp = ra;
			ra += ra;
			check_carry(ra);
			check_zero(ra);
			set_subtract(0);
			check_hcarry(ra, temp);
			pc += 1;
			break;
		}

		case 0x89: {  //adc A c,  add c and carry flag to A
			ra += rc + (r_sr('c'));
			check_carry(ra);
			check_zero(ra);
			set_subtract(0);
			check_hcarry(ra, rc);
			pc += 1;
			break;
		}

		case 0x8f: { //add a and fc to a
			uint16_t temp = r_sr('c') + ra;
			ra = (ra * 2) + r_sr('c');
			check_carry(ra);
			check_zero(ra);
			set_subtract(0);
			check_hcarry(ra, temp);
			pc += 1;
			break;
		}

		case 0xaf:  //XOR A A
			ra = 0x0000;
			pc += 1;
			break;

		case 0xc3:   //JMP bb aa
			pc = bbaa();
			break;

		case 0xc5: //push bc
			push16(r_rbc());
			pc += 1;
			break;

		case 0xcd: //call subroutine at bbaa
			push16(pc);
			pc = bbaa();
			break;

		case 0xcf: //call subroutine at 08h
			push16(pc);
			pc = 0x08;
			break;

		case 0xd5: // push de
			push16(r_rde());
			pc += 1;
			break;

		case 0xdf:   // call subroutine at 0018h
			push16(pc);
			pc = 0x0180;
			break;

		case 0xe1:  //pop into hl
			rhl = pop16();
			pc += 1;
			break;

		case 0xe5: //push hl
			push16(rhl);
			pc += 1;
			break;

		case 0xe9:  //jmp (hl)
			pc = memory[rhl];
			break;

		case 0xef:  //call sub at 28h
			push16(pc);
			pc = 0x28;
			break;

		case 0xf0: { //ld a from (ff00h + xx)
			ra = memory[(0xff00 + operand[0])];
			pc += 2;
			break;
		}

		case 0xf5: {// push af
			push16(r_raf());
			pc += 1;
			break;
		}

		case 0xff: {  //FF RST $38
			pc = 0x38;
			break;
		}

		default: {
			cout << "unknown opcode," << endl << "pc: 0x" << hex << (int)pc << "\nopcode: 0x" << hex << (int)opcode;
			cout << endl;
			break;
		}
		};

		return;
	}


	void ginit() {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return;
		}
		window = SDL_CreateWindow("C8emu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			return;
		}
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == NULL) {
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return;
		}
		else {
			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		}

	}

	void drawDisplay() {

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(renderer);

		int w = SCREEN_WIDTH / 64;
		int h = SCREEN_HEIGHT / 32;

		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++) {
				//TODO refine graphics
				SDL_Rect fillRect = { x*w, y*h, w, h };
				SDL_SetRenderDrawColor(renderer, gfx[x][y][0], gfx[x][y][1], gfx[x][y][2], 0xff);
				SDL_RenderFillRect(renderer, &fillRect);

			}
		}
		SDL_RenderPresent(renderer);

	}

};


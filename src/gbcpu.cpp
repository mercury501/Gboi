#include "gbcpu.h"


class gbcpu {
private:
	

	uint8_t vram_init[0x1a0] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0xF0,0x00,0xFC,0x00,0xFC,0x00,0xFC,0x00,0xFC,0x00,0xF3,0x00,0xF3,0x00,0x3C,0x00,0x3C,0x00,0x3C,0x00,0x3C,0x00,0x3C,0x00,0x3C,0x00,0x3C,0x00,0x3C,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0xF3,0x00,0xF3,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xCF,0x00,0xCF,0x00,0x00,0x00,0x00,0x00,0x0F,0x00,0x0F,0x00,0x3F,0x00,0x3F,0x00,0x0F,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0xC0,0x00,0x0F,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xF3,0x00,0xF3,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC0,0x00,0xC0,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0x03,0x00,0xFF,0x00,0xFF,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC0,0x00,0xC3,0x00,0xC3,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x00,0xFC,0x00,0xF3,0x00,0xF3,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0x3C,0x00,0x3C,0x00,0xFC,0x00,0xFC,0x00,0xFC,0x00,0xFC,0x00,0x3C,0x00,0x3C,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0x3C,0x00,0x3C,0x00,0x3F,0x00,0x3F,0x00,0x3C,0x00,0x3C,0x00,0x0F,0x00,0x0F,0x00,0x3C,0x00,0x3C,0x00,0xFC,0x00,0xFC,0x00,0x00,0x00,0x00,0x00,0xFC,0x00,0xFC,0x00,0xFC,0x00,0xFC,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF0,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF3,0x00,0xF0,0x00,0xF0,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xC3,0x00,0xFF,0x00,0xFF,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0xCF,0x00,0xC3,0x00,0xC3,0x00,0x0F,0x00,0x0F,0x00,0x0F,0x00,0x0F,0x00,0x0F,0x00,0x0F,0x00,0xFC,0x00,0xFC,0x00,0x3C,0x00,0x42,0x00,0xB9,0x00,0xA5,0x00,0xB9,0x00,0xA5,0x00,0x42,0x00,0x3C};  //N logo?
	uint8_t gfx[MAX_NUM_TILES * 8][8];

	/*
	8000-87FF  tile set 1 0-127
	8800-8fff  tile set 1 128-255          in total 384 tiles.
		       tile set 0 -1- -128
	9000-97FF  tile set 0  0-127
	9800-9BFF  tile map 0
	9C00-9FFF  tile map 1
	*/
	SDL_Window* Gboi = NULL;
    SDL_Window* vram_viewer = NULL;

	//SDL_Texture* texture = NULL;

	SDL_Renderer* Gboi_renderer = NULL;
    SDL_Renderer* vram_renderer = NULL;
	
	/*Flag register (F)bits:

	7	6	5	4	3	2	1	0
	Z	N	H	C	0	0	0	0

		Z - Zero Flag
		N - Subtract Flag
		H - Half Carry Flag
		C - Carry Flag
		0 - Not used, always zero
	*/

	uint8_t memory[0xffff];

	uint16_t pc;
	uint16_t sp;
	uint32_t rhl;

	bool ie;  // interrupt enable flag

	uint16_t ra, rb, rc, rd, re; //registers
	uint16_t sr;

	uint8_t IME, IF;  //Interrupt Master Enable, Interrupt Flags

	//DEBUG
	bool debugging = false;
	int state_number = 0;
	uint16_t current_pc = 0;
	int foundonce = 0;
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

	int cycle_count;
	int old_cycle_count;
	int last_frame_cycle_count = 0;

	uint32_t frame_start_time;

	

	void wait_next_frame(uint32_t frame_end){  //should already account for instruction time
        	    while (SDL_GetTicks() < frame_end)
					SDL_Delay(5);
		   return;
 	}


	uint16_t bbaa() {
		return (operand[1] << 8) + operand[0];
	}

	bool r_sr(char flg) {  //read status register
		switch (flg) {
		case 'c':
			return (sr & 0b00010000);

		case 'h':
			return (sr & 0b00100000);

		case 'n':
			return (sr & 0b01000000);

		case 'z':
			return (sr & 0b10000000);

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
/*
	void check_hcarry(uint16_t result, uint16_t anyoperand) {
		if ((((result & 0xf) + (anyoperand & 0xf)) & 0x10 ) > 0 )
			w_sr('h', 1);
		else
			w_sr('h', 0);
		return;
	}

	void check_hcarry32(uint32_t result, uint32_t anyoperand) { 
		if ((result & 0xff) < (anyoperand & 0xff) || (result & 0xffff) < (anyoperand & 0xffff))
			w_sr('h', 1);
		else
			w_sr('h', 0);
		return;
	} */

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
		w_sr('n', value);
		return;
	}

	bool read_carry() {
		return r_sr('c');
	}

	bool read_hcarry() {
		return r_sr('h');
	}

	bool read_subtract() {
		return r_sr('n');
	}

	bool read_zero() {
		return r_sr('z');
	}

	void set_carry(bool value) {
		w_sr('c', value);
		return;
	}

	void set_hcarry(bool value) {
		w_sr('h', value);
		return;
	}

	void set_zero(bool value) {
		w_sr('z', value);
		return;
	}

	uint16_t r_rde() {
		uint16_t temp = 0;
		temp += re;
		temp += (rd << 8);   
		return temp;
	}

	void w_rde(uint16_t input) {
		re = input & 0xff;
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
		rc = input & 0xff;
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
		sr = input & 0xff;
		ra = input >> 8;
		return;
	}


	void push8(uint8_t datos) { 
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

	void wr_mem(uint16_t address, uint8_t data){
		switch(address){
			/*case 0x9938:  //DEBUG
				memory[address] = data;
				if (data == 0x2f)
				cout<<endl;
				break; */
			
			case 0xff44: //LY write resets counter
				memory[address] = 0;
				break;

			case 0xff46: //DMA
				data *= 0x100; //ra = address / 100h
				//TODO DMA
				break;

			case 0xff80: //tetris patch?
				break;

			default:{
				memory[address] = data;
				break;
			}
		};
		return;
	}

	void dump_memory(){ //DEBUG
		ofstream outfile ("memory.dump");
		for (int i = 0; i < 0xffff; i++){
		outfile << memory[i];
		}
		outfile.close();

		return;
	}

	void print_trace_of_sorts(){  //DEBUG
		for (int i = 0; i < 10000; i++)
			cout<< lastpc[i] <<" ,";
		return;
	}


	/*	bit 2 enable (1)
		00: 4096 Hz 
		01: 262144 Hz 
		10: 65536 Hz 
		11: 16384 Hz
	*/
	
/*  TODO timers, need more resolution than SDL_GetTicks()
	void timer_routine(){
		if (memory[TMC] > 0b100){
			uint8_t temp = memory[TMC] & 0b11;

			switch(temp){
				case 0b00:
					timer_freq =


			}

		}

		return;
	} */

/* 0	Vblank   0x40
   1	LCD stat 0x48
   2	Timer 	 0x50
   3	Serial	 0x58
   4	Joypad   0x60 */

void interrupt_routine(){
	IME = memory[0xffff];
	IF  = memory[0xff0f];

	if (ie > 0){
		if ((IME & 0x1) && (IF & 0x1)){  //Vblank
			memory[0xff0f] = 0;
			push16(pc);
			pc = 0x40;
		}
		else if((IME & 0x2) && (IF & 0x2)){  //LCD
				memory[0xff0f] = 0;
				push16(pc);
				pc = 0x48;
		}
			else if ((IME & 0x4) && (IF & 0x4)){   //Timer
					memory[0xff0f] = 0;
					push16(pc);
					pc = 0x50;
			}
				else if ((IME & 0x8) && (IF & 0x8)){  //Serial
						memory[0xff0f] = 0;
						push16(pc);
						pc = 0x58;
				}
					else if ((IME & 0x10) && (IF & 0x10)){  //Joypad
							memory[0xff0f] = 0;
							push16(pc);
							pc = 0x60;
					}
	
	}

	return;
}

public:

	void boot_logo(){
		update_tileram();
		
		
		SDL_SetRenderDrawColor(Gboi_renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(Gboi_renderer);

		//draw routine
			
			
		for (int lo = 1; lo < 13; lo++)   //top half logo
			draw_tile(lo + 10 , 15, lo);
				
		
			for (int go = 1; go < 20; go ++)	//bottom half logo
				draw_tile(go + 10 , 16, 12 + go );
		
	
		// display on screen
		
		SDL_RenderPresent(Gboi_renderer);

		frame_start_time = SDL_GetTicks();
		wait_next_frame(frame_start_time + 1500);
		return;
	}

	bool load_binary(string path) { //load rom starting at 0x200

		char cpath[200];
		strcpy(cpath, path.c_str());

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
		//write nintendo logo to vram
		/*for (int i = 0x8000; i <= 0x819f; i++)
			memory[i] = vram_init[i - 0x8000];
		*/

		//write 0x0 to vram
		for (int i = 0x8000; i <= 0x819f; i++)
			memory[i] = 0x0;
		
		soft_reset();

		return;

	}
	

	void soft_reset() {
		
		ra = 0x01;
		rb = 0;
		//rc = 0x13;
		rc  = 0;
		rd = 0;
		//re = 0xd8;  //registers
		re = 0;
		
		//rhl = 0x014d;
		rhl = 0;
		
		
		//lcd register 0x91

		ie = 0;  //interrupt enable

		//sr = 0xb0; //status register
		sr = 0;
		sp = 0xfffe;  //not dfff?
		pc = 0x100;

		frame_start_time = SDL_GetTicks();

		

		return;

	}

	void test_bit(int num, uint16_t reg){
		if ((reg  & num) > 0)
						set_zero(0);
					else
						set_zero(1);
					set_subtract(0);
					set_hcarry(1);
					return;
	}

void savestate() {
	/*00 bootrom_enable_boh
	01 ra
	02 rf
	03 rb
	04 rc
	05 rd
	06 re
	07-08 rhl
	09-0a rsp
	0b-0c pc
	0d IME

	0e halted   ??? written as 0
	0f stopped             0

	10-2009 VRAM
	2010-20af OAM

	20b0 LCDC
	20b1 BGP
	20b2 OBP0
	20b3 OBP1  all 00
	20b4 SCY
	20b5 SCX
	20b6 WY
	20b7 WX

	20b8 - 40b7 RAM    from 0xc000 to 0xe000

	40b8- 4117 non io internal ram
	4118 - 4163  io ports
	4164 - 41e2   internal ram 1

	41e3 interrupt enable register    IF */  
	if (state_number == 12340 && debugging)
		cout<<"";
	if (state_number >= 12000 && debugging){
		cout<<"Saving state:  "<<state_number;
		ofstream outfile ("gstate_" + to_string(state_number), ios::binary);

		outfile << (char)(0x00 & 0xff) << (char)(ra & 0xff) << (char)(sr & 0xff) << (char)(rb & 0xff) << (char)(rc & 0xff) << (char)(rd & 0xff) << (char)(re & 0xff) << (char)(rhl & 0x00ff) << (char)((rhl >> 8) & 0xff) << (char)(sp & 0xff) << (char)((sp >> 8) & 0xff) << (char)(current_pc & 0xff) << (char)((current_pc >> 8) & 0xff) ;
		outfile << (char)(IME & 0xff) << (char)0x00 << (char)0x00 ;
		
		for (int a = 0; a < 0x2000; a++){  //vram, 8000 to a000
			outfile << (char)memory[0x8000 + a];
		}

		for (int a = 0; a < 0xa0; a++){  //oam, fe00 to fea0
			outfile << (char)memory[0xfe00 + a];
		}

		outfile << (char)0x00 << (char)0x00 << (char)0x00 << (char)0x00 << (char)0x00 << (char)0x00 << (char)0x00 << (char)0x00 ;
		
		for (int j = 0; j < 0x2000; j++){
			outfile << memory[0xc000 + j];
		} 
		
		outfile.close();
		
	}
	
	state_number++;
	if (state_number == 13000 && debugging )
 		cout<<"LELLO";
	return;
}

long lel = 0;   //DEBUG
bool found = false;
int lastpc [10000];
int index = 0;
int mov_breakpoint = 0x312;  
bool blallo = 0;

void cycle() {  //fetch, execute

	//TODO interrupts, timers, tile maps <---
	
	
	lel ++;

	if (lel % 4 == 0)  //temporary LY bypass  //TODO this
		memory[0xff44] = memory[0xff44] + 1;

	//interrupt handling:
	if ((old_cycle_count - cycle_count) > 0)     //need to check if x time has passed, then enable interrupt and reset old-cycle-count
		IF = IF | 0x2;

	interrupt_routine();

	

	if (cycle_count > (last_frame_cycle_count + CYCLES_PER_SECOND)){   //frame handling kinda
		last_frame_cycle_count = cycle_count;  // reset cycle counter
		
		wait_next_frame(frame_start_time + (1000 / 60)); //60 frames every 1000 ms
		frame_start_time = SDL_GetTicks();

		//update vram and draw
		
		draw_tileset();	//TEMP
		draw_map(false);  //TODO debug map side, pc has to get to 0x407 twice untiil map has loaded completely

		//vblank interrupt	
		memory [0xff0f] = memory[0xff0f] | 0x1;

	}

	old_cycle_count = cycle_count;  //TODO completely wrong

	//DEBUG
	if (debugging){
		current_pc = pc;
		if(pc == 0x407)
			foundonce ++;
		if (foundonce == 2)
			for(int o = 0; o < 360; o++)
				cout<<"address   "<<0x9800 + o<<"        value      "<<(int)memory[0x9800 + o]<<endl;

		// savestate();

		if (rhl == 0xa0d)
			cout<<"";
	}  //Not debug

	opcode = memory[pc];
	operand[0] = memory[pc + 1];
	operand[1] = memory[pc + 2];

	/*if (opcode == 0x32 && rhl == 0x9800 && pc == 0x27f1){

		dump_memory();

		for (int i = 0; i < 0x300; i++)
			cout<<(int)memory[i+0x9800]<<" ,";
		cout<<endl;	} */

	switch (opcode) {

		case 0x00:    // NOP
			pc += 1;
			cycle_count += 4;
			break;

		case 0x01:    // LD rbc bbaa()
			w_rbc(bbaa());
			pc += 3;
			cycle_count += 20;
			break;

		case 0x03: {  // INC rbc
			uint16_t temp = r_rbc();
			w_rbc(temp + 1);
			pc += 1;
			cycle_count += 8;
			break;	}

		case 0x04: {  // INC rb
			if ((rb & 0xf) == 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			rb++;
			set_subtract(0);
			rb = rb & 0xff;
			check_zero(rb);
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x05: {  // DEC rb
			uint8_t temp = rb >> 4;
			rb--;
			if (rb >>4 != temp)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			
			set_subtract(1);
			rb = rb & 0xff;
			check_zero(rb);
			pc += 1;
			cycle_count += 4;
			break; 	}

		case 0x06:    // LD rb operand0
			rb = operand[0];
			check_zero(rb);
			pc += 2;
			cycle_count += 8;
			break; 	

		case 0x09:    // ADD rhl rbc
			if ((r_rbc() & 0xff) + (rhl & 0xff) > 0xff)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			rhl += r_rbc();
			check_carry32(rhl);
			set_subtract(0);
			pc += 1;
			cycle_count += 8;
			break;

		case 0x0a:    // LD ra (rbc)
			ra = memory[r_rbc()];
			pc += 1;
			cycle_count += 8;
			break;

		case 0x0b: {  // DEC rbc
			uint32_t temp = r_rbc();  
			w_rbc((temp - 0x1)); 
			pc += 1;
			cycle_count += 4;
			break; 	}

		case 0x0c: {  // INC rc
			if ((rc & 0xf) == 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			rc++;
			set_subtract(0);
			rc = rc & 0xff;
			check_zero(rc);
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x0d: {  // DEC rc
			uint8_t temp = rc >> 4;
			rc--;
			if (rc >>4 != temp)
				set_hcarry(1);
			else
				set_hcarry(0);

			set_subtract(1);
			rc = rc & 0xff;
			check_zero(rc);
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x0e:    // LD rc operand0
			rc = operand[0];
			pc += 2;
			cycle_count += 8;
			break;

		case 0x11:    // LD rbe bbaa()
			w_rde(bbaa());
			pc += 3;
			cycle_count += 12;
			break;

		case 0x12:    // LD (rde) ra
			wr_mem(r_rde(), ra);
			pc += 1;
			cycle_count += 8;
			break;

		case 0x13: {  // INC rde
			uint16_t temp = r_rde();
			w_rde(temp + 1);
			pc += 1;
			cycle_count += 8;
			break;	}
		
		case 0x14:    // INC rd
			if ((rd & 0xf) == 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			rd++;
			set_subtract(0);
			rd = rd & 0xff;
			check_zero(rd);
			pc += 1;
			cycle_count += 4;
			break;	

		case 0x15: {  // DEC rd  
			uint8_t temp = rd >> 4;
			rd--;
			if (rd >>4 != temp)
				set_hcarry(1);
			else
				set_hcarry(0);

			set_subtract(1);
			rd = rd & 0xff;
			check_zero(rd);
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x16:    // LD rd operand0
			rd = operand[0];
			pc += 2;
			cycle_count += 8;
			break;

		case 0x18:    // JR signed
			if (operand[0] >= 0x80) {
					operand[0] = (operand[0]^0xff) + 1 ;
					pc -= operand[0];
				}
				else {
				pc += operand[0];
				}
					
				pc += 2;
				cycle_count += 16;
			break;

		case 0x19:    // ADD rhl rde
			if ((r_rde() & 0xff) + (rhl & 0xff) > 0xff)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			rhl += r_rde();
			check_carry32(rhl);
			set_subtract(0);
			pc += 1;
			cycle_count += 8;
			break;

		case 0x1a:    // LD ra (de)
			ra = memory[r_rde()];
			pc += 1;
			cycle_count += 8;
			break;

		case 0x1c: {  // INC re
			if ((re & 0xf) == 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			re++;
			set_subtract(0);
			re = re & 0xff;
			check_zero(re);
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x1e:    // LD re operand0 
			re = operand[0];
			pc += 2;
			cycle_count += 8;
			break;

		case 0x1f: {  // RRA
			bool temp = read_carry();
			set_carry(bool((ra & 0x80) >> 8));  //TODO check this mess
			ra = (ra * 2) + temp;
			check_carry(ra);
			set_subtract(0);
			set_hcarry(0);
			set_zero(0);
			pc += 1;
			cycle_count += 4;
			break;	}
				   
		case 0x20: {  // JR NZ operand0
			if (read_zero() == 0) {
				if (operand[0] >= 0x80) {
					operand[0] = (operand[0]^0xff) + 1 ;
					pc -= operand[0];
					cycle_count += 16;
				}
				else {
					pc += operand[0];
					cycle_count += 12;
				}
			}
			
				pc += 2;
				
			break;	}

		case 0x21:    // LD rhl bbaa()
			rhl = bbaa();
			pc += 3;
			cycle_count += 12;
			break;

		case 0x22:    // LD (rhl)+ ra 
			wr_mem(rhl, ra);
			rhl ++;
			pc += 1;
			cycle_count += 8;
			break;

		case 0x23:    // INC rhl
			rhl++;
			pc += 1;
			cycle_count += 8;
			break;

		case 0x26:    // LD rh operand0
			rhl = rhl & 0x00ff;
			rhl += operand[0] << 8;
			pc += 2;
			cycle_count += 8;
			break;

		case 0x28:    // JRZ signed
			if (read_zero() != 0) {
				if (operand[0] >= 0x80) {
					operand[0] = (operand[0]^0xff) + 1 ;
					pc -= operand[0];
					cycle_count += 16;
				}
				else {
					pc += operand[0];
					cycle_count += 12;
				}
			}
			
				pc += 2;
			break;

		case 0x2a:    // LD ra (rhl)+
			ra = memory[rhl];
			rhl += 0x1;
			pc += 1;
			cycle_count += 8;
			break;

		case 0x2c: {  // INC rl
			uint8_t temp = rhl;
			
			if ((temp & 0xf) == 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			temp ++;
			set_subtract(0);
			check_zero(temp);
			rhl = rhl & 0xff00;
			rhl += temp;
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x2d: {  // DEC rl
			uint8_t temp = (rhl >> 4) & 0xf;
			rhl--;
			
			if (((rhl >> 4) & 0xf) != temp)
				set_hcarry(1);
			else
				set_hcarry(0);

			set_subtract(1);
			rhl = rhl & 0xffff;
			check_zero(rhl & 0xff);
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x2f:    // NOT ra
			ra = 0xff - ra;
			set_subtract(1);
			set_hcarry(1);
			pc += 1;
			cycle_count += 4; //?
			break;

		case 0x31:    // LD SP bbaa()
			sp = bbaa();
			pc += 3;
			cycle_count += 12;
			break;

		case 0x32:    // LD (HL)- ra
			wr_mem(rhl, ra);
			rhl--;
			pc += 1;
			cycle_count += 8;
			break;
		
		case 0x34:    // INC (rhl)
			if ((memory[rhl] & 0xf) == 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			memory[rhl]++;
			set_subtract(0);
			memory[rhl] = memory[rhl] & 0xff;
			check_zero(memory[rhl]);
			pc += 1;
			cycle_count += 12;
			break;

		case 0x35: {  // DEC (rhl)
			if ((memory[rhl] & 0xf) == 0xf)
				set_hcarry(0);
			else
				set_hcarry(1);
			
			memory[rhl] = memory[rhl] - 1;
			set_subtract(1);
			check_zero(memory[rhl]);
			pc += 1;
			cycle_count += 12;
			break;	}

		case 0x36:    // LD (HL) operand0
			wr_mem(rhl, operand[0]);
			pc += 2;
			cycle_count += 12;
			break;

		case 0x38:    // JR C operand0
			if (read_carry() == 1) {
				if (operand[0] >= 0x80) {
					operand[0] = (operand[0]^0xff) + 1 ;
					pc -= operand[0];
					cycle_count += 16;
				}
				else {
					pc += operand[0];
					cycle_count += 12;
				}
			}
			
				pc += 2;
				
			break;

		case 0x3a:    // LD ra (rhl)-
			ra = memory[rhl];
			pc += 1;
			rhl --;
			cycle_count += 8;
			break;

		case 0x3c:    // INC ra
			if ((ra & 0xf) == 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			ra++;
			set_subtract(0);
			ra = ra & 0xff;
			check_zero(ra);
			pc += 1;
			cycle_count += 4;
			break;

		case 0x3d: {  // DEC ra
			uint8_t temp = ra >> 4;
			ra--;
			if (ra >>4 != temp)
				set_hcarry(1);
			else
				set_hcarry(0);

			set_subtract(1);
			ra = ra & 0xff;
			check_zero(ra);
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x3e:    // LD ra operand0
			ra = operand[0];
			pc += 2;
			cycle_count += 8;
			break;

		case 0x40:    // LD rb rb
			rb = rb;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x4e:    // LD rc (rhl)
			rc = memory[rhl];
			pc += 1;
			cycle_count += 8;
			break;

		case 0x46:    // LD rb (rhl)
			rb = memory[rhl];
			pc += 1;
			cycle_count += 8;
			break;

		case 0x47:    // LD rb ra
			rb = ra;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x4f:    // LD rc ra
			rc = ra;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x54:    // LD rd rh
			rd = (rhl >> 8) & 0xff;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x56:    // LD rd (rhl)
			rd = memory[rhl];
			pc += 1;
			cycle_count += 8;
			break;

		case 0x57:    // LD rd ra
			rd = ra;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x5d:    // LD re rl
			re = rhl >> 8;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x5e:    // LD re (rhl)
			re = memory[rhl];
			pc += 1;
			cycle_count += 8;
			break;

		case 0x5f:    // LD re ra
			re = ra;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x60:    // LD rh rb
			rhl = rhl & 0x00ff;
			rhl += rb << 8;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x67:    // LD rh ra
			rhl = rhl & 0x00ff;
			rhl += ra << 8;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x69:    // LD rl rc
			rhl = rhl & 0xff00;
			rhl += rc;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x6f:    // LD rl ra
			rhl = rhl & 0xff00;
			rhl += ra;
			pc += 1;
			cycle_count += 4;
			break;
		
		case 0x71:    // LD (rhl) rc
			wr_mem(rhl, rc);
			pc += 1;
			cycle_count += 8;
			break;

		case 0x72:    // LD (rhl) rd
			wr_mem(rhl, rd);
			pc += 1;
			cycle_count += 8;
			break;

		case 0x73:    // LD (rhl) re
			wr_mem(rhl, re);
			pc += 1;
			cycle_count += 8;
			break;

		case 0x75: {  // LD (rhl) rl
			wr_mem(rhl, rhl & 0xff);
			pc += 1;
			cycle_count += 8;
			break;	}

		case 0x77:    // LD (rhl) ra
			wr_mem(rhl, ra);
			pc += 1;
			cycle_count += 8;
			break;
		
		case 0x78:    // LD ra rb
			ra = rb;
			pc += 1;
			cycle_count += 4;	
			break;
					
		case 0x7a:    // LD ra rd
			ra = rd;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x7b:    // LD ra re
			ra = re;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x79:    // LD ra rc
			ra = rc;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x7c:    // LD ra rh
			ra = rhl >> 8;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x7d:    // LD ra rl
			ra = rhl & 0x00ff;
			pc += 1;
			cycle_count += 4;
			break;

		case 0x7e: {  // LD ra (hl)
			ra = memory[rhl];
			pc += 1;
			cycle_count += 12;
			break;	}

		case 0x80:    // ADD ra rb
			if ((ra & 0xf) + (rb & 0xf) > 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);		

			ra += rb;
			check_carry(ra);
			check_zero(ra);
			set_subtract(0);
			pc += 1;
			cycle_count += 4;
			break;

		case 0x82:    // ADD ra rd
			if ((ra & 0xf) + (rd & 0xf) > 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);		

			ra += rd;
			check_carry(ra);
			check_zero(ra);
			set_subtract(0);
			pc += 1;
			cycle_count += 4;
			break;
		
		case 0x83:    // ADD ra re
			if ((ra & 0xf) + (re & 0xf) > 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			ra += re;
			set_subtract(0);
			check_carry(ra);
			check_zero(ra);
			pc += 1;
			cycle_count += 4;
			break;

		case 0x85: {  // ADD ra rl
			uint8_t temp = rhl;
			if ((ra & 0xf) + (temp & 0xf) > 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			ra += temp;
			set_subtract(0);
			check_carry(ra);
			check_zero(ra);
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x87: {  // ADD ra ra
			if ((ra & 0xf) + (ra & 0xf) > 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);

			ra += ra;
			check_carry(ra);
			check_zero(ra);
			set_subtract(0);
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x89: {  // ADC ra rc
			if ((ra & 0xf) + ((rc + r_sr('c')) & 0xf) > 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);

			ra += rc + (r_sr('c'));
			check_carry(ra);
			check_zero(ra);
			set_subtract(0);
			pc += 1;
			cycle_count += 4;
			break;	}

		case 0x8f: {  // ADC ra ra
			if ((ra & 0xf) + ((ra + r_sr('c')) & 0xf) > 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);
			
			uint16_t temp = r_sr('c') + ra;
			ra = (ra * 2) + r_sr('c');
			check_carry(ra);
			check_zero(ra);
			set_subtract(0);
			pc += 1;
			cycle_count += 4;
			break;	}

		//case 0x97:    // SUB ra ra
		case 0xa0:    // AND ra rb
			ra = rb & ra;
			set_hcarry(1);
			set_subtract(0);
			set_carry(0);
			check_zero(ra);
			pc +=1;
			cycle_count += 4;
			break;

		case 0xa1:    // AND ra rc
			ra = rc & ra;
			set_hcarry(1);
			set_subtract(0);
			set_carry(0);
			check_zero(ra);
			pc +=1;
			cycle_count += 4;
			break;

		case 0xa7:    // AND ra ra
			ra = ra & ra;
			set_hcarry(1);
			check_zero(ra);
			set_subtract(0);
			set_carry(0);
			pc += 1;
			cycle_count += 4;
			break;

		case 0xa9:    // XOR ra rc
			ra = rc ^ ra;
			check_zero(ra);
			set_subtract(0);
			set_hcarry(0);
			set_carry(0);
			pc += 1;
			cycle_count += 4;
			break;

		case 0xaf:    // XOR ra ra
			ra = 0;
			set_zero(1);
			set_hcarry(0);
			set_carry(0);
			set_subtract(0);
			pc += 1;
			cycle_count += 4;
			break;

		case 0xb0:    // OR ra rb  
			ra = ra | rb;
			check_zero(ra);
			set_subtract(0);
			set_hcarry(0);
			set_carry(0);
			pc += 1;
			cycle_count += 4;
			break;
		
		case 0xb1:    // OR ra rc
			ra = rc | ra;
			set_hcarry(0);
			set_subtract(0);
			set_carry(0);
			check_zero(ra);
			pc += 1;
			cycle_count += 4;
			break;

		case 0xb7:    // OR ra ra
			ra = ra | ra;
			check_zero(ra);
			set_carry(0);
			set_hcarry(0);
			set_subtract(0);
			pc +=2;
			cycle_count += 4;
			break;

		case 0xc0:    // RTS NZ
			if (read_zero() == 0){
				pc = pop16();
				cycle_count += 20;
			}
			else{
				pc += 1;
				cycle_count += 8;
			}
			break;
		
		case 0xc1:    // POP rbc
			w_rbc(pop16());
			pc += 1;
			cycle_count += 12;
			break;

		case 0xc2:    // JNZ bbaa()
			if (read_zero() > 0) {
				pc = bbaa();
				cycle_count += 16;
			}
			else
			{
				pc += 3;
				cycle_count += 12;
			}
			break;
			

		case 0xc3:    // JMP bbaa()
			pc = bbaa();
			cycle_count += 16;
			break;

		case 0xc5:    // PUSH rbc
			push16(r_rbc());
			pc += 1;
			cycle_count += 16;
			break;

		case 0xc6:    // ADD ra operand0
			if ((ra & 0xf) + (operand[0] & 0xf) > 0xf)
				set_hcarry(1);
			else
				set_hcarry(0);

			ra = ra + operand[0];
			set_subtract(0);
			check_carry(ra);
			check_zero(ra);
			pc += 2;
			cycle_count += 8;
			break;

		case 0xc8:    // RTS Z
			if (read_zero() == 1){
				pc = pop16();
				cycle_count += 20;
			}
			else{
				pc += 1;
				cycle_count += 8;
			}
			break;	
			
		case 0xc9:    // RTS
			pc = pop16();
			cycle_count += 16;
			break;

		case 0xca:    // JZ absolute
			if (read_zero() == 1){
				pc = bbaa();
				cycle_count += 16;
			}
			else{
				pc += 3;
				cycle_count += 12;
			}
			break;

		case 0xcb: {  // 2 bytes instructions
			switch (operand[0]){
				case 0x27:    // SLA ra
					set_carry(ra >> 7);
					ra = ra << 1;
					check_zero(ra);
					set_subtract(0);
					set_hcarry(0);
					pc += 1;
					cycle_count += 8;
					break;
				
				case 0x33: {  // SWAP re
					uint8_t temp = (re & 0xf);
					re= (re >> 4) + (temp << 4);
					check_zero(re);
					set_subtract(0);
					set_hcarry(0);
					set_carry(0);
					cycle_count += 8;
					break;	}

				case 0x37: {  // SWAP ra
					uint8_t temp = (ra & 0xf);
					ra = (ra >> 4) + (temp << 4);
					check_zero(ra);
					set_subtract(0);
					set_hcarry(0);
					set_carry(0);
					cycle_count += 8;
					break;	}

				case 0x3f:    // SRL ra
					set_carry(ra & 0b1);
					ra = ra >> 1;
					check_zero(ra);
					set_subtract(0);
					set_hcarry(0);
					cycle_count += 8;
					break;
					
				case 0x40:    // BIT 0 rb
					test_bit(0,rb);
					cycle_count += 8;
					break;
				
				case 0x50:    // BIT 2 rb
					test_bit(2, rb);
					cycle_count += 8;
					break;

				case 0x5f:    // BIT 3 ra
					test_bit(3,ra);
					cycle_count += 8;
					break;

				case 0x7e:    // BIT 7 (rhl)
					test_bit(7,memory[rhl]);
					cycle_count += 12;
					break;

				case 0x7f:    // BIT 7 ra
					test_bit(7,ra);
					cycle_count += 8;
					break;

				case 0x86: {  // RES 0 (rhl)
					uint8_t temp = memory[rhl];
					temp = temp & 0b11111110;
					wr_mem(rhl, temp);
					cycle_count += 16;
					break;	}
				case 0x87:    // RES 0 ra
					  ra = ra & 0xfe;
					  cycle_count += 8;
					break;



				default: {
					cout << "Unknown CB op ";	}
			} 

			pc += 2;
			break;
		}
		case 0xcd:    // CALL bbaa()
			push16(pc + 0x3);
			pc = bbaa();
			cycle_count += 24;
			break;

		case 0xcf:    // CALL 08h
			push16(pc);
			pc = 0x08;
			cycle_count += 24;  //?
			break;

		case 0xd1:    // POP rde
			w_rde(pop16());
			pc += 1;
			cycle_count += 12;
			break;

		case 0xd5:    // PUSH rde
			push16(r_rde());
			pc += 1;
			cycle_count += 16;
			break;

		case 0xd9:    // RETI
			pc = pop16();
			ie = 1;
			cycle_count += 16;
			break;

		case 0xdf:    // CALL 0018h
			push16(pc);
			pc = 0x0018;
			cycle_count += 24; // ?
			break;

		case 0xe0:    // LD (ff00h + operand0) ra
			wr_mem((0xff00 + operand[0]), ra);
			pc +=2;
			cycle_count += 8;
			break;


		case 0xe1:    // POP rhl
			rhl = pop16();
			pc += 1;
			cycle_count += 12;
			break;

		case 0xe2:    // LD (ff00h + rc) ra
				wr_mem((0xff00 + rc), ra);
				pc += 1;
				cycle_count += 8;
			break;

		case 0xe5:    // PUSH rhl
			push16(rhl);
			pc += 1;
			cycle_count += 16;
			break;

		case 0xe6:    // AND ra operand0
			ra = ra & operand[0];
			set_hcarry(1);
			pc += 2;
			cycle_count += 8;
			break;

		case 0xe9:    // JMP rhl
			pc = rhl;
			cycle_count += 16;
			break;

		case 0xea: {  // LD (operand0) ra
			wr_mem(bbaa(), ra);
			pc += 3;
			cycle_count += 16;
			break;	}
		case 0xee:    // XOR ra operand0
			ra = ra ^ operand[0];
			check_zero(ra);
			set_subtract(0);
			set_hcarry(0);
			set_carry(0);
			pc += 2;
			cycle_count += 4;
			break;

		case 0xef:    // CALL 28h
			push16(pc + 1);
			pc = 0x28;
			cycle_count += 24; //?
			break;

		case 0xf0: {  // LD ra (ff00h + operand0)
			ra = memory[(0xff00 + operand[0])];
			pc += 2;
			cycle_count += 8;
			break;	}
		case 0xf1:    // POP raf
			w_raf(pop16());
			pc += 1;
			cycle_count += 12;
			break;

		case 0xf3: {  // DI
			ie = 0;
			pc += 1;
			cycle_count += 4;
			break;	} 

		case 0xf5: {  // PUSH raf
			push16(r_raf());
			pc += 1;
			cycle_count += 16;
			break;	}

		
		case 0xf6:    // OR ra operand0
			ra = operand[0] | ra;
			set_hcarry(0);
			set_subtract(0);
			set_carry(0);
			check_zero(ra);
			pc += 1;
			cycle_count += 4;
			break;

		case 0xfa:    // LD ra bbaa()
			ra = memory[bbaa()];
			pc += 3;
			cycle_count += 16;
			break;

		case 0xfb:    // IE
			ie = 1;
			pc += 1;
			cycle_count += 4;
			break;

		case 0xfe: {  // CMP ra operand0 
			uint16_t temp = ra - operand[0];
			if (((ra & 0x10) == 0x10) && ((temp & 0x10) != 0x10)) 
				set_hcarry(1);
			else
				set_hcarry(0);

			check_carry(temp);
			set_subtract(1);
			ra = temp & 0xff;
			check_zero(temp);

			pc += 2;
			//?
			break;	}
		case 0xff: {  // RST $38
			pc = 0x38;
			cycle_count += 24;//?
			break;	}

		default:   {
			cout << "unknown opcode" << (int)opcode << "   " << (int)pc ;
			//DEBUG print trace of sorts
			//print_trace_of_sorts();
			break;
			}
		};
		
		return;
	}

	void dump_fbuffer(){	//DEBUG
		
			for (int i = 0; i < 8; i++){
				cout << endl;
				for(int j = 0; j < 128; j++)
					if (gfx[j][i] == 0){
						cout << " ";
					}
					else
					{
						cout << "X";
					}
					cout << " ";
			}
			cout<<endl;
		
		return;
	}


    void ginit() {
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return;
		}
		
		vram_viewer = SDL_CreateWindow("VRAM Viewer Gboi", VRAM_VIEWER_POS_X, VRAM_VIEWER_POS_Y, VRAM_SCREEN_WIDTH, VRAM_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		Gboi =SDL_CreateWindow("Gboi", GBOI_POS_X, GBOI_POS_Y, GBOI_SCREEN_WIDTH, GBOI_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		
		if (vram_viewer == NULL || Gboi == NULL) {
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			return;
		}

		vram_renderer = SDL_CreateRenderer(vram_viewer, -1, SDL_RENDERER_ACCELERATED);
		Gboi_renderer = SDL_CreateRenderer(Gboi, -1, SDL_RENDERER_ACCELERATED);
		
		if (vram_renderer == NULL || Gboi_renderer == NULL) {
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			return;
		}
		else {
			SDL_SetRenderDrawColor(vram_renderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_SetRenderDrawColor(Gboi_renderer, 0x00, 0x00, 0x00, 0xFF);
		}
	}

	void draw_tileset() {  
		
		//populate gfx
		update_tileram();
		
		
		SDL_SetRenderDrawColor(vram_renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(vram_renderer);

		//SDL_SetRenderDrawColor(Gboi_renderer, 0x00, 0x00, 0x00, 0xFF);
		//SDL_RenderClear(Gboi_renderer);
		
		//draw routine
			
		for (int hi = 0; hi < 32; hi ++)		
			for (int lo = 0; lo < 32; lo++)   
				draw_tile_viewer(lo , hi, lo + (hi * 32));
					
		
	
		// display on screen
		SDL_RenderSetScale(vram_renderer,VRAM_SCREEN_MULTIPLIER,VRAM_SCREEN_MULTIPLIER);
		SDL_RenderPresent(vram_renderer);
		
		//SDL_RenderPresent(Gboi_renderer);
			
	}

	void draw_map(bool map_number){ //draw map, #0 is at 9800h-9BFFh 
		update_tileram();
		
		SDL_SetRenderDrawColor(Gboi_renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(Gboi_renderer);
		
		if (map_number == false){
			
			for (int i = 0; i < 20; i++){
				for (int j = 0; j < 18; j++)
					draw_tile(i,j,memory[0x9800 + i + (j * 0x20)]);
				

			}
		}
		else
		{
			
		}
		
		SDL_RenderSetScale(Gboi_renderer,GBOI_SCREEN_MULTIPLIER,GBOI_SCREEN_MULTIPLIER);
		SDL_RenderPresent(Gboi_renderer);

		return;
	}

	void draw_tile_viewer(int xpos, int ypos, int xindex){  // takes input x and y tile position, and x y index of tile in gfx
																
			xpos   *= 8;
			ypos   *= 8;
			xindex *= 8;			

			for (int y = ypos; y < ypos + 8; y++) {  				
				for (int x = xpos; x < xpos + 8; x++) {
					SDL_Rect fillRect = { x, y, 1, 1};
					SDL_SetRenderDrawColor(vram_renderer, gfx[xindex + (x - xpos)][(y - ypos)] * 0x55, gfx[xindex +(x - xpos)][(y - ypos)] * 0x55, gfx[xindex + (x - xpos)][(y - ypos)] * 0x55, 0xff);
					SDL_RenderFillRect(vram_renderer, &fillRect);	
				}
			}  
	}

	void draw_tile(int xpos, int ypos, int xindex){  // takes input x and y tile position, and x y index of tile in gfx
																
		xpos   *= 8;
		ypos   *= 8;
		xindex *= 8;			

		for (int y = ypos; y < ypos + 8; y++) {  				
			for (int x = xpos; x < xpos + 8; x++) {
				SDL_Rect fillRect = { x, y, 1, 1};
				SDL_SetRenderDrawColor(Gboi_renderer, gfx[xindex + (x - xpos)][(y - ypos)] * 0x55, gfx[xindex +(x - xpos)][(y - ypos)] * 0x55, gfx[xindex + (x - xpos)][(y - ypos)] * 0x55, 0xff);
				SDL_RenderFillRect(Gboi_renderer, &fillRect);	
			}
		}  
	}

	void update_tileram(){

		uint16_t tile_address;
			 
											
		for (int col = 0; col < MAX_NUM_TILES; col++) {

			tile_address = 0x8000 + (col * 16) - 2;
					
			for (int pxline = 0; pxline <= 7; pxline++) {
					
				tile_address +=2;

				gfx [(col * 8)][pxline]     = ((memory[tile_address] & 0b10000000) >> 6) + ((memory[tile_address + 1] & 0b10000000) >> 7);
				gfx [(col * 8) + 1][pxline] = ((memory[tile_address] & 0b01000000) >> 5) + ((memory[tile_address + 1] & 0b01000000) >> 6);
				gfx [(col * 8) + 2][pxline] = ((memory[tile_address] & 0b00100000) >> 4) + ((memory[tile_address + 1] & 0b00100000) >> 5);
				gfx [(col * 8) + 3][pxline] = ((memory[tile_address] & 0b00010000) >> 3) + ((memory[tile_address + 1] & 0b00010000) >> 4);
				gfx [(col * 8) + 4][pxline] = ((memory[tile_address] & 0b00001000) >> 2) + ((memory[tile_address + 1] & 0b00001000) >> 3);
				gfx [(col * 8) + 5][pxline] = ((memory[tile_address] & 0b00000100) >> 1) + ((memory[tile_address + 1] & 0b00000100) >> 2);
				gfx [(col * 8) + 6][pxline] = (memory[tile_address] & 0b00000010)        + ((memory[tile_address + 1] & 0b00000010) >> 1);
				gfx [(col * 8) + 7][pxline] = ((memory[tile_address] & 0b00000001) << 1) + (memory[tile_address + 1] & 0b00000001);

						
			}
				
		}

			
	return;
	}

	void write_tile_vram(uint8_t tile_location[], uint16_t tile_address, int tile_index){
		
		tile_address -= 2;
					
			for (int pxline = 0; pxline <= 7; pxline++) {
				
				tile_address +=2;

				gfx [(tile_index * 8)][pxline]     = ((tile_location[tile_address] & 0b10000000) >> 6) + ((tile_location[tile_address + 1] & 0b10000000) >> 7);
				gfx [(tile_index * 8) + 1][pxline] = ((tile_location[tile_address] & 0b01000000) >> 5) + ((tile_location[tile_address + 1] & 0b01000000) >> 6);
				gfx [(tile_index * 8) + 2][pxline] = ((tile_location[tile_address] & 0b00100000) >> 4) + ((tile_location[tile_address + 1] & 0b00100000) >> 5);
				gfx [(tile_index * 8) + 3][pxline] = ((tile_location[tile_address] & 0b00010000) >> 3) + ((tile_location[tile_address + 1] & 0b00010000) >> 4);
				gfx [(tile_index * 8) + 4][pxline] = ((tile_location[tile_address] & 0b00001000) >> 2) + ((tile_location[tile_address + 1] & 0b00001000) >> 3);
				gfx [(tile_index * 8) + 5][pxline] = ((tile_location[tile_address] & 0b00000100) >> 1) + ((tile_location[tile_address + 1] & 0b00000100) >> 2);
				gfx [(tile_index * 8) + 6][pxline] = (tile_location[tile_address] & 0b00000010)        + ((tile_location[tile_address + 1] & 0b00000010) >> 1);
				gfx [(tile_index * 8) + 7][pxline] = ((tile_location[tile_address] & 0b00000001) << 1) + (tile_location[tile_address + 1] & 0b00000001);

						
			}



	}
	
};
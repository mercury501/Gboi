using namespace std;


class gbcpu {
private:
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

	uint16_t af; //accumulator
	  //status register	
	uint16_t bc, de, hl; //general purpose

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

	char w = 'w';    //for ease of use of flags function
	char r = 'r';
	char n = 'n';
	char z = 'z';
	char h = 'h';
	char c = 'c';

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
		af = 0;
		bc = 0;
		de = 0;
		hl = 0;

		sp = 0xdfff;
		pc = 0x100;

		return;

	}

	//uint8_t ram(bool mode, uint16_t address, uint8_t data) {
	//	if (mode == 1) {  //1 = write
	//		memory[address + 0xc000] = data;
	//		return 0;
	//	}
	//	else

	//		return memory[0xc000 + address];


	//}
	uint16_t bbaa() {

		return (operand[1] << 8) + operand[0];

	}

	uint16_t aabb() {

		return (operand[1] << 8) + operand[0];

	}

	bool flags(char mode, char flag, bool value) { //mode w write r read, flag Zero 7 N last math sub 6 Half carry (from lower nibble last math op) Carry set if carry or a is less than value for cp

		if (mode == 'w') {

			switch (flag) {
			case 'z':
				af | 0b0000000010000000;   //zero 7
				break;

			case 'n':
				af | 0b0000000001000000;  //last math sub 6
				break;

			case 'h':
				af | 0b0000000000100000;  //half carry 5
				break;

			case'c':
				af | 0b0000000000010000;  //carry 4
				break;

			default:
				cout << "UNKNOWN FLAG";
				break;
			}

		}

		if (mode == 'r') {
			bool retflag;

			switch (flag) {
			case 'z':
				retflag = ((af & 0b0000000010000000) >> 7);//zero 7
				break;

			case 'n':
				retflag = ((af & 0b0000000001000000) >> 6);//last math sub 6
				break;

			case 'h':
				retflag = ((af & 0b0000000000100000) >> 5); //half carry 5
				break;

			case'c':
				retflag = ((af & 0b0000000000010000) >> 4); //carry 4
				break;

			default:
				cout << "UNKNOWN FLAG";
				break;
			}

			return retflag;

		}

		else {
			cout << "UNKNOWN MODE STATUS REG";
			return 0;
		}


	}

	void cycle() {
		opcode = memory[pc];
		operand[0] = memory[pc + 1];
		operand[1] = memory[pc + 2];

		switch (opcode) {

		case 0x00:   //NOP
			pc += 1;
			break;

		case 0xc3:   //JMP bb aa
			pc = bbaa();
			break;

		case 0xaf:  //XOR A A
			af & 0x00FF;
			pc += 1;
			break;

		case 0x21:   //21 bb aa LD HL,$aabb
			hl = aabb();
			pc += 3;
			break;

		case 0xff:  //FF RST $38
			pc = 0x38;
			break;

		case 0x0e:   //0E xx LD C,$xx
			bc = bc & 0xff00;
			bc = bc | operand[0];
			pc += 2;
			break;

		case 0x06: { //06 xx LD B,$xx
			bc = bc & 0x00ff;
			bc = bc | (operand[0] << 8);
			pc += 2;
			break; }

		case 0x32:  //32 LD (HL)-,A
			memory[hl] = af >> 8;
			hl--;
			pc += 1;
			break;
		case 0x05: //05 DECrement B
			bc -= 0x0100;
			pc += 1;
			break;

		case 0x20:  //20 xx JR NZ,$xx
			if (!(flags(r, z, 0))) {
				if (operand[0] > 127)
					pc += operand[0];
				else
					pc -= operand[0];
			}
			else
				pc += 1;
			break;

		default:
			cout << "UNKNOWN OPERAND:";
			cout << endl;
			system("PAUSE");
			break;
		};

		return;
	}











};


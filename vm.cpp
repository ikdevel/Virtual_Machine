#include <iostream>
#include <fstream>
#include <stdint.h>
#include <iomanip>
#include "vm.hpp"
//#include <boost/lexical_cast.hpp> -- No longer required
#include <stdlib.h>
using namespace std;

void resetvm();

int chopcode;
int chtype;
int chval_a;
int chval_b;
int chnulval;
int chprog = 0x0110B020;
bool running = true; // Running flag



ifstream file;
ifstream::pos_type fsize;
ifstream::pos_type fcur;
int openbin(const char * fname) {
  file.open(fname, ios::in|ios::binary|ios::ate);
	if (file.is_open()) {
		fsize = file.tellg();
		file.seekg(0, ios::beg);
		return 0;
	}
	else return 1;
	return 0;
}

CPU cpu1; // If we ever consider adding another cpu, we can do so
int ip = 0; // Instruction pointer

void decode() { // Seperate program instructions and opcodes
			      //0x0110B020
	chopcode = (chprog&	0xFF000000) >> 24;
	chtype = (chprog&	0x0F00000) >> 20;
	chval_a = (chprog&	0x00FF000) >> 12;
	chval_b = (chprog&	0x0000FF0) >> 4;
	chnulval = (chprog&	0x000000F)	;
}

void printregs() {
	for(int i = 0; i < 16; i++) {
		cout << hex << "Main Register " << i << ": " << cpu1.m_reg[i] << endl;
	}
	for (int i = 0; i < 4; i++) {
		cout << hex << "Flag Register " << i << ": " << cpu1.flg[i] << endl;
	}
	cout << "Usermode flag: " << cpu1.usrflg << endl;
	cout << "CMP Flag: " << (short int) cpu1.cmpflg << endl;
}
	

void runins() {
	switch(chopcode) {
		case 0: // HLT
			cout << "HLT\n";
			running = false;
			return;
			break;
		case 0x01: // MOV
		cout << "MOV\n";
			switch(chtype) {
				case 1: cpu1.m_reg[chval_a] = chval_b; break;
			}
			break;
		case 0x02: // ADD
			cout << "ADD\n";
			switch(chtype) {
				case 1: cpu1.m_reg[chval_a] += cpu1.m_reg[chval_b];
					break;
			}
			break;
		case 0x03: // RESET
			cout << "RESET\n";
			resetvm();
			break;
		case 0x04: // SUB
			cout << "SUB\n";
			switch(chtype) {
				case 1: cpu1.m_reg[chval_a] -= cpu1.m_reg[chval_b];
					break;
			}
	}
}
void runall(const char * fname) {
	char buffer[4];
	openbin(fname);
	while ((file.good()) && running) {
		file.read((char *) &chprog, 4);
		cout << hex << uppercase << chprog << endl;
		decode();
		runins();
		/*if(file.eof()){cout << "EOF reached\n"; break;}*/
	}
}

int main(int argc,char * argv[]) {
	runall(argv[1]);
	cout << "\n";
	printregs();
	cout << hex << "Opcode: " << (int) chopcode << endl;
	cout << hex << "Instruction Type: " << (int) chtype << endl;
	cout << hex << "Operand A: " << (int) chval_a << endl;
	cout << hex << "Operand B: " << (int) chval_b << endl;
	cout << hex << "NULL Value: " << (int) chnulval << endl;
	cout << "\n";
	return 0;
}

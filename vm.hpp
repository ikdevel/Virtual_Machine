#ifndef VM_HPP
#define VM_HPP

// Global Variables
typedef struct _CPU { // CPU
  int m_reg[16]; // 16 main registers
	int flg[4]; // 4 FLAG registers -- Currently left unused
	int lck[6]; // 6 "LOCKED" registers ( hacking purposes ) -- Also unused
	bool active = true; // Active flag
	bool usrflg = true; // Usermode flag
	char cmpflg = -1; // Compare flag
} CPU;
extern CPU cpu1;

void resetvm() {
	for (int i = 0; i <= 16; i++) {
		cpu1.m_reg[i] = 0;
		if(i <= 4)
			cpu1.flg[i] = 0;
		if(i <= 6)
			cpu1.lck[i] = 0;
		if(i == 1) {
			cpu1.active = true;
			cpu1.usrflg = false;
			cpu1.cmpflg = -1;
		}
	}
}

#endif // VM_HPP

/** Utility Functions **/
void all_off(void) {
	PPU_CTRL = 0;
	PPU_MASK = 0;
}

void all_on(void) {
	PPU_CTRL = 0x90; //NMI On
	PPU_MASK = 0x1e; //Screen on
}

void loadPalette(void) {
	PPU_ADDRESS = 0x3f;
	PPU_ADDRESS = 0x00;
	for(index = 0; index < sizeof(PALETTE); ++index) {
		PPU_DATA = PALETTE[index];
	}

	PPU_ADDRESS = 0x23;
	PPU_ADDRESS = 0xda;
	for(index = 0; index < sizeof(attrib_table); ++index) {
		PPU_DATA = attrib_table[index];
	}
}

void resetScroll(void) {
	PPU_ADDRESS = 0;
	PPU_ADDRESS = 0;
	SCROLL = 0;
	SCROLL = 0;
}

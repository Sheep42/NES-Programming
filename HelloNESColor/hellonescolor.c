//Define the NES Registers we'll use
#define PPU_CTRL 	*((unsigned char*)0x2000)
#define PPU_MASK 	*((unsigned char*)0x2001)
#define PPU_STATUS 	*((unsigned char*)0x2002)
#define SCROLL 		*((unsigned char*)0x2005)
#define PPU_ADDRESS *((unsigned char*)0x2006)
#define PPU_DATA 	*((unsigned char*)0x2007)

//Force vars to be in the zeropage of the ram for optimization purposes
#pragma bss-name(push, "ZEROPAGE")

unsigned char index;
unsigned char NMI_flag;
unsigned char frame_count;
unsigned char text_pos;

//Force vars to be in the BSS of RAM, set as $0300 in cfg
#pragma bss-name(push, "BSS")
unsigned char test;

const unsigned char TEXT[] = {"Hello NES!"};

#include "palette.c"
#include "code.c"

//Forward Definers
void loadText(void);

void main(void) {
	/*
 	 * Turn off the screen
 	 *
 	 * Writing to the PPU can only happen during V-blank or when the screen is off
 	 */
	all_off();

	loadPalette();
	resetScroll();

	/*
 	 * Turn the screen on
 	 *
 	 * This will turn the screen back on and display our graphics
 	 *
 	 * See PPU Registers on Wiki for more info
 	 */
	all_on();

	//Loop forever
	while(1) {
		while(NMI_flag == 0); //NMI_flag is set in reset.s
		NMI_flag = 0;

		if(TEXT[text_pos] == ' ') frame_count = 15;

		//Wait 15 frames (~0.25s) 
		//Frame_Count increments in reset.s
		if(frame_count == 15) {
			loadText();
			resetScroll();
			frame_count = 0;
			++test;
		}
	}
}

void loadText(void) {
	if(text_pos < sizeof(TEXT)) {
		PPU_ADDRESS = 0x21;
		PPU_ADDRESS = 0xca + text_pos; //Roughly center

		PPU_DATA = TEXT[text_pos];

		PPU_ADDRESS = 0x21;
		PPU_ADDRESS = 0xea + text_pos; //One line down

		PPU_DATA = TEXT[text_pos];

		++text_pos;
	} else {
		text_pos = 0;
		PPU_ADDRESS = 0x21;
		PPU_ADDRESS = 0xca;

		for(index = 0; index < sizeof(TEXT); ++index) {
			PPU_DATA = 0; //Clear the text by writing tile 0 (blank) in it's place
		}

		PPU_ADDRESS = 0x21;
		PPU_ADDRESS = 0xea;

		for(index = 0; index < sizeof(TEXT); ++index) {
			PPU_DATA = 0; //Clear the text by writing tile 0 (blank) in it's place
		}
	}
}

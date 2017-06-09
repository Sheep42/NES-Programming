#define PPU_CTRL 	*((unsigned char*)0x2000)
#define PPU_MASK 	*((unsigned char*)0x2001)
#define PPU_STATUS 	*((unsigned char*)0x2002)
#define SCROLL 		*((unsigned char*)0x2005)
#define PPU_ADDRESS *((unsigned char*)0x2006)
#define PPU_DATA 	*((unsigned char*)0x2007)

unsigned char i;

const unsigned char TEXT[] = {"Hello NES!"};
const unsigned char PALETTE[] = {0x1f, 0x00, 0x10, 0x20};

void main(void) {
	/*
 	 * Turn off the screen
 	 *
 	 * Writing to the PPU can only happen during V-blank or when the screen is off
 	 */
	PPU_CTRL = 0;
	PPU_MASK = 0;

	/*
 	 * Load the palette
 	 *
	 *	We set PPU_ADDRESS to the high byte first, followed by the low byte (in this case 0x3f then 0x00
	 *	$3f00 is the beginning of the first bg palette address
 	 */

	PPU_ADDRESS = 0x3f; 
	PPU_ADDRESS = 0x00;

	for(i = 0; i < sizeof(PALETTE); ++i) {
		PPU_DATA = PALETTE[i]; //Loads our palatte colors into memory
	}

	/*
 	 * Load the text
 	 *
 	 * Address $21ca is somewhere near the middle of the screen in nametable 0
 	 * See PPU Memory map for more info
 	 */
	PPU_ADDRESS = 0x21;
	PPU_ADDRESS = 0xca;

	for(i = 0; i < sizeof(TEXT); ++i) {
		PPU_DATA = TEXT[i]; //Loads the text into memory
	}

	/*
 	 * Reset scroll pos
 	 *
 	 * Necessary because writing to the PPU screws up the scroll position, if not reset text may appear in the wrong place
 	 */
	PPU_ADDRESS = 0;
	PPU_ADDRESS = 0;
	SCROLL = 0;
	SCROLL = 0;

	/*
 	 * Turn the screen on
 	 *
 	 * This will turn the screen back on and display our graphics
 	 *
 	 * See PPU Registers on Wiki for more info
 	 */
	PPU_CTRL = 0x90; //NMI on
	PPU_MASK = 0x1e; //screen on

	//Loop forever
	while(1);
}

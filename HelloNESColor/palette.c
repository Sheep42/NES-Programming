const unsigned char PALETTE[] = {
	0x23, 0x00, 0x00, 0x11,		//blues
	0x00, 0x00, 0x00, 0x15,		//red
	0x00, 0x00, 0x00, 0x27,		//yellow
	0x00, 0x00, 0x00, 0x1a 		//green
};
//11 is the default bg color (blue)

const unsigned char attrib_table[] = {
	0x44,	//0100 0100
	0xbb,	//1011 1011
	0x44,	//0100 0100
	0xbb    //1011 1011
};

/*
	attrib table works as follows:

	33221100 = 2 bits per att area

	Position on screen:

		0  1
		2  3
	
	Each box is 16x16 px
*/

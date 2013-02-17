//ELD002 Group Project: Cybots
//Chronos System Software
//
//FILE DESCRIPTION
//LCD.c
//Contains functions for LCD driver.
//
//CONTAINS FUNCTIONS
//clear_display
//clear_line
//clear_number
//display_char
//display_chars
//display_number
//display_symbol
//flash_heart
//LCD_initiate
//switch_seg
//update_counts_remaining
//update_display
//update_time_elapsed
//write_LCD_mem
//
//WRITTEN BY
//Chris Elmer

//INCLUDES
#include  "main.h" //Processor header.

//GLABAL VARIABLES

// Table with memory bit assignment for digits "0" to "9" and characters "A" to "Z"
const unsigned lcd_font[] =
{
  SEG_A+SEG_B+SEG_C+SEG_D+SEG_E+SEG_F,           // Displays "0"
        SEG_B+SEG_C,                             // Displays "1"
  SEG_A+SEG_B+      SEG_D+SEG_E+      SEG_G,     // Displays "2"
  SEG_A+SEG_B+SEG_C+SEG_D+            SEG_G,     // Displays "3"
        SEG_B+SEG_C+            SEG_F+SEG_G,     // Displays "4"
  SEG_A+      SEG_C+SEG_D+      SEG_F+SEG_G,     // Displays "5"
  SEG_A+      SEG_C+SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "6"
  SEG_A+SEG_B+SEG_C,                             // Displays "7"
  SEG_A+SEG_B+SEG_C+SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "8"
  SEG_A+SEG_B+SEG_C+SEG_D+      SEG_F+SEG_G,     // Displays "9"
  0                                        ,     // Displays " "
  0                                        ,     // Displays " "
  0                                        ,     // Displays " "
  0                                        ,     // Displays " "
  0                                        ,     // Displays " "
                   SEG_D+SEG_E+       SEG_G,     // Displays "c"
  0                                        ,     // Displays " "
  SEG_A+SEG_B+SEG_C+      SEG_E+SEG_F+SEG_G,     // Displays "A"
              SEG_C+SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "b"
  SEG_A+            SEG_D+SEG_E+SEG_F      ,     // Displays "C"
        SEG_B+SEG_C+SEG_D+SEG_E+      SEG_G,     // Displays "d"
  SEG_A+           +SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "E"
  SEG_A+                  SEG_E+SEG_F+SEG_G,     // Displays "F"
//  SEG_A+      SEG_C+SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "G"
  SEG_A+SEG_B+SEG_C+SEG_D+      SEG_F+SEG_G,     // Displays "g"
        SEG_B+SEG_C+      SEG_E+SEG_F+SEG_G,     // Displays "H"
                          SEG_E+SEG_F      ,     // Displays "I"
  SEG_A+SEG_B+SEG_C+SEG_D                  ,     // Displays "J"
//  		SEG_B+SEG_C+      SEG_E+SEG_F+SEG_G,     // Displays "k"
  		     		SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "k"
                    SEG_D+SEG_E+SEG_F      ,     // Displays "L"
  SEG_A+SEG_B+SEG_C+      SEG_E+SEG_F      ,     // Displays "M"
              SEG_C+      SEG_E+      SEG_G,     // Displays "n"
              SEG_C+SEG_D+SEG_E+      SEG_G,     // Displays "o"
  SEG_A+SEG_B+            SEG_E+SEG_F+SEG_G,     // Displays "P"
  SEG_A+SEG_B+SEG_C+SEG_D+SEG_E+SEG_F      ,     // Displays "Q"
                          SEG_E+      SEG_G,     // Displays "r"
  SEG_A+      SEG_C+SEG_D+      SEG_F+SEG_G,     // Displays "S"
                    SEG_D+SEG_E+SEG_F+SEG_G,     // Displays "t"
              SEG_C+SEG_D+SEG_E            ,     // Displays "u"
              SEG_C+SEG_D+SEG_E            ,     // Displays "u"
                                      SEG_G,     // Displays "-"
        SEG_B+SEG_C+     +SEG_E+SEG_F+SEG_G,     // Displays "X"
        SEG_B+SEG_C+SEG_D+      SEG_F+SEG_G,     // Displays "Y"
  SEG_A+SEG_B+      SEG_D+SEG_E+      SEG_G,     // Displays "Z"
};

// Table with memory address for each display element
const unsigned * segments_lcdmem[] =
{
	LCD_SYMB_AM_MEM,
	LCD_SYMB_PM_MEM,
	LCD_SYMB_ARROW_UP_MEM,
	LCD_SYMB_ARROW_DOWN_MEM,
	LCD_SYMB_PERCENT_MEM,
	LCD_SYMB_TOTAL_MEM,
	LCD_SYMB_AVERAGE_MEM,
	LCD_SYMB_MAX_MEM,
	LCD_SYMB_BATTERY_MEM,
	LCD_UNIT_L1_FT_MEM,
	LCD_UNIT_L1_K_MEM,
	LCD_UNIT_L1_M_MEM,
	LCD_UNIT_L1_I_MEM,
	LCD_UNIT_L1_PER_S_MEM,
	LCD_UNIT_L1_PER_H_MEM,
	LCD_UNIT_L1_DEGREE_MEM,
	LCD_UNIT_L2_KCAL_MEM,
	LCD_UNIT_L2_KM_MEM,
	LCD_UNIT_L2_MI_MEM,
	LCD_ICON_HEART_MEM,
	LCD_ICON_STOPWATCH_MEM,
	LCD_ICON_RECORD_MEM,
	LCD_ICON_ALARM_MEM,
	LCD_ICON_BEEPER1_MEM,
	LCD_ICON_BEEPER2_MEM,
	LCD_ICON_BEEPER3_MEM,
	LCD_SEG_L1_3_MEM,
	LCD_SEG_L1_2_MEM,
	LCD_SEG_L1_1_MEM,
	LCD_SEG_L1_0_MEM,
	LCD_SEG_L1_COL_MEM,
	LCD_SEG_L1_DP1_MEM,
	LCD_SEG_L1_DP0_MEM,
	LCD_SEG_L2_5_MEM,
	LCD_SEG_L2_4_MEM,
	LCD_SEG_L2_3_MEM,
	LCD_SEG_L2_2_MEM,
	LCD_SEG_L2_1_MEM,
	LCD_SEG_L2_0_MEM,
	LCD_SEG_L2_COL1_MEM,
	LCD_SEG_L2_COL0_MEM,
	LCD_SEG_L2_DP_MEM,
};

// Table with bit mask for each display element
const unsigned segments_bitmask[] =
{
	LCD_SYMB_AM_MASK,
	LCD_SYMB_PM_MASK,
	LCD_SYMB_ARROW_UP_MASK,
	LCD_SYMB_ARROW_DOWN_MASK,
	LCD_SYMB_PERCENT_MASK,
	LCD_SYMB_TOTAL_MASK,
	LCD_SYMB_AVERAGE_MASK,
	LCD_SYMB_MAX_MASK,
	LCD_SYMB_BATTERY_MASK,
	LCD_UNIT_L1_FT_MASK,
	LCD_UNIT_L1_K_MASK,
	LCD_UNIT_L1_M_MASK,
	LCD_UNIT_L1_I_MASK,
	LCD_UNIT_L1_PER_S_MASK,
	LCD_UNIT_L1_PER_H_MASK,
	LCD_UNIT_L1_DEGREE_MASK,
	LCD_UNIT_L2_KCAL_MASK,
	LCD_UNIT_L2_KM_MASK,
	LCD_UNIT_L2_MI_MASK,
	LCD_ICON_HEART_MASK,
	LCD_ICON_STOPWATCH_MASK,
	LCD_ICON_RECORD_MASK,
	LCD_ICON_ALARM_MASK,
	LCD_ICON_BEEPER1_MASK,
	LCD_ICON_BEEPER2_MASK,
	LCD_ICON_BEEPER3_MASK,
	LCD_SEG_L1_3_MASK,
	LCD_SEG_L1_2_MASK,
	LCD_SEG_L1_1_MASK,
	LCD_SEG_L1_0_MASK,
	LCD_SEG_L1_COL_MASK,
	LCD_SEG_L1_DP1_MASK,
	LCD_SEG_L1_DP0_MASK,
	LCD_SEG_L2_5_MASK,
	LCD_SEG_L2_4_MASK,
	LCD_SEG_L2_3_MASK,
	LCD_SEG_L2_2_MASK,
	LCD_SEG_L2_1_MASK,
	LCD_SEG_L2_0_MASK,
	LCD_SEG_L2_COL1_MASK,
	LCD_SEG_L2_COL0_MASK,
	LCD_SEG_L2_DP_MASK,
};

//Line 1 Numbers
const unsigned char line1_num[] =
{
		L1_0,
		L1_1,
		L1_2,
		L1_3,
		L1_4,
		L1_5,
		L1_6,
		L1_7,
		L1_8,
		L1_9,
};

unsigned volatile flash;	//Keeps track of whether flashing segments are on or off.
unsigned volatile flash_counter;	//Keeps track of 1/4seconds for flashing segments

//FUNCTIONS

//Clear Line
void clear_line(unsigned line)
{
	display_chars(switch_seg(line, LCD_SEG_L1_3_0, LCD_SEG_L2_5_0), 0, SEG_OFF);
	if (line == LINE1)
	{
		display_symbol(LCD_SEG_L1_DP1, SEG_OFF);
		display_symbol(LCD_SEG_L1_DP0, SEG_OFF);
		display_symbol(LCD_SEG_L1_COL, SEG_OFF);
		clear_number(LCD_MEM_2);
		clear_number(LCD_MEM_3);
		clear_number(LCD_MEM_4);
	}
	else // line == LINE2
	{
		display_symbol(LCD_SEG_L2_DP, SEG_OFF);
		display_symbol(LCD_SEG_L2_COL1, SEG_OFF);
		display_symbol(LCD_SEG_L2_COL0, SEG_OFF);
		clear_number(LCD_MEM_8);
		clear_number(LCD_MEM_9);
		clear_number(LCD_MEM_10);
		clear_number(LCD_MEM_11);
	}
}

//Clear Display
void clear_display(void)
{
	clear_line(LINE1);
	clear_line(LINE2);
}

//LCD_initiate
void LCD_initiate (void)
{
	extern unsigned volatile flash;
	extern unsigned volatile flash_counter;

    // Clear entire display memory
	LCDBMEMCTL |= LCDCLRBM + LCDCLRM;

	// LCD_FREQ = ACLK/16/8 = 256Hz 
	// Frame frequency = 256Hz/4 = 64Hz, LCD mux 4, LCD on
	LCDBCTL0 = (LCDDIV0 + LCDDIV1 + LCDDIV2 + LCDDIV3) | (LCDPRE0 + LCDPRE1) | LCD4MUX | LCDON;

	// LCB_BLK_FREQ = ACLK/8/4096 = 1Hz
	LCDBBLKCTL = LCDBLKPRE0 | LCDBLKPRE1 | LCDBLKDIV0 | LCDBLKDIV1 | LCDBLKDIV2 | LCDBLKMOD0; 

	// I/O to COM outputs
	P5SEL |= (BIT5 | BIT6 | BIT7);
	P5DIR |= (BIT5 | BIT6 | BIT7);
  
	// Activate LCD output
	LCDBPCTL0 = 0xFFFF;  // Select LCD segments S0-S15
	LCDBPCTL1 = 0x00FF;  // Select LCD segments S16-S22

	clear_display(); //Avoids floating pins
	flash = 1;
	flash_counter = 1;
}

//Update Display
void update_display (void)
{
	extern unsigned volatile  time_elapsed[2];
	extern unsigned volatile counts_remaining;
	clear_display();
	update_counts_remaining();
	update_time_elapsed();
}

//Update Time Elapsed
void update_time_elapsed (void)
{
	extern unsigned volatile time_elapsed[2];
	unsigned TEM_10 = 0;
	unsigned TEM_1 = 0;
	unsigned TES_10 = 0;
	unsigned TES_1 = 0;

	TEM_1 = time_elapsed[0] % 10;
	TEM_10 = (time_elapsed[0] - TEM_1) / 10;
	display_number(LCD_MEM_11, TEM_10, 2);
	display_number(LCD_MEM_10, TEM_1, 2);

	display_symbol(LCD_SEG_L2_COL0, SEG_ON);

	TES_1 = time_elapsed[1] % 10;
	TES_10 = (time_elapsed[1] - TES_1) / 10;
	display_number(LCD_MEM_9, TES_10, 2);
	display_number(LCD_MEM_8, TES_1, 2);
}

//Update Counts Remaining
void update_counts_remaining (void)
{
	extern unsigned volatile counts_remaining;
	unsigned CR_100 = 0;
	unsigned CR_10 = 0;
	unsigned CR_1 = 0;

	CR_100 = counts_remaining / 100;
	CR_10 = ((counts_remaining % 100) / 10);
	CR_1 = counts_remaining % 10;

	display_number(LCD_MEM_2, CR_100, 1);
	display_number(LCD_MEM_3, CR_10, 1);
	display_number(LCD_MEM_4, CR_1, 1);
}

//Display Number
void display_number(unsigned int * LCD_MEM, unsigned num, unsigned line)
{
	unsigned char * lcdmem;
	unsigned int segs;
	segs = line1_num[num];

	if(line == 2)
	{
		unsigned segs1;
		segs1 = ((segs << 4) & 0xF0) | ((segs >> 4) & 0x0F);
		segs = segs1;
	}

	lcdmem = (unsigned char *) LCD_MEM;
	*lcdmem = (unsigned char)(*lcdmem | (segs));
}

//Clear Number
void clear_number(unsigned int * LCD_MEM)
{
	unsigned char * lcdmem;
	unsigned int segs;
	segs = L1_B;

	lcdmem = (unsigned char *) LCD_MEM;
	*lcdmem = (unsigned char)(*lcdmem & ~segs);
}

//Display Chars
void display_chars(unsigned segments, unsigned * str, unsigned mode)
{
	unsigned i;
	unsigned length = 0;			// Write length
	unsigned char_start;			// Starting point for consecutive write

	switch (segments)
	{
		// LINE1
		case LCD_SEG_L1_3_0:	length=4; char_start=LCD_SEG_L1_3; break;
		case LCD_SEG_L1_2_0:	length=3; char_start=LCD_SEG_L1_2; break;
		case LCD_SEG_L1_1_0: 	length=2; char_start=LCD_SEG_L1_1; break;
		case LCD_SEG_L1_3_1: 	length=3; char_start=LCD_SEG_L1_3; break;
		case LCD_SEG_L1_3_2: 	length=2; char_start=LCD_SEG_L1_3; break;

		// LINE2
		case LCD_SEG_L2_5_0:	length=6; char_start=LCD_SEG_L2_5; break;
		case LCD_SEG_L2_4_0:	length=5; char_start=LCD_SEG_L2_4; break;
		case LCD_SEG_L2_3_0:	length=4; char_start=LCD_SEG_L2_3; break;
		case LCD_SEG_L2_2_0:	length=3; char_start=LCD_SEG_L2_2; break;
		case LCD_SEG_L2_1_0: 	length=2; char_start=LCD_SEG_L2_1; break;
		case LCD_SEG_L2_5_4:	length=2; char_start=LCD_SEG_L2_5; break;
		case LCD_SEG_L2_5_2:	length=4; char_start=LCD_SEG_L2_5; break;
		case LCD_SEG_L2_3_2:	length=2; char_start=LCD_SEG_L2_3; break;
		case LCD_SEG_L2_4_2: 	length=3; char_start=LCD_SEG_L2_4; break;
	}

	// Write to consecutive digits
	for(i=0; i<length; i++)
	{
		// Use single character routine to write display memory
		display_char(char_start+i, *(str+i), mode);
	}
}

//Display Char
void display_char(unsigned segment, unsigned chr, unsigned mode)
{
	unsigned * lcdmem;			// Pointer to LCD memory
	unsigned bitmask;			// Bitmask for character
	unsigned bits, bits1;		// Bits to write

	// Write to single 7-segment character
	if ((segment >= LCD_SEG_L1_3) && (segment <= LCD_SEG_L2_DP))
	{
		// Get LCD memory address for segment from table
		lcdmem = (unsigned *)segments_lcdmem[segment];

		// Get bitmask for character from table
		bitmask = segments_bitmask[segment];

		// Get bits from font set
		if ((chr >= 0x30) && (chr <= 0x5A))
		{
			// Use font set
			bits = lcd_font[chr-0x30];
		}
		else if (chr == 0x2D)
		{
			// '-' not in font set
			bits = BIT1;
		}
		else
		{
			// Other characters map to ' ' (blank)
			bits = 0;
		}

		// When addressing LINE2 7-segment characters need to swap high- and low-nibble,
		// because LCD COM/SEG assignment is mirrored against LINE1
		if (segment >= LCD_SEG_L2_5)
		{
			bits1 = ((bits << 4) & 0xF0) | ((bits >> 4) & 0x0F);
			bits = bits1;

			// When addressing LCD_SEG_L2_5, need to convert ASCII '1' and 'L' to 1 bit,
			// because LCD COM/SEG assignment is special for this incomplete character
			if (segment == LCD_SEG_L2_5)
			{
				if ((chr == '1') || (chr == 'L')) bits = BIT7;
			}
		}

		// Physically write to LCD memory
		write_lcd_mem(lcdmem, bits, bitmask, mode);
	}
}

//Display symbol
void display_symbol(unsigned symbol, unsigned mode)
{
	unsigned * lcdmem;
	unsigned bits;
	unsigned bitmask;

	if (symbol <= LCD_SEG_L2_DP)
	{
		// Get LCD memory address for symbol from table
		lcdmem 	= (unsigned *)segments_lcdmem[symbol];

		// Get bits for symbol from table
		bits 	= segments_bitmask[symbol];

		// Bitmask for symbols equals bits
		bitmask = bits;

		// Write LCD memory
		write_lcd_mem(lcdmem, bits, bitmask, mode);
	}
}

//Write LCD Memory
void write_lcd_mem(unsigned * lcdmem, unsigned bits, unsigned bitmask, unsigned state)
{
	if (state == SEG_ON)
	{
		// Clear segments before writing
		*lcdmem = (unsigned)(*lcdmem & ~bitmask);

		// Set visible segments
		*lcdmem = (unsigned)(*lcdmem | bits);
	}
	else if (state == SEG_OFF)
	{
		// Clear segments
		*lcdmem = (unsigned)(*lcdmem & ~bitmask);
	}
	else if (state == SEG_ON_BLINK_ON)
	{
		// Clear visible / blink segments before writing
		*lcdmem 		= (unsigned)(*lcdmem & ~bitmask);
		*(lcdmem+0x20) 	= (unsigned)(*(lcdmem+0x20) & ~bitmask);

		// Set visible / blink segments
		*lcdmem 		= (unsigned)(*lcdmem | bits);
		*(lcdmem+0x20) 	= (unsigned)(*(lcdmem+0x20) | bits);
	}
	else if (state == SEG_ON_BLINK_OFF)
	{
		// Clear visible segments before writing
		*lcdmem = (unsigned)(*lcdmem & ~bitmask);

		// Set visible segments
		*lcdmem = (unsigned)(*lcdmem | bits);

		// Clear blink segments
		*(lcdmem+0x20) 	= (unsigned)(*(lcdmem+0x20) & ~bitmask);
	}
	else if (state == SEG_OFF_BLINK_OFF)
	{
		// Clear segments
		*lcdmem = (unsigned)(*lcdmem & ~bitmask);

		// Clear blink segments
		*(lcdmem+0x20) 	= (unsigned)(*(lcdmem+0x20) & ~bitmask);
	}
}

//Switch Segment
unsigned switch_seg(unsigned line, unsigned index1, unsigned index2)
{
	if (line == LINE1)
	{
		return index1;
	}
	else // line == LINE2
	{
		return index2;
	}
}

//Flash Heart
void flash_heart (void)
{
	extern unsigned volatile flash;
	extern unsigned volatile flash_counter;

	if ((flash_counter / 4) == 1)
	{
		if (flash == 1)
		{
			display_symbol(LCD_ICON_HEART, SEG_OFF);
			flash = 0;
		}
		else
		{
			display_symbol(LCD_ICON_HEART, SEG_ON);
			flash = 1;
		}
	}
	else
		++ flash_counter;

	if (flash_counter == 5)	//Stop flash counter getting too high.
		flash_counter = 1;
}


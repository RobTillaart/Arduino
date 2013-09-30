#ifndef VT100_h
#define VT100_h
//
//    FILE: VT100.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: VT100 codes, to be sent by serial.print() et al.
//    DATE: 2013-09-30
//     URL:
//
// Released to the public domain
//

// a sourcec of VT100 codes
// http://ascii-table.com/ansi-escape-sequences-vt-100.php


// CHAR MODES
#define OFF             "\033[0m"
#define BOLD            "\033[1m"
#define LOWINTENS       "\033[2m"
#define UNDERLINE       "\033[4m"
#define BLINK           "\033[5m"
#define REVERSE         "\033[7m"

// POSITIONING
#define CLS             "\033[2J"       // Esc[2J Clear entire screen
#define GOTOXY(x,y)    "\033[x;yH"     // Esc[Line;ColumnH
#define HOME            "\033[H"

#define CUD(x)          "\033[xB"      // Move cursor up n lines
// Esc[ValueA 	Move cursor up n lines 	    CUU
// Esc[ValueB 	Move cursor down n lines 	CUD
// Esc[ValueC 	Move cursor right n lines 	CUF
// Esc[ValueD 	Move cursor left n lines 	CUB



// ADDITIONAL CODES depend on terminal if supported.
/*
Esc[20h 	Set new line mode 	LMN
Esc[?1h 	Set cursor key to application 	DECCKM
none 	Set ANSI (versus VT52) 	DECANM
Esc[?3h 	Set number of columns to 132 	DECCOLM
Esc[?4h 	Set smooth scrolling 	DECSCLM
Esc[?5h 	Set reverse video on screen 	DECSCNM
Esc[?6h 	Set origin to relative 	DECOM
Esc[?7h 	Set auto-wrap mode 	DECAWM
Esc[?8h 	Set auto-repeat mode 	DECARM
Esc[?9h 	Set interlacing mode 	DECINLM

Esc[20l 	Set line feed mode 	LMN
Esc[?1l 	Set cursor key to cursor 	DECCKM
Esc[?2l 	Set VT52 (versus ANSI) 	DECANM
Esc[?3l 	Set number of columns to 80 	DECCOLM
Esc[?4l 	Set jump scrolling 	DECSCLM
Esc[?5l 	Set normal video on screen 	DECSCNM
Esc[?6l 	Set origin to absolute 	DECOM
Esc[?7l 	Reset auto-wrap mode 	DECAWM
Esc[?8l 	Reset auto-repeat mode 	DECARM
Esc[?9l 	Reset interlacing mode 	DECINLM

Esc= 	Set alternate keypad mode 	DECKPAM
Esc> 	Set numeric keypad mode 	DECKPNM

Esc(A 	Set United Kingdom G0 character set 	setukg0
Esc)A 	Set United Kingdom G1 character set 	setukg1
Esc(B 	Set United States G0 character set 	setusg0
Esc)B 	Set United States G1 character set 	setusg1
Esc(0 	Set G0 special chars. & line set 	setspecg0
Esc)0 	Set G1 special chars. & line set 	setspecg1
Esc(1 	Set G0 alternate character ROM 	setaltg0
Esc)1 	Set G1 alternate character ROM 	setaltg1
Esc(2 	Set G0 alt char ROM and spec. graphics 	setaltspecg0
Esc)2 	Set G1 alt char ROM and spec. graphics 	setaltspecg1

EscN 	Set single shift 2 	SS2
EscO 	Set single shift 3 	SS3

Esc[m 	Turn off character attributes 	SGR0
Esc[0m 	Turn off character attributes 	SGR0
Esc[1m 	Turn bold mode on 	SGR1
Esc[2m 	Turn low intensity mode on 	SGR2
Esc[4m 	Turn underline mode on 	SGR4
Esc[5m 	Turn blinking mode on 	SGR5
Esc[7m 	Turn reverse video on 	SGR7
Esc[8m 	Turn invisible text mode on 	SGR8

Esc[Line;Liner 	Set top and bottom lines of a window 	DECSTBM

Esc[ValueA 	Move cursor up n lines 	CUU
Esc[ValueB 	Move cursor down n lines 	CUD
Esc[ValueC 	Move cursor right n lines 	CUF
Esc[ValueD 	Move cursor left n lines 	CUB
Esc[H 	Move cursor to upper left corner 	cursorhome
Esc[;H 	Move cursor to upper left corner 	cursorhome
Esc[Line;ColumnH 	Move cursor to screen location v,h 	CUP
Esc[f 	Move cursor to upper left corner 	hvhome
Esc[;f 	Move cursor to upper left corner 	hvhome
Esc[Line;Columnf 	Move cursor to screen location v,h 	CUP
EscD 	Move/scroll window up one line 	IND
EscM 	Move/scroll window down one line 	RI
EscE 	Move to next line 	NEL
Esc7 	Save cursor position and attributes 	DECSC
Esc8 	Restore cursor position and attributes 	DECSC

EscH 	Set a tab at the current column 	HTS
Esc[g 	Clear a tab at the current column 	TBC
Esc[0g 	Clear a tab at the current column 	TBC
Esc[3g 	Clear all tabs 	TBC

Esc#3 	Double-height letters, top half 	DECDHL
Esc#4 	Double-height letters, bottom half 	DECDHL
Esc#5 	Single width, single height letters 	DECSWL
Esc#6 	Double width, single height letters 	DECDWL

Esc[K 	Clear line from cursor right 	EL0
Esc[0K 	Clear line from cursor right 	EL0
Esc[1K 	Clear line from cursor left 	EL1
Esc[2K 	Clear entire line 	EL2

Esc[J 	Clear screen from cursor down 	ED0
Esc[0J 	Clear screen from cursor down 	ED0
Esc[1J 	Clear screen from cursor up 	ED1
Esc[2J 	Clear entire screen 	ED2

Esc5n 	Device status report 	DSR
Esc0n 	Response: terminal is OK 	DSR
Esc3n 	Response: terminal is not OK 	DSR

Esc6n 	Get cursor position 	DSR
EscLine;ColumnR 	Response: cursor is at v,h 	CPR

Esc[c 	Identify what terminal type 	DA
Esc[0c 	Identify what terminal type (another) 	DA
Esc[?1;Value0c 	Response: terminal type code n 	DA

Escc 	Reset terminal to initial state 	RIS

Esc#8 	Screen alignment display 	DECALN
Esc[2;1y 	Confidence power up test 	DECTST
Esc[2;2y 	Confidence loopback test 	DECTST
Esc[2;9y 	Repeat power up test 	DECTST
Esc[2;10y 	Repeat loopback test 	DECTST

Esc[0q 	Turn off all four leds 	DECLL0
Esc[1q 	Turn on LED #1 	DECLL1
Esc[2q 	Turn on LED #2 	DECLL2
Esc[3q 	Turn on LED #3 	DECLL3
Esc[4q 	Turn on LED #4 	DECLL4


Codes for use in VT52 compatibility mode
Esc< 	Enter/exit ANSI mode (VT52) 	setansi

Esc= 	Enter alternate keypad mode 	altkeypad
Esc> 	Exit alternate keypad mode 	numkeypad

EscF 	Use special graphics character set 	setgr
EscG 	Use normal US/UK character set 	resetgr

EscA 	Move cursor up one line 	cursorup
EscB 	Move cursor down one line 	cursordn
EscC 	Move cursor right one char 	cursorrt
EscD 	Move cursor left one char 	cursorlf
EscH 	Move cursor to upper left corner 	cursorhome
EscLineColumn 	Move cursor to v,h location 	cursorpos(v,h)
EscI 	Generate a reverse line-feed 	revindex

EscK 	Erase to end of current line 	cleareol
EscJ 	Erase to end of screen 	cleareos

EscZ 	Identify what the terminal is 	ident
Esc/Z 	Correct response to ident 	identresp




VT100 Special Key Codes

These are sent from the terminal back to the computer when the particular key is pressed.
Note that the numeric keypad keys send different codes in numeric mode than in alternate mode.
See escape codes above to change keypad mode.



Function Keys:
EscOP	PF1
EscOQ	PF2
EscOR	PF3
EscOS	PF4



Arrow Keys:
    Reset 	Set
up 	EscA	EscOA
down 	EscB	EscOB
right 	EscC	EscOC
left 	EscD	EscOD



Numeric Keypad Keys:
EscOp	0
EscOq	1
EscOr	2
EscOs	3
EscOt	4
EscOu	5
EscOv	6
EscOw	7
EscOx	8
EscOy	9
EscOm	-(minus)
EscOl	,(comma)
EscOn	.(period)
EscOM	^M



Printing:
Esc[i 	Print Screen 	Print the current screen
Esc[1i	Print Line 	Print the current line
Esc[4i	Stop Print Log 	Disable log
Esc[5i	Start Print Log	Start log; all received text is echoed to a printer

*/

#endif
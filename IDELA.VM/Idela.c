/**
 *	MIT License
 *
 *	Copyright (c) 2020 r0da [r0da@protonmail.ch]
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in all
 *	copies or substantial portions of the Software.
 *
 * 	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * 	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *	SOFTWARE.
 */

#include "Dispatcher.h"
#include "Opcode.h"
#include "Includes.h"

byte opcode[] = {

	ISAVE8,   0,0,  '\0',
	ISAVE8,   1,0,  'L',
	ISAVE8,   2,0,  'I',
	ISAVE8,   3,0,  'A',
	ISAVE8,   4,0,  'F',
	ISAVE8,   5,0,  '\0', 
	ISAVE8,   6,0,  'N',
	ISAVE8,   7,0,  'I',
	ISAVE8,   8,0,  'W',

	IPUSH8,   '\0',		 
	IPUSH8,   ' ',
	IPUSH8,   ':',
	IPUSH8,   ' ',
	IPUSH8,   'G',
	IPUSH8,   'A',
	IPUSH8,   'L',
	IPUSH8,   'F',
	PRINTSS,

	CINPUT,   4, 

	ICALLS8,   12,

	ICMP8,    0x1,
	IJE8,	  65,

	PRINTHS,  4,0,
	EXIT,
	PRINTHS,  8,0,
	EXIT,

	ICMP8,    'W',
	IJNE8,	  90,
	IPOP8,	  1,
	ICMP8,    'O',
	IJNE8,	  90,
	IPOP8,	  1,
	ICMP8,    'W',
	IJNE8,	  90,

	IPUSH8,   0x1,
	RET,

	IPUSH8,   0x0,
	RET,
};

int main()
{
#ifdef _DEBUG
	printf("IDELA VM : Start\r\n");
#endif

	VM* vm;

	IDELA_Init(&vm, opcode, BYTE_ARRAY_SIZE(opcode), 0);

	IDELA_Start(vm);

	IDELA_Free(vm);

#ifdef _DEBUG
	printf("IDELA VM : Stop\r\n");
#endif
}
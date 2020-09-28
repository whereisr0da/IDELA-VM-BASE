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

#ifndef Handlers_h

#define Handlers_h

#include "Context.h"

void H_IPUSH8(VM* vm);
void H_ISAVE8(VM* vm);
void H_LOAD8(VM* vm);
void H_PRINTHS(VM* vm);
void H_CALL8(VM* vm);
void H_RET(VM* vm);
void H_ICALL8(VM* vm);
void H_ICALLS8(VM* vm);
void H_IADD8(VM* vm);
void H_ICMP8(VM* vm);
void H_IXOR8(VM* vm);
void H_IJMP8(VM* vm);
void H_IJE8(VM* vm);
void H_IJNE8(VM* vm);
void H_CMP8(VM* vm);
void H_PRINTS8X(VM* vm);
void H_PRINTSC(VM* vm);
void H_PRINTSS(VM* vm);
void H_IPUSH8(VM* vm);
void H_SAVE8(VM* vm);
void H_CINPUT(VM* vm);
void H_IPOP8(VM* vm);
void H_ISP8(VM* vm);
void H_ADD8(VM* vm);
void H_SUB8(VM* vm);
void H_XOR8(VM* vm);
void H_MULT8(VM* vm);
void H_IMULT8(VM* vm);

void HANDLE_Init();

#ifdef _WIN64
extern uint64 HANDLE_MAP[];
#else
extern uint32 HANDLE_MAP[];
#endif

extern int HANDLE_INDEX_OPCODE[HANDLE_MAP_SIZE];

#endif // !Handlers_h
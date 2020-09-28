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

#ifndef Constant_h

#define Constant_h

// Uncomment to debug your code

//#define SHOW_DISASSEMBLY
//#define SHOW_DISPATCHER
//#define SHOW_STACK
//#define SHOW_HEAP

#define SHOW_HEAP_LENGTH 20

#define STACK_SIZE		 0x500
#define HEAP_SIZE		 0xFFFF
#define CALL_STACK_SIZE  0x500
#define HANDLE_MAP_SIZE  0xFF

typedef __int32 int32;
typedef unsigned __int64 uint64;
typedef unsigned __int32 uint32;
typedef unsigned __int16 uint16;
typedef unsigned __int8 byte;

#define EXEC_HANDLE(OPCODE_ID,VM_OBJ) ((void(*)(VM*))(HANDLE_MAP[HANDLE_INDEX_OPCODE[OPCODE_ID]]))(VM_OBJ); 

#define BYTE_ARRAY_SIZE(ARRAY) (sizeof(ARRAY) / sizeof(byte))

#endif // !Constant_h
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

#ifndef Context_h

#define Context_h

#include "Constant.h"

// Execution context of the VM
typedef struct VM_CONTEXT {

	// Instruction pointer
	uint32 ip;
	// Stack pointer
	int32 sp;
	// Callstack pointer
	uint32 cp;
	// Heap storage (global storage)
	byte   heap[HEAP_SIZE];
	// Stack storage (local storage)
	byte   stack[STACK_SIZE];
	// Call stack (instruction pointer stack)
	uint32 callStack[CALL_STACK_SIZE];
	// VM running boolean
	byte   running;
	// Comparison register
	byte   comparisonRegister;
	// Pointer to opcode
	byte*  opcode;
	// Opcode size
	uint32 opcodeSize;
} VM;

#endif // !Context_h
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

#include "Handlers.h"
#include "Opcode.h"
#include "Includes.h"

#ifdef _WIN64
uint64 HANDLE_MAP[] = {
	(uint64)H_IPUSH8,
	(uint64)H_ISAVE8,
	(uint64)H_LOAD8,
	(uint64)H_PRINTHS,
	(uint64)H_CALL8,
	(uint64)H_RET,
	(uint64)H_ICALL8,
	(uint64)H_IADD8,
	(uint64)H_ICMP8,
	(uint64)H_IXOR8,
	(uint64)H_IJMP8,
	(uint64)H_IJE8,
	(uint64)H_IJNE8,
	(uint64)H_CMP8,
	(uint64)H_PRINTS8X,
	(uint64)H_PRINTSC,
	(uint64)H_PRINTSS,
	(uint64)H_ICALLS8,
	(uint64)H_SAVE8,
	(uint64)H_CINPUT,
	(uint64)H_IPOP8,
	(uint64)H_ISP8,
	(uint64)H_ADD8,
	(uint64)H_SUB8,
	(uint64)H_XOR8,
	(uint64)H_IMULT8,
	(uint64)H_MULT8,
};
#else
uint32 HANDLE_MAP[] = {
	(uint32)H_IPUSH8,
	(uint32)H_ISAVE8,
	(uint32)H_LOAD8,
	(uint32)H_PRINTHS,
	(uint32)H_CALL8,
	(uint32)H_RET,
	(uint32)H_ICALL8,
	(uint32)H_IADD8,
	(uint32)H_ICMP8,
	(uint32)H_IXOR8,
	(uint32)H_IJMP8,
	(uint32)H_IJE8,
	(uint32)H_IJNE8,
	(uint32)H_CMP8,
	(uint32)H_PRINTS8X,
	(uint32)H_PRINTSC,
	(uint32)H_PRINTSS,
	(uint32)H_ICALLS8,
	(uint32)H_SAVE8,
	(uint32)H_CINPUT,
	(uint32)H_IPOP8,
	(uint32)H_ISP8,
	(uint32)H_ADD8,
	(uint32)H_SUB8,
	(uint32)H_XOR8,
	(uint32)H_IMULT8,
	(uint32)H_MULT8,
};
#endif

int HANDLE_INDEX_OPCODE[HANDLE_MAP_SIZE];

void HANDLE_Init() {
	HANDLE_INDEX_OPCODE[IPUSH8] = 0;
	HANDLE_INDEX_OPCODE[ISAVE8] = 1;
	HANDLE_INDEX_OPCODE[LOAD8] = 2;
	HANDLE_INDEX_OPCODE[PRINTHS] = 3;
	HANDLE_INDEX_OPCODE[CALL8] = 4;
	HANDLE_INDEX_OPCODE[RET] = 5;
	HANDLE_INDEX_OPCODE[ICALL8] = 6;
	HANDLE_INDEX_OPCODE[IADD8] = 7;
	HANDLE_INDEX_OPCODE[ICMP8] = 8;
	HANDLE_INDEX_OPCODE[IXOR8] = 9;
	HANDLE_INDEX_OPCODE[IJMP8] = 10;
	HANDLE_INDEX_OPCODE[IJE8] = 11;
	HANDLE_INDEX_OPCODE[IJNE8] = 12;
	HANDLE_INDEX_OPCODE[CMP8] = 13;
	HANDLE_INDEX_OPCODE[PRINTS8X] = 14;
	HANDLE_INDEX_OPCODE[PRINTSC] = 15;
	HANDLE_INDEX_OPCODE[PRINTSS] = 16;
	HANDLE_INDEX_OPCODE[ICALLS8] = 17;
	HANDLE_INDEX_OPCODE[SAVE8] = 18;
	HANDLE_INDEX_OPCODE[CINPUT] = 19;
	HANDLE_INDEX_OPCODE[IPOP8] = 20;
	HANDLE_INDEX_OPCODE[ISP8] = 21;
	HANDLE_INDEX_OPCODE[ADD8] = 22;
	HANDLE_INDEX_OPCODE[SUB8] = 23;
	HANDLE_INDEX_OPCODE[XOR8] = 24;
	HANDLE_INDEX_OPCODE[IMULT8] = 25;
	HANDLE_INDEX_OPCODE[MULT8] = 26;
}

void H_IPOP8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : IPOP8 0x%x\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, vm->opcode[vm->ip]);
#endif

	// Prevent stack crashing
	if (vm->sp - vm->opcode[vm->ip] < 0)
		return;

	// Update the stack pointer
	vm->sp -= vm->opcode[vm->ip++];
}

void H_ISP8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : ISP8 0x%x\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, vm->opcode[vm->ip]);
#endif

	// Prevent int32 overflow
	if (vm->sp + vm->opcode[vm->ip] < 0)
		return;

	// Update the stack pointer
	vm->sp += vm->opcode[vm->ip++];
}

void H_CINPUT(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : CINPUT 0x%x\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, vm->opcode[vm->ip]);
#endif

	// Get the input length from opcode
	// Max size is 0xFF
	int inputLength = vm->opcode[vm->ip++];

	// Alloc a buffer for the input
	char* input = malloc(inputLength);

	// Get console input
	fgets(input, inputLength, stdin);

	// Push the reversed input on the stack
	for (int i = inputLength - 1; i > -1; i--)
		vm->stack[++vm->sp] = input[i];

	// Free the allocated buffer
	free(input);
}

void H_IADD8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : IADD8 0x%x\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, vm->opcode[vm->ip]);
#endif

	// Prevent stack crashing
	if (vm->sp < 0)
		return;

	// Get the immediate from opcode and add it to the stack top value
	vm->stack[vm->sp] += vm->opcode[vm->ip++];
}

void H_IMULT8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : IMULT8 0x%x\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, vm->opcode[vm->ip]);
#endif

	// Prevent stack crashing
	if (vm->sp < 0)
		return;

	// Get the immediate from opcode and multiply it to the stack top value
	vm->stack[vm->sp] *= vm->opcode[vm->ip++];
}

void H_MULT8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : MULT8\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1);
#endif

	// Prevent stack crashing
	if (vm->sp < 0 && vm->sp - 1 < 0)
		return;

	// Get the operand value from stack and multiply it to the stack top value
	vm->stack[vm->sp] *= vm->stack[vm->sp - 1];
}

void H_XOR8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : XOR8\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1);
#endif

	// Prevent stack crashing
	if (vm->sp < 0 && vm->sp - 1 < 0)
		return;

	// Get the operand value from stack and xor it to the stack top value
	vm->stack[vm->sp] ^= vm->stack[vm->sp - 1];
}

void H_ADD8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : ADD8\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1);
#endif

	// Prevent stack crashing
	if (vm->sp < 0 && vm->sp - 1 < 0)
		return;

	// Get the operand value from stack and add it to the stack top value
	vm->stack[vm->sp] += vm->stack[vm->sp-1];
}

void H_SUB8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : SUB8\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1);
#endif

	// Prevent stack crashing
	if (vm->sp < 0 && vm->sp - 1 < 0)
		return;

	// Get the operand value from stack and substract it to the stack top value
	vm->stack[vm->sp] -= vm->stack[vm->sp - 1];
}

void H_ICMP8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : ICMP8 0x%x\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, vm->opcode[vm->ip]);
#endif

	// Prevent stack crashing
	if (vm->sp < 0)
		return;

	// Set conditionRegister to the comparison of the last stack value and an immediate
	vm->comparisonRegister = vm->stack[vm->sp] == vm->opcode[vm->ip++];
}

void H_IXOR8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : IXOR8 0x%x\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, vm->opcode[vm->ip]);
#endif

	// Prevent stack crashing
	if (vm->sp < 0)
		return;

	// Get the immediate from opcode and xor it with the stack top value
	vm->stack[vm->sp] ^= vm->opcode[vm->ip++];
}

void H_IJMP8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : IJMP8 0x%x\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, vm->opcode[vm->ip]);
#endif

	// Change the instruction pointer to immediate from opcode
	vm->ip = vm->opcode[vm->ip];
}

void H_IJE8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : IJE8 0x%x\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, vm->opcode[vm->ip]);
#endif

	// Jump if the last comparison checked the conditionRegister
	if (vm->comparisonRegister)
		// Change the instruction pointer to immediate from opcode
		vm->ip = vm->opcode[vm->ip];
	// Otherwise jump to next instruction
	else
		++vm->ip;
}

void H_IJNE8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : IJNE8 0x%x\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, vm->opcode[vm->ip]);
#endif

	// Jump if the last comparison unchecked the conditionRegister
	if (!vm->comparisonRegister)
		// Change the instruction pointer to immediate from opcode
		vm->ip = vm->opcode[vm->ip];
	// Otherwise jump to next instruction
	else
		++vm->ip;
}

void H_CMP8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : CMP8\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1);
#endif

	// Prevent stack crashing
	if (vm->sp < 0 || vm->sp - 1 < 0)
		return;

	// Set conditionRegister to the comparison of the first stack value and the second
	vm->comparisonRegister = vm->stack[vm->sp] == vm->opcode[vm->sp - 1];
}

void H_PRINTS8X(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : PRINTS8X\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1);
#endif

	// Prevent stack crashing
	if (vm->sp < 0)
		return;

	// Print the last byte pushed on the stack
	printf("0x%x\r\n", vm->stack[vm->sp]);
}

void H_PRINTSC(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : PRINTSC\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1);
#endif

	// Prevent stack crashing
	if (vm->sp < 0)
		return;

	// Print the last character pushed on the stack
	printf("%c\r\n", vm->stack[vm->sp]);
}

void H_PRINTSS(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : PRINTSS\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1);
#endif

	// Prevent stack crashing
	if (vm->sp < 0)
		return;

	// Save a temporary stack pointer to not change the real one
	int stackPointer = vm->sp;

	// Print a null terminated string from the stack
	// NOTE : The stack pointer will return to the null terminator address
	while (vm->stack[stackPointer] != 0x00)
		printf("%c", vm->stack[stackPointer--]);
	printf("\r\n");
}

void H_IPUSH8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	byte value = vm->opcode[vm->ip];

	if (value >= 33 && value < 127)
		printf("[%04x] : IPUSH8 '%c'\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, value);
	else
		printf("[%04x] : IPUSH8 0x%x\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, value);
#endif

	// Get the immediate from opcode and push it on top of the stack
	vm->stack[++vm->sp] = vm->opcode[vm->ip++];
}

void H_RET(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : RET\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1);
#endif

	// Change ip to the stored ret instruction
	vm->ip = vm->callStack[--vm->cp];
}

void H_CALL8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : CALL8\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1);
#endif

	// Prevent stack crashing
	if (vm->sp < 0)
		return;

	// Get the next instruction executed after the function return
	uint32 returnPointer = vm->ip + 1;
	// Set the intruction pointer to the function from stack
	vm->ip = vm->stack[vm->sp];
	// Save the return pointer in the call stack
	vm->callStack[vm->cp++] = returnPointer;
}

void H_ICALL8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : ICALL8 0x%x\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, vm->opcode[vm->ip]);
#endif

	// Get the next instruction executed after the function return
	uint32 returnPointer = vm->ip + 1;
	// Set the intruction pointer to the function
	vm->ip = vm->opcode[vm->ip];
	// Save the return pointer in the call stack
	vm->callStack[vm->cp++] = returnPointer;
}

void H_ICALLS8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : ICALLS8 0x%x\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, vm->opcode[vm->ip]);
#endif

	// Get the next instruction executed after the function return
	uint32 returnPointer = vm->ip + 1;
	// Increase the intruction pointer to the function
	// NOTE : +1 because of the offset in opcode
	vm->ip += vm->opcode[vm->ip] + 1;
	// Save the return pointer in the call stack
	vm->callStack[vm->cp++] = returnPointer;
}

void H_ISAVE8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	byte value = vm->opcode[vm->ip+2];

	if (value >= 33 && value < 127)
		printf("[%04x] : ISAVE8 0x%x '%c'\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, *(uint16*)(vm->opcode + vm->ip), value);
	else
		printf("[%04x] : ISAVE8 0x%x 0x%x\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, *(uint16*)(vm->opcode + vm->ip), value);
#endif

	// Get heap object id from opcode
	uint16 id = *(uint16*)(vm->opcode + vm->ip);
	// Padding of heap id element 
	vm->ip += 2;
	// Save the immediate on the heap
	vm->heap[id] = vm->opcode[vm->ip++];
}

void H_SAVE8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : SAVE8 0x%x\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, *(uint16*)(vm->opcode + vm->ip));
#endif

	// Prevent stack crashing
	if (vm->sp < 0)
		return;

	// Get heap object id from opcode
	uint16 id = *(uint16*)(vm->opcode + vm->ip);
	// Padding of heap id element 
	vm->ip += 2;
	// Save the last stack value on the heap
	vm->heap[id] = vm->stack[vm->sp];
}


void H_LOAD8(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : LOAD8 0x%x\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, *(uint16*)(vm->opcode + vm->ip));
#endif

	// Get heap object id from opcode
	uint16 id = *(uint16*)(vm->opcode + vm->ip);
	// Padding of heap id element 
	vm->ip += 2;
	// Get the immediate from heap with the id and push it on the stack
	vm->stack[++vm->sp] = vm->heap[id];
}

void H_PRINTHS(VM* vm) {

#if(defined _DEBUG && defined SHOW_DISASSEMBLY)
	printf("[%04x] : PRINTHS 0x%x\r\n", vm->ip == 0 ? vm->ip : vm->ip - 1, *(uint16*)(vm->opcode + vm->ip));
#endif

	// Get heap object id from opcode
	uint16 id = *(uint16*)(vm->opcode + vm->ip);
	// Padding of heap id element 
	vm->ip += 2;
	// Print a null terminated string from the heap element id
	while (vm->heap[id] != 0x00)
		printf("%c", vm->heap[id--]);
	printf("\r\n");
}
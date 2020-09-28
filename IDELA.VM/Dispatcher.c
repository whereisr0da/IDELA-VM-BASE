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
#include "Handlers.h"
#include "Constant.h"
#include "Includes.h"

void IDELA_Init(VM** vm, byte* opcode, uint32 opcodeSize, uint32 entrypoint) {

	// Allocate the struct
	(*vm) = (VM*)malloc(sizeof(VM));
	// Allocate the opcode buffer
	(*vm)->opcode = (byte*)malloc(opcodeSize);
	(*vm)->opcodeSize = opcodeSize;
	// Copy the opcode in the allocated memory
	for (size_t i = 0; i < opcodeSize; i++)
		(*vm)->opcode[i] = opcode[i];
	// Set the ip to the entrypoint instruction
	(*vm)->ip = entrypoint;
	// Start the stack pointer at -1 (to get a clean stack)
	(*vm)->sp = -1;
	(*vm)->cp = 0;
	(*vm)->running = FALSE;
	(*vm)->comparisonRegister = FALSE;
	// It's better if the stack and heap are clean
	ZeroMemory((*vm)->stack, STACK_SIZE);
	ZeroMemory((*vm)->heap, HEAP_SIZE);
}

#ifdef _DEBUG

void IDELA_PrintStack(VM* vm) {

	printf("IDELA_PrintStack : Stack start\r\n");

	// Print the stack 
	for (size_t i = vm->sp; i != -1; i--)
	{
		// If the value is printable
		if(vm->stack[i] >= 33 && vm->stack[i] < 127)
			printf("[%04x] : %c\r\n", i, vm->stack[i]);
		else 
			printf("[%04x] : %02x\r\n", i, vm->stack[i]);
	}

	printf("IDELA_PrintStack : Stack end\r\n");
}

void IDELA_PrintHeap(VM* vm) {

	printf("IDELA_PrintStack : Heap start");

	// Print the heap 
	for (size_t i = 0; i < SHOW_HEAP_LENGTH; i++)
	{
		if(i == 0 || i % 6 == 0)
			printf("\r\n[%04x] : ", i);

		// If the value is printable
		if (vm->heap[i] >= 33 && vm->heap[i] < 127)
			printf("'%c ", vm->heap[i]);
		else
			printf("%02x ", vm->heap[i]);
	}

	printf("\r\n");

	printf("IDELA_PrintStack : Heap end\r\n");
}

#endif

void IDELA_Start(VM* vm) {

	// Update the vm stat
	vm->running = TRUE;

	HANDLE_Init();

	// Loop while there if opcode
	while (vm->ip != vm->opcodeSize && vm->running)
		IDELA_Dispatcher(vm);
}

void IDELA_Free(VM* vm) {

	// Prevent leaks
	ZeroMemory(vm->opcode, vm->opcodeSize);
	// Free allocations
	free(vm->opcode);
	free(vm);
	// Prevent use after free
	vm->opcode = NULL;
	vm = NULL;
}

void IDELA_Dispatcher(VM* vm) {

#ifdef _DEBUG

#ifdef SHOW_STACK
	if(vm->sp > -1)
		IDELA_PrintStack(vm);
#endif
#ifdef SHOW_HEAP
	IDELA_PrintHeap(vm);
#endif
#ifdef SHOW_DISPATCHER
	printf("IDELA_Dispatcher : Start IP 0x%x\r\n", vm->ip);
#endif

#endif

	// Get the next opcode identifier
	byte identifier = vm->opcode[vm->ip++];

#if(defined _DEBUG && defined SHOW_DISPATCHER)
	printf("IDELA_Dispatcher : Identifier 0x%x\r\n", identifier);
#endif

	// Handle exit opcode
	if (identifier == EXIT) {
		vm->running = FALSE;
		return;
	}

	// Handle all other opcode
	switch (identifier)
	{ 
	case IPUSH8:
		EXEC_HANDLE(IPUSH8, vm)
		break;
	case CALL8:
		EXEC_HANDLE(CALL8, vm)
		break;
	case RET:
		EXEC_HANDLE(RET, vm)
		break;
	case ICALLS8:
		EXEC_HANDLE(ICALLS8, vm)
		break;
	case ICALL8:
		EXEC_HANDLE(ICALL8, vm)
		break;
	case IADD8:
		EXEC_HANDLE(IADD8, vm)
		break;
	case IXOR8:
		EXEC_HANDLE(IXOR8, vm)
		break;
	case IMULT8:
		EXEC_HANDLE(IMULT8, vm)
		break;
	case MULT8:
		EXEC_HANDLE(MULT8, vm)
		break;
	case XOR8:
		EXEC_HANDLE(XOR8, vm)
		break;
	case SUB8:
		EXEC_HANDLE(SUB8, vm)
		break;
	case ADD8:
		EXEC_HANDLE(ADD8, vm)
		break;
	case IJMP8:
		EXEC_HANDLE(IJMP8, vm)
		break;
	case IJE8:
		EXEC_HANDLE(IJE8, vm)
		break;
	case IJNE8:
		EXEC_HANDLE(IJNE8, vm)
		break;
	case ICMP8:
		EXEC_HANDLE(ICMP8, vm)
		break;
	case CMP8:
		EXEC_HANDLE(CMP8, vm)
		break;
	case ISAVE8:
		EXEC_HANDLE(ISAVE8, vm)
		break;
	case LOAD8:
		EXEC_HANDLE(LOAD8, vm)
		break;
	case SAVE8:
		EXEC_HANDLE(SAVE8, vm)
		break;
	case CINPUT:
		EXEC_HANDLE(CINPUT, vm)
		break;
	case PRINTS8X:
		EXEC_HANDLE(PRINTS8X, vm)
		break;
	case PRINTSC:
		EXEC_HANDLE(PRINTSC, vm)
		break;
	case PRINTSS:
		EXEC_HANDLE(PRINTSS, vm)
		break;
	case PRINTHS:
		EXEC_HANDLE(PRINTHS, vm)
		break;
	case IPOP8:
		EXEC_HANDLE(IPOP8, vm)
		break;
	case ISP8:
		EXEC_HANDLE(ISP8, vm)
		break;
	default:

#if(defined _DEBUG && defined SHOW_DISPATCHER)
		printf("IDELA_Dispatcher : Invalid identifier 0x%x at IP 0x%x\r\n", vm->ip);
#endif
		vm->running = FALSE;

		return;
	}

#if(defined _DEBUG && defined SHOW_DISPATCHER)
	printf("IDELA_Dispatcher : Next IP 0x%x\r\n", vm->ip);
#endif
}
# IDELA INSTRUCTION SET :

	// Push immediate on the stack (value in opcode)
	// FORMAT : ID(UINT8) IMM(UINT8)
	IPUSH8 = 0x00,

	// Pop a number of 8 bits (an immediate) elements of the stack
	// EXAMPLE : IPOP8 5 = vm->sp -= 5
	// FORMAT : ID(UINT8) IMM(UINT8)
	IPOP8 = 0x01,

	// Increase stack pointer from the top with an immediate
	// EXAMPLE : SP 3 = vm->sp += 3
	// FORMAT : ID(UINT8) IMM(UINT8)
	ISP8 = 0x02,

	// Save immediate on heap from heap id
	// FORMAT : ID(UINT8) ID(UINT16) IMM(UINT8)
	// TODO : Fix heap id max (short)
	ISAVE8 = 0x03,

	// Save 8 bits stack value on heap from heap id
	// FORMAT : ID(UINT8) ID(UINT16)
	// TODO : Fix heap id max (short)
	SAVE8 = 0x04,

	// Load heap data from heap data id to the stack
	// FORMAT : ID(UINT8) HEAP_ID(UINT16)
	// TODO : Fix heap id max (short)
	LOAD8 = 0x05,

	// Multiply an immediate (value in opcode) of 8 bits to stack top value
	// FORMAT : ID(UINT8) IMM(UINT8)
	IMULT8 = 0x34,

	// Multiply a value from the stack (sp-1) of 8 bits to stack top value
	// FORMAT : ID(UINT8)
	MULT8 = 0x35,

	// Add an immediate (value in opcode) of 8 bits to stack top value
	// FORMAT : ID(UINT8) IMM(UINT8)
	IADD8 = 0x06,

	// Add a value from the stack (sp-1) of 8 bits to stack top value
	// FORMAT : ID(UINT8)
	ADD8 = 0x4A,

	// Subtract an immediate (value in opcode) of 8 bits to stack top value
	// FORMAT : ID(UINT8) IMM(UINT8)
	ISUB8 = 0x07,

	// Subtract a value from the stack (sp-1) of 8 bits to stack top value
	// FORMAT : ID(UINT8)
	SUB8 = 0x4B,

	// Xor an immediate (value in opcode) of 8 bits to stack top value
	// FORMAT : ID(UINT8) IMM(UINT8)
	IXOR8 = 0xAA,

	// Xor a value from the stack (sp-1) of 8 bits to stack top value
	// FORMAT : ID(UINT8)
	XOR8 = 0xAB,

	// Jump to absolute opcode index of 8 bits from opcode
	// FORMAT : ID(UINT8) INDEX(UINT8)
	IJMP8 = 0x09,

	// Jump if, the comparison register is set to false, to absolute opcode index of 8 bits from opcode
	// FORMAT : ID(UINT8) INDEX(UINT8)
	IJNE8 = 0x0A,

	// Jump if, the comparison register is set to true, to absolute opcode index of 8 bits from opcode
	// FORMAT : ID(UINT8) INDEX(UINT8)
	IJE8 = 0x11,

	// Compare a value of 8 bits on the stack and an immediate in opcode. Set the comparison register in function of the result
	// FORMAT : ID(UINT8) IMM(UINT8)
	ICMP8 = 0x12,

	// Compare two value of 8 bits on the stack and set the comparison register accordingly
	// FORMAT : ID(UINT8)
	CMP8 = 0x13,

	// Function return
	// FORMAT : ID(UINT8)
	RET = 0x14,

	// Exit the program
	// FORMAT : ID(UINT8)
	EXIT = 0x15,

	// Do nothing
	// FORMAT : ID(UINT8)
	NOP = 0x16,

	// Call function from absolute opcode index of 8 bits on the stack
	// FORMAT : ID(UINT8)
	CALL8 = 0x17,

	// Call function from absolute opcode index of 8 bits immediate in opcode
	// FORMAT : ID(UINT8) INDEX(UINT8)
	ICALL8 = 0x18,

	// Call function from short opcode offset of 8 bits immediate in opcode
	// FORMAT : ID(UINT8) OFFSET(UINT8)
	ICALLS8 = 0x19,

	// Print 8 bits value as hex from stack
	// FORMAT : ID(UINT8)
	PRINTS8X = 0x56,

	// Print 8 bit value as char from stack
	// FORMAT : ID(UINT8)
	PRINTSC = 0x57,

	// Print C string from stack (null terminated)
	// NOTE : Don't forget to put the null terminator (\0)
	// FORMAT : ID(UINT8)
	PRINTSS = 0x72,

	// Print C string from heap (null terminated)
	// NOTE : Don't forget to put the null terminator (\0)
	// FORMAT : ID(UINT8) HEAP_ID(UINT16)
	PRINTHS = 0x73,

	// Get console input with a max size in opcode
	// FORMAT : ID(UINT8) SIZE(UINT8)
	// NOTE : Max size is 0xFF
	CINPUT = 0x79,

Remaining intructions :
	
	// TODO : DIV8, OR8, AND8, IJB, IJBE, IJL, IJE
	// TODO : PRINTS16X, PRINTS32X, PRINTS64X
	// TODO : ICALL16, ICALL32, ICALL64
	// TODO : CALL16, CALL32, CALL64
	// TODO : CMP16, CMP32, CMP64
	// TODO : ICMP16, ICMP32, ICMP64
	// TODO : IMULT16, IMULT32, IMULT64
	// TODO : MULT16, MULT32, MULT64
	// TODO : IJE16, IJE32, IJE64
	// TODO : JE8, JE16, JE32, JE64
	// TODO : IJNE16, IJNE32, IJNE64
	// TODO : JNE8, JNE16, JNE32, JNE64
	// TODO : IJMP16, IJMP32, IJMP64
	// TODO : JMP8, JMP16, JMP32, JMP64
	// TODO : IXOR16, IXOR32, IXOR64
	// TODO : XOR16, XOR32, XOR64
	// TODO : ICALLS16, ICALLS32, ICALLS64
	// TODO : ISUB16, ISUB32, ISUB64
	// TODO : SUB16, SUB32, SUB64
	// TODO : IADD16, IADD32, IADD64
	// TODO : ADD16, ADD32, ADD64
	// TODO : IPUSH16, IPUSH32, IPUSH64
	// TODO : ISAVE16, ISAVE32, ISAVE64
	// TODO : SAVE16, SAVE32, SAVE64
	// TODO : LOAD16, LOAD32, LOAD64
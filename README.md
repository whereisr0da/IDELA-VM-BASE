# IDELA VM BASE

This is a simple C vm with a simple interpreted language.

It's a "base" vm that will be improved using obfuscation and polymothism in the future.

This is more a POC than an accurate vm made to code complexes programs.

# Instructions

The instruction set is simple but "huge" for obfuscation purposes. A diversified instruction set is needed to make the opcode buffer less repetitive. It's why I'm doing one instruction per operation length (IPUSH8, IPUSH16, ...) unlike x86 or others.

Instructions are separated in two parts :

- Instructions with operand value in opcode (immediate values)
- Instructions with identifier only

[See the Instruction set documentation](INSTRUCTION_SET.md)

# Program examples

Simple console input comparison : 

	MAIN:
		ISAVE8,   0,0,  '\0',	# SAVE "FAIL\0" STRING ON THE HEAP
		ISAVE8,   1,0,  'L',
		ISAVE8,   2,0,  'I',
		ISAVE8,   3,0,  'A',
		ISAVE8,   4,0,  'F',	
		ISAVE8,   5,0,  '\0',	# SAVE "WIN\0" STRING ON THE HEAP
		ISAVE8,   6,0,  'N',
		ISAVE8,   7,0,  'I',
		ISAVE8,   8,0,  'W',
		IPUSH8,   '\0',			# PUSH EACH "FLAG : \0" CHARACTER ON THE STACK
		IPUSH8,   ' ',
		IPUSH8,   ':',
		IPUSH8,   ' ',
		IPUSH8,   'G',
		IPUSH8,   'A',
		IPUSH8,   'L',
		IPUSH8,   'F',
		PRINTSS,				# PRINT THE NULL TERMINATED STRING ON THE STACK
		CINPUT,   4, 			# GET 4 CHAR FROM THE STDIN ('\n' INCLUDED) TO THE STACK
		ICALLS8,   12,			# CALL THE CHECK_FUNCTION 12 BYTES ABOVE
		ICMP8,    0x1,			# IF THE FUNCTION RETURN 1
		IJE8,	  65,			# JUMP IF EQUAL TO INSTRUCTION 65 (PRINT_WIN)
	PRINT_FAIL:
		PRINTHS,  4,0,			# PRINT HEAP STRING AT ID 4, PRINT "FAIL\0"
		EXIT,					# EXIT THE PROGRAM
	PRINT_WIN:
		PRINTHS,  8,0,			# PRINT HEAP STRING AT ID 8, PRINT "WIN\0"
		EXIT,					# EXIT THE PROGRAM

	CHECK_FUNCTION:
		ICMP8,    'W',			# COMPARE THE FIRST CHAR TO 'W'
		IJNE8,	  90,			# JUMP IF NOT EQUAL TO INSTRUCTION 90 (FAIL)
		IPOP8,	  1,			# POP THE STACK POINTER OF 1 BYTE, POP TO THE NEXT STACK CHAR
		ICMP8,    'O',			# COMPARE THE SECOND CHAR TO 'O'
		IJNE8,	  90,			# JUMP IF NOT EQUAL TO INSTRUCTION 90 (FAIL)
		IPOP8,	  1,			# POP THE STACK POINTER OF 1 BYTE, POP TO THE NEXT STACK CHAR
		ICMP8,    'W',			# COMPARE THE THIRD CHAR TO 'O'
		IJNE8,	  90,			# JUMP IF NOT EQUAL TO INSTRUCTION 90 (FAIL)
	VALID:
		IPUSH8,   0x1,			# PUSH 1 ON THE STACK, RETURN TRUE
		RET,					# FUNCTION'S RETURN
	FAIL:
		IPUSH8,   0x0,			# PUSH 0 ON THE STACK, RETURN FALSE
		RET,					# FUNCTION'S RETURN

# License
[This code is published on MIT License](https://fr.wikipedia.org/wiki/Licence_MIT)

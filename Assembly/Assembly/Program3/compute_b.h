.NOLIST
.386

EXTRN compute_b_proc : Near32

compute_b MACRO array_addr, degree, extra_operands
	IFB <array_addr>
		.ERR <missing "array_addr" operand in compute_b>
	ELSEIFB <degree>
		.ERR <missing "degree" operand in compute_b>
	ELSEIFNB <extra_operands>
		.ERR <extra operand(s) in compute_b>
	ELSE
		push eax
		push array_addr
		push degree
		mov eax, 0 ;clear eax register
		push ax ;m value
		call compute_b_proc ;procedure call
		pop eax ;pop eax off the stack
	ENDIF
ENDM

.NOLISTMACRO
.LIST
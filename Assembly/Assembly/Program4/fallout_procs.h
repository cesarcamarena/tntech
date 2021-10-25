.NOLIST
.386

EXTRN num_matches_proc:Near32
EXTRN fallout_swap_proc:Near32

num_matches MACRO source, dest, xtra
	IFB <source>
		.ERR <missing "source" operand in num_matches>
	ELSEIFB <dest>
		.ERR <missing "dest" operand in num_matches>
	ELSEIFNB <xtra>
		.ERR <extra operand(s) in num_matches>
	ELSE

	push ebx
		push source
		push dest
		call num_matches_proc
	pop ebx

ENDIF
ENDM

fallout_swap MACRO source, dest, xtra
	IFB <source>
		.ERR <missing "source" operand in fallout_swap>
	ELSEIFB <dest>
		.ERR <missing "dest" operand in fallout_swap>
	ELSEIFNB <xtra>
		.ERR <extra operand(s) in fallout_swap>
	ELSE
	
	push ebx
		push source
		push dest
		call fallout_swap_proc
	pop ebx

ENDIF
ENDM

.NOLISTMACRO
.LIST
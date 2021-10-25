.NOLIST
.386

EXTRN interpolate_proc : Near32

interpolate MACRO array_name, x_coordinate, degree, destination, extra_operands
	IFB <array_name>
		.ERR <missing "array_name" operand in interpolate>
	ELSEIFB <x_coordinate>
		.ERR <missing "x_coordinate" operand in interpolate>
	ELSEIFB <degree>
		.ERR <missing "degree" operand in interpolate>
	ELSEIFB <destination>
		.ERR <missing "destination" operand in interpolate>
	ELSEIFNB <extra_operands>
		.ERR <extra operand(s) in interpolate>
	ELSE
		output carriage
		push ebx
		lea ebx, array_name
		push ebx
		push x_coordinate
		push degree
		call interpolate_proc ;call procedure
		pop ebx
		fstp destination
	ENDIF
ENDM

.NOLISTMACRO
.LIST
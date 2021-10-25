.386
.MODEL FLAT
ExitProcess PROTO NEAR32 stdcall, dwExitCode:DWORD
.STACK 4096

INCLUDE io.h
INCLUDE debug.h
INCLUDE float.h
INCLUDE sort_points.h
INCLUDE interpolate.h

.DATA
points_array		REAL4 40 DUP(?)

x_real				REAL4 ?
answer				REAL4 ?
tol					REAL4 0.0001

degree				WORD ?
num_points			WORD ?

x 					BYTE 8 DUP(?)
x_poly				BYTE 8 DUP(?)
point 				BYTE 8 DUP(?)

prompt_1			BYTE "Enter the x-coordinate of the desired interpolated y:", 0
prompt_2			BYTE "Enter the degree of the interpolated degreenomial:", 0
prompt_3			BYTE "You may enter up to 20 points, one at a time.", 0
prompt_4			BYTE "Input q to quit", 0
prompt_res			BYTE "The result: ", 0
prompt_q			BYTE "q", 0

feedback			BYTE 50 DUP(?)

_input MACRO array_name
	local new_point, done

	;get x-coordinate
	output carriage
	output prompt_1
	output carriage
	input x, 8
	atof x, x_real
	output x
	output carriage

	;get degree
	output prompt_2
	output carriage
	input x_poly, 8
	atoi x_poly
	mov degree, ax
	output x_poly
	output carriage

	;get points
	output prompt_3
	output carriage
	output prompt_4
	output carriage
	output carriage

	lea ebx, array_name
	mov ecx, 0 ;points counter

	new_point:
		input point, 8
		cmp point, 'q'
		je done
		output point
		output carriage

		atof point, REAL4 PTR [ebx]
		add ebx, 4
		add ecx, 1
		cmp ecx, 20
		jl new_point

	done:
		output prompt_q
		output carriage
		shr cx, 1
		mov num_points, cx
		output carriage
ENDM

_result MACRO ans
	ftoa ans, 5, 11, ans
	output prompt_res
	output ans
	output carriage
ENDM

.CODE
	_start:
		_input points_array
		sort_points points_array, x_real, tol, num_points
		print_points points_array, num_points
		interpolate points_array, x_real, degree, answer
		_result answer

INVOKE ExitProcess, 0
PUBLIC _start
END
;Program 1 By Cesar Camarena

.386
.MODEL FLAT

ExitProcess PROTO NEAR32 stdcall, dwExitCode:DWORD

INCLUDE io.h
INCLUDE debug.h
INCLUDE sqrt.h

cr 	EQU	0dh
Lf	EQU	0ah

.STACK  4096

.DATA

;Eyepoint Variables
eyepointE_locationX			WORD ?
eyepointE_locationY			WORD ?
eyepointE_locationZ			WORD ?

;Atpoint Variables
atpointA_locationX			WORD ?
atpointA_locationY			WORD ?
atpointA_locationZ			WORD ?

;Upvector Variables
upvectorVUP_locationX		WORD ?
upvectorVUP_locationY		WORD ?
upvectorVUP_locationZ		WORD ?

;N computation
nx							WORD ?
ny							WORD ?
nz							WORD ?
nlength						WORD ?

;temp variables for dot product
temp 						WORD ?
temp2 						WORD ?

;V computation
vx 							WORD ?
vy 							WORD ?
vz 							WORD ?
vlength 					WORD ?

;U computation
ux 							WORD ?
uy 							WORD ?
uz 							WORD ?
ulength						WORD ?

;Prompts
eyepoint_promptX			BYTE "Enter the x-coordinate of the camera eyepoint:		", 0
eyepoint_promptY			BYTE "Enter the y-coordinate of the camera eyepoint:		", 0
eyepoint_promptZ			BYTE "Enter the z-coordinate of the camera eyepoint:		", 0

atpointA_promptX			BYTE "Enter the x-coordinate of the camera look at point:		", 0
atpointA_promptY			BYTE "Enter the y-coordinate of the camera look at point:		", 0
atpointA_promptZ			BYTE "Enter the z-coordinate of the camera look at point:		", 0

upvector_promptX			BYTE "Enter the x-coordinate of the camera up direction:		", 0
upvector_promptY			BYTE "Enter the y-coordinate of the camera up direction:		", 0
upvector_promptZ			BYTE "Enter the x-coordinate of the camera up direction:		", 0

;Displays Prompt
display_prompt				BYTE 40 DUP (?)

;Displays Vector
display_n  					BYTE "n:", CR, LF
        					BYTE 37 DUP(?), 0

;Formats the fractions
display_result MACRO x, y, z, length, display1, text
	mov  display1+37, ')'
	itoa display1+31, length
	mov  display1+33, '/'
	itoa display1+27, z
	mov  display1+26, ','
	itoa display1+20, length
	mov  display1+22, '/'
	itoa display1+16, y
	mov  display1+15, ','
	itoa display1+9, length
	mov  display1+11, '/'
	itoa display1+5, x
	mov  display1+4, '('
	mov  display1, text

	output display_n
	output carriage

	ENDM

;Calculates dot product
dot_product MACRO x, y, z, length, temp
	mov ax, x
	imul x
	mov temp, ax

	mov ax, y
	imul y
	add temp, ax

	mov ax, z
	imul z
	add temp, ax

	sqrt temp

	mov length,ax

	ENDM


.CODE
_start:
	;Grabs input from text file
	inputW eyepoint_promptX, eyepointE_locationX
	outputW eyepointE_locationX
	inputW eyepoint_promptY, eyepointE_locationY
	outputW eyepointE_locationY
	inputW eyepoint_promptZ, eyepointE_locationZ
	outputW eyepointE_locationZ

	;Formats the numbers
	mov  display_prompt+21, ')'
	itoa display_prompt+15, eyepointE_locationZ
	mov  display_prompt+14, ','
	itoa display_prompt+8, eyepointE_locationY
	mov  display_prompt+7, ','
	itoa display_prompt+1, eyepointE_locationX
	output display_prompt
	output carriage

	inputW atpointA_promptX, atpointA_locationX
	outputW atpointA_locationX
	inputW atpointA_promptY, atpointA_locationY
	outputW atpointA_locationY
	inputW atpointA_promptZ, atpointA_locationZ
	outputW atpointA_locationZ

	mov  display_prompt+21, ')'
	itoa display_prompt+15, atpointA_locationZ
	mov  display_prompt+14, ','
	itoa display_prompt+8, atpointA_locationY
	mov  display_prompt+7, ','
	itoa display_prompt+1, atpointA_locationX
	output display_prompt
	output carriage

	inputW upvector_promptX, upvectorVUP_locationX
	outputW upvectorVUP_locationX
	inputW upvector_promptY, upvectorVUP_locationY
	outputW upvectorVUP_locationY
	inputW upvector_promptZ, upvectorVUP_locationZ
	outputW upvectorVUP_locationZ

	mov  display_prompt+21, ')'
	itoa display_prompt+15, upvectorVUP_locationZ
	mov  display_prompt+14, ','
	itoa display_prompt+8, upvectorVUP_locationY
	mov  display_prompt+7, ','
	itoa display_prompt+1, upvectorVUP_locationX
	output display_prompt
	output carriage

	;Calculates N
	mov ax, eyepointE_locationX
	sub ax, atpointA_locationX
	mov nx, ax

	mov ax, eyepointE_locationY
	sub ax, atpointA_locationY
	mov ny, ax

	mov ax, eyepointE_locationZ
	sub ax, atpointA_locationZ
	mov nz, ax

	dot_product nx, ny, nz, nlength, temp

	;Calculates V
	mov ax, upvectorVUP_locationX
	imul nx
	mov temp2, ax

	mov ax, upvectorVUP_locationY
	imul ny
	add temp2, ax

	mov ax, upvectorVUP_locationZ
	imul nz
	add temp2, ax

	mov ax, temp
	imul upvectorVUP_locationX
	mov vx, ax
	mov ax, temp2
	imul nx
	sub vx, ax

	mov ax, temp
	imul upvectorVUP_locationY
	mov vy, ax
	mov ax, temp2
	imul ny
	sub vy, ax

	mov ax, temp
	imul upvectorVUP_locationZ
	mov vz, ax
	mov ax, temp2
	imul nz
	sub vz, ax

	dot_product vx, vy, vz, vlength, temp

	;Calculates U
	mov ax, vy
	imul nz
	mov ux, ax
	mov ax, vz
	imul ny
	sub ux, ax

	mov ax, vz
	imul nx
	mov uy, ax
	mov ax, vx
	imul nz
	sub uy, ax

	mov ax, vx
	imul ny
	mov uz, ax
	mov ax, vy
	imul nx
	sub uz, ax

	;Displays everything
	dot_product ux, uy, uz, ulength, temp

	display_result ux, uy, uz, ulength, display_n, 'u'

	display_result vx, vy, vz, vlength, display_n, 'v'

	display_result nx, ny, nz, nlength, display_n, 'n'

	INVOKE ExitProcess, 0

	PUBLIC _start
END
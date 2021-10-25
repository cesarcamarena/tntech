.386
.MODEL FLAT

ExitProcess PROTO NEAR32 stdcall, dwExitCode:DWORD

INCLUDE io.h
INCLUDE debug.h
INCLUDE fallout_procs.h

MAX		EQU 25
LEN		EQU 13

.STACK 4096

.DATA

count 			DWORD ?
curr 			DWORD ?
compare 		DWORD ?

index 			DWORD ?
matches 		WORD ?
num 			WORD ?
total 			WORD ?

str_array BYTE MAX * LEN DUP (?)

input_string	BYTE LEN DUP(?)
string			BYTE "Enter a string: ", 0
num_str			BYTE "The number of strings entered is ", 0
index_prompt	BYTE "Enter the index for the test password (1-based): ", 0
matches_prompt 	BYTE "Enter the number of exact character matches: ", 0


.CODE

_start:

	;MACRO TO PRINT OUT STRINGS
	print_strings MACRO array_name, num_strings
		mov ecx, 0
		lea ebx, array_name
		print_loop_start:
			cmp cx, num_strings
			jge print_loop_finished
			output BYTE PTR [ebx]
			output carriage
			inc cx
			add ebx, LEN
			jmp print_loop_start
		print_loop_finished:
	ENDM

	lea ebx, str_array
	mov ecx, 0

	;OUTPUT THE INPUT THE FIRST TIME AROUND
	loop_start:
		cmp cx, WORD PTR MAX
		jg loop_finished
		output string
		input BYTE PTR [ebx], LEN
		output BYTE PTR [ebx]
		output carriage
		cmp BYTE PTR [ebx], 'x'
		je loop_finished
		inc cx
		add ebx, LEN
		jmp loop_start
	loop_finished:

	;PRINTS OUT NUMBER OF STRINGS INPUT/OUTPUT
	mov total, cx
	mov num, cx
	output carriage
	output num_str
	outputW cx
	output carriage

	;LOOPS TO PRINT OUT PASSWORDS, GET INDEX, GET NUM MATCHES, DO HACKING STUFF AND LOOP
	loop_begins:

		print_strings str_array, num

		cmp num, 1
		jle loop_ends ;final exit

		;GETS THE INPUT/OUTPUT FOR INDEX
		output index_prompt
		input input_string, LEN
		output input_string
		atod input_string
		mov index, eax

		output carriage

		;GETS THE INPUT/OUTPUT FOR MATCHES
		output 	matches_prompt
		input 	input_string, LEN
		output 	input_string
		atoi 	input_string
		mov 	matches, ax

		output carriage
		output carriage

		;(index - 1) x LEN
		sub 	index, 1		;index - 1
		mov 	eax, index 		;store it in eax
		mov 	ebx, LEN 		;store LEN in edx
		mul 	ebx 			;((index - 1) x LEN)
		mov 	index, eax

		lea 	esi, str_array
		mov 	count, esi
		mov 	curr, esi
		add 	esi, index

		;SETTING UP THE COMPARE WORD
		mov 	eax, 0
		mov 	ax, total
		mov 	ebx, LEN
		mul 	ebx 			;(total x LEN)
		
		lea 	edi, str_array
		add 	edi, eax
		mov 	compare, edi

		fallout_swap compare, esi

		mov cx, num
		mov num, 0
		swap_loop:
			cmp cx, 0
			je swap_done
			;mov esi, curr
			;output BYTE PTR [esi]
			num_matches curr, compare
			;outputW WORD PTR 123
			cmp matches, ax
			jne	next

			swap_word:
				fallout_swap count, curr
				inc num
				add count, LEN

			next:
				dec cx
				add curr, LEN

		jmp swap_loop

		swap_done:

		jmp loop_begins

	loop_ends:

INVOKE ExitProcess, 0
PUBLIC _start
END
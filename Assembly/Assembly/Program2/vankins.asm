.386
.MODEL FLAT

ExitProcess PROTO NEAR32 stdcall, dwExitCode:DWORD

INCLUDE io.h
INCLUDE debug.h

CR	EQU	0Dh
LF	EQU	0Ah

MAXNBRS   EQU   100

.STACK    4096

.DATA

matrix_addr    DWORD    MAXNBRS DUP (?) 
ArrayShift    DWORD    8       DUP (?) 
Nrow          WORD     8       DUP (?)
Mcolumn       WORD     8       DUP (?)
MandNTotal    WORD     8       DUP (?)
string        BYTE     8       DUP (?)
lineOut       BYTE     200     DUP (?)
StrRight      BYTE     "r", 0
StrDown       BYTE     "d", 0

.CODE
getMandN	MACRO Nrow, Mcolumn
    input  string, 8
    atod   string
    mov    Nrow, AX
    input  string, 8
    atod   string
    mov    Mcolumn, AX
    ENDM

getElement MACRO Nrow, Mcolumn, MandNTotal, matrix_addr
    LOCAL body, whileNotDone, endWhile
    mul   Nrow
    mov   MandNTotal, AX
    mov   DI, 0
    lea EBX, matrix_addr
    whileNotDone: cmp  DI, MandNTotal
          jl  short body
          jmp endWhile
    body:
        input string, 8
        atod  string
        mov [ebx], eax
        cmp SI, Mcolumn
        add   ebx, 4
        inc   DI
        jmp  whileNotDone
    endWhile:
    ENDM

displayMatrix MACRO Mcolumn, MandNTotal, matrix_addr
   LOCAL Mcolumn, MandNTotal, matrix_addr, whileNotFinish, body, endWhile, NotEndLine, EndLine, theNext
   lea EBX, matrix_addr
   mov DI, 0
   mov SI, 1
   whileNotFinish: cmp DI, MandNTotal
            jl short body
            jmp short endWhile
   body:
        cmp SI, Mcolumn
        jl  short NotEndLine
        jmp short EndLine
        NotEndLine:
            itoa lineOut, [ebx]
            output lineOut
            inc SI
            jmp short theNext
        EndLine:
            mov SI, 1
            itoa lineOut, [ebx]
            output lineOut
            output carriage
        theNext:
        add ebx, 4
        inc DI
        jmp whileNotFinish
   endWhile:
   output carriage 
   ENDM

setElement MACRO Nrow, Mcolumn, MandNTotal, matrix_addr
   lea EBX, matrix_addr
   mov EDI, EBX
   mov AX, 4
   mul MandNTotal
   movzx EAX, AX
   add EBX, EAX
   sub EBX, 4
   mov ArrayShift, EBX
   mov SI, Mcolumn
   whileStillFilling: cmp EBX, EDI
            jnl FillSquare
            jmp Finished
   FillSquare:
        cmp SI, 1
        jl  AddESICol
        jmp continueOn
        AddESICol:
            add SI, Mcolumn
            jmp continueOn
        continueOn:
        cmp EBX, ArrayShift
        je RightBottom
        jmp NotRightBottom
        RightBottom:
            sub EBX, 4
            dec SI
            jmp whileStillFilling
        NotRightBottom:
            cmp SI, Mcolumn
            je RightSide
            jmp CheckBottom
            RightSide:
                mov AX, 4
                mul Mcolumn
                movzx EAX, AX
                mov EDX, EBX
                add EBX, EAX
                jg AddToSquare
                jmp DecreaseEBX
                AddToSquare:
                    mov ECX, [EBX]
                    mov EBX, EDX          
                    mov EDX, [EBX]        
                    mov EAX, ECX          
                    add EAX, EDX          
                    mov DWORD PTR [EBX], EAX
                    sub EBX, 4
	                dec SI
                    jmp whileStillFilling
                DecreaseEBX:
                    dec SI
                    mov EBX, EDX
                    sub EBX, 4
                    jmp whileStillFilling
            CheckBottom:
                mov AX, 4
                mul Mcolumn 
                movzx EAX, AX
                mov ECX, EAX
                mov EAX, ArrayShift
                sub EAX, ECX
                cmp EBX, EAX
                jge AtBottom
                jmp NotAtBottomOrRight
                AtBottom:
                    dec SI
                    cmp DWORD PTR [EBX + 4], 0
                    jg AddToGrid2
                    jmp DecreaseEBX2
                    AddToGrid2:
                        mov ECX, [EBX]
                        mov EDX, [EBX + 4]
                        mov EAX, ECX
                        add EAX, EDX
                        mov DWORD PTR [EBX], EAX
                    DecreaseEBX2:
                        sub EBX, 4
                        jmp whileStillFilling
                NotAtBottomOrRight:
                    dec SI
                    mov ECX, [EBX + 4]
                    mov AX, 4
                    mul Mcolumn
                    movzx EAX, AX
                    add EAX, EBX 
                    mov EDX, EBX 
                    mov EBX, EAX 
                    mov EAX, [EBX] 
                    mov EBX, EDX  
                    mov EDX, EAX  
                    cmp ECX, EDX   
                    jge AddRight
                    jmp AddBottom
                    AddRight:
                        add ECX, [EBX] 
                        mov DWORD PTR [EBX], ECX
                        sub EBX, 4
                        jmp whileStillFilling
                    AddBottom:                         
                        add EDX, [EBX]
                        mov DWORD PTR [EBX], EDX
                        sub EBX, 4
                        jmp whileStillFilling
   Finished:
   ENDM

findAndDisplayPath MACRO Mcolumn, Nrow, matrix_addr
   LOCAL whileLoop, NotFinished, StillNotFinished, GoRight, GoDown
   lea EBX, matrix_addr
   mov DI, 1
   mov SI, 1
   whileLoop: cmp DI, Nrow
        jl NotFinished
        jmp AtBottomRow
        NotFinished:
           cmp SI, Mcolumn
           jl  StillNotFinished
           jmp AtBottomColumn
           StillNotFinished:
                mov ECX, [EBX + 4]     
                mov AX, 4
                mul Mcolumn
                movzx EAX, AX
                mov EDX, EBX
                add EBX, EAX
                mov EAX, [EBX]
                cmp ECX, EAX
                jge GoRight
                jmp GoDown
                GoRight:
                   mov EBX, EDX
                   add EBX, 4
                   inc SI
                   output StrRight
                   jmp whileLoop
                GoDown:
                   mov EBX, EDX
                   mov AX, 4
                   mul Mcolumn
                   movzx EAX, AX
                   add EBX, EAX
                   inc DI
                   output StrDown
                   jmp whileLoop               
           AtBottomColumn:
                mov AX, 4
                mul Mcolumn
                movzx EAX, AX
                add EBX, EAX
                cmp DWORD PTR [EBX], 0
                jge GoDown2
                jmp GoRightEnd
                GoDown2: 
                   output StrDown
                   inc DI
                   jmp whileLoop
                GoRightEnd:
                   output StrRight
                   inc SI
                   jmp DonePath
        AtBottomRow:
            cmp SI, Mcolumn
            jle CheckMore
            jmp DonePath
            CheckMore:
                mov EAX, [EBX + 4]
                cmp DWORD PTR EAX, 0
                jge GoRight2
                jmp GoDownEnd
                GoRight2:
                  output StrRight
                  inc SI
                  jmp whileLoop
                GoDownEnd:
                  output StrDown
                  inc DI
                  jmp DonePath
     DonePath:
   ENDM

_start:
    getMandN           Nrow, Mcolumn
    getElement       Nrow, Mcolumn, MandNTotal, matrix_addr
    displayMatrix   Mcolumn, MandNTotal, matrix_addr
    setElement  Nrow, Mcolumn, MandNTotal, matrix_addr
    displayMatrix   Mcolumn, MandNTotal, matrix_addr
    findAndDisplayPath Mcolumn, Nrow, matrix_addr
    output carriage
    output carriage
    
    INVOKE	  ExitProcess, 0

PUBLIC _start

END
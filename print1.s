; Compilation instructions:
; nasm -f macho64 print1.s
; gcc -m64 -mmacosx-version-min=10.6 -isysroot /Developer/SDKs/MacOSX10.7.sdk/ -o print1 print1.o


SECTION .data

; Variables
	a	  dd	5
fmt   db 'a=%d, b=%d', 10, 0

SECTION .text
  GLOBAL _main
  extern _printf

align 4, db 0x90

_main:

push  qword rbp		    ; set up stack frame
mov   rbp, rsp

mov   rdi, qword fmt	; address of ctrl string
mov   eax, 2
mov   rsi, 432        ; second parameter: %d
mov   rdx, 1024       ; third parameter
call  _printf

mov	  eax,0		        ;  normal, no error, return value
leave
ret			; return
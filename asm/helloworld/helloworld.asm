section .data
    hello_msg db "Hello, World!", 0AH, "This is my first program.", 0AH, "In Assembly :D", 0AH
    msg_end:

section .text
    global _start

_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, hello_msg
    mov edx, msg_end - hello_msg
    int 0x80
    
    mov eax, 1
    xor ebx, ebx
    int 0x80

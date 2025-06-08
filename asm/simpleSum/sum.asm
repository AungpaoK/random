section .text
global _start

_start:

  mov rax, 5
  mov rbx, 7
  
  mov rcx, rax
  add rcx, rbx

  mov rax, 60
  mov rdi, rcx
  syscall

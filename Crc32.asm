section .text
global _my_crc32



;----------------------------------------------------------------------------
;uint32_t my_crc32(char* x, unsigned long len)
;DAMEGED: RAX, R11
;IN:    RDI = pointer to word
;       RSI = len word
;============================================================================
_my_crc32:
    xor rax, rax
    mov eax, -1
    mov r11, 0
Next_iter:
    crc32 eax, byte [rdi + r11]
    inc r11
    cmp r11, rsi
    jb Next_iter
    ret
;============================================================================

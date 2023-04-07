; compilar con: nasm -f elf32 multiplicador.asm
segment .text
       global convert

convert:
; Argumento: número a multiplicar en el registro EAX
        enter   0,0 
        push    ebx               ; Por la convencion de C hay que mantener intacto ebx

        mov     eax,[ebp+8]       ; eax = moneda_fuente
        mul     dword [ebp+12]    ; edx:eax = eax * moneda_destino

        pop     ebx               ; volvemos ebx
        leave
        ret

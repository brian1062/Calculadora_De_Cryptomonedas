; compilar con: nasm -f elf32 multiplicador.asm
segment .text
       global convert

convert:
; Argumento: número a multiplicar en el registro EAX
        enter   0,0 
        push    ebx               ; Por la convencion de C hay que mantener intacto ebx
       

        fld     dword [ebp+8]
        fld     dword [ebp+12]
        fmul    st1, st0
        fstp    dword [ebp+8]

        pop     ebx               ; volvemos ebx
        leave
        ret

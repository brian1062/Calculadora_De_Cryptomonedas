; compilar con: nasm -f elf32 multiplicador.asm
segment .text
       global convert

convert:
; Argumento: número a multiplicar en el registro EAX
        enter   0,0
        ;push    ebx                ; Por la convencion de C hay que mantener intacto ebx

        fld     dword [ebp+8]      ; Carga un float_32 en la pila de la FPU desde la direccion apuntada por ebp mas ocho bits
        fld     dword [ebp+12]     ; Carga el un float_32 en la pila de la FPU desde la direccion apuntada por ebp mas doce bits
        fmul    st1, st0           ;
        fstp    dword [ebp+8]

        ;pop     ebx               ; volvemos ebx
        leave
        ret

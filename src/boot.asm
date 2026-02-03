; src/boot.asm
bits 32                 ; Мы в 32-битном режиме (Protected Mode)
section .multiboot      ; Заголовок для GRUB
    dd 0x1BADB002       ; Магическое число (чтобы GRUB нас нашел)
    dd 0x0              ; Флаги
    dd - (0x1BADB002 + 0x0) ; Контрольная сумма

section .text
global start
extern kernel_main      ; Эту функцию мы напишем на C

start:
    cli                 ; Отключаем прерывания (пока мы не умеем их обрабатывать)
    mov esp, stack_space ; Настраиваем стек
    call kernel_main    ; Прыгаем в код на C!
    hlt                 ; Если C вернул управление (чего быть не должно), стопим процессор

section .bss
resb 8192               ; Выделяем 8 КБ под стек
stack_space:

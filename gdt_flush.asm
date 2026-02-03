; src/gdt_flush.asm
global gdt_flush    ; Делаем функцию доступной для C кода

gdt_flush:
    mov eax, [esp+4]  ; Получаем адрес таблицы GDT, который передал C код
    lgdt [eax]        ; Загружаем новую таблицу (Load GDT)

    mov ax, 0x10      ; 0x10 — это адрес Сегмента Данных в нашей таблице
    mov ds, ax        ; Обновляем все регистры данных
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp 0x08:.flush   ; Дальний прыжок (Far Jump) для обновления Кодового сегмента (0x08)
.flush:
    ret               ; Возвращаемся в ядро

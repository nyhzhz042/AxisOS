/* linker.ld */
ENTRY(start)

SECTIONS
{
    . = 1M; /* Ядра обычно грузятся с 1-го мегабайта */

    .text :
    {
        *(.multiboot)
        *(.text)
    }

    .data :
    {
        *(.data)
    }

    .bss :
    {
        *(.bss)
    }
}

/* src/kernel.c - AxisOS v0.0.2 Fixed */
#include <stdint.h> 
#include <stddef.h> // <--- ВОТ ЭТОЙ СТРОКИ НЕ ХВАТАЛО!

// --- НАСТРОЙКИ ТЕРМИНАЛА ---
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

// Цвета
enum VgaColor {
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_LIGHT_BROWN = 14,
    COLOR_WHITE = 15,
};

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

// --- ФУНКЦИИ ---

uint8_t vga_entry_color(enum VgaColor fg, enum VgaColor bg) {
    return fg | bg << 4;
}

uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

void terminal_initialize(void) {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(COLOR_LIGHT_CYAN, COLOR_BLACK);
    terminal_buffer = (uint16_t*) 0xB8000;

    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_column = 0;
        terminal_row++;
    } else {
        terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
        terminal_column++;
        if (terminal_column == VGA_WIDTH) {
            terminal_column = 0;
            terminal_row++;
        }
    }
}

void terminal_writestring(const char* data) {
    for (size_t i = 0; data[i] != '\0'; i++)
        terminal_putchar(data[i]);
}

// --- ГЛАВНАЯ ФУНКЦИЯ ---
void kernel_main(void) {
    terminal_initialize();

    terminal_writestring("AxisOS Kernel v0.0.2 Alpha\n");
    terminal_writestring("--------------------------\n");
    
    terminal_color = vga_entry_color(COLOR_GREEN, COLOR_BLACK);
    terminal_writestring("[OK] Video driver loaded.\n");
    
    terminal_color = vga_entry_color(COLOR_WHITE, COLOR_BLACK);
    terminal_writestring("[OK] Core system initialized.\n");
    
    terminal_color = vga_entry_color(COLOR_LIGHT_RED, COLOR_BLACK);
    terminal_writestring("[WARNING] No keyboard detected (Not implemented yet).\n");

    terminal_color = vga_entry_color(COLOR_LIGHT_BLUE, COLOR_BLACK);
    terminal_writestring("\n");
    terminal_writestring("    /\\   |  |  |  /  \n");
    terminal_writestring("   /  \\  |  |  |  \\  \n");
    terminal_writestring("  / -- \\  \\/   |  /  \n");
    
    while(1);
}

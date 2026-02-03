/* src/gdt.c */
#include <stdint.h>

// Структура одной записи GDT (8 байт)
// Она описывает права доступа к памяти
struct gdt_entry_struct {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
} __attribute__((packed)); // Запрещаем компилятору добавлять лишние байты

// Указатель на GDT (для процессора)
struct gdt_ptr_struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// Создаем массив из 3 записей (Null, Code, Data)
struct gdt_entry_struct gdt_entries[3];
struct gdt_ptr_struct   gdt_ptr;

// Объявляем внешнюю функцию из ассемблера
extern void gdt_flush(uint32_t);

// Функция для заполнения одной записи (настройка битов)
void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
    gdt_entries[num].base_low    = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high   = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low   = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access      = access;
}

// Главная функция инициализации
void init_gdt() {
    // Указываем размер и адрес таблицы
    gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * 3) - 1;
    gdt_ptr.base  = (uint32_t)&gdt_entries;

    // 0: NULL Descriptor (Обязательно должен быть нулем, требование процессора)
    gdt_set_gate(0, 0, 0, 0, 0);

    // 1: Code Segment (Здесь живет код ядра)
    // База=0, Лимит=4ГБ, Доступ=0x9A (Read/Exec), Флаги=0xCF
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // 2: Data Segment (Здесь живут данные)
    // База=0, Лимит=4ГБ, Доступ=0x92 (Read/Write), Флаги=0xCF
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // Загружаем таблицу!
    gdt_flush((uint32_t)&gdt_ptr);
}

# AxisOS 🎯
> **Current Version:** v0.0.3 Alpha (GDT Implemented)

**AxisOS** is a custom operating system kernel written from scratch in **C** and **Assembly**, designed for the x86 architecture.

## 🚀 Features Status
| Feature | Status | Description |
| :--- | :---: | :--- |
| **Bootloader** | ✅ | Multiboot compliant (GRUB) |
| **Video Driver** | ✅ | VGA Text Mode (80x25) & Color Support |
| **GDT** | ✅ | Global Descriptor Table initialized |
| **Logs** | ✅ | System status messages & ASCII Logo |
| **IDT** | ⏳ | Interrupt Descriptor Table (*In Progress*) |
| **Keyboard** | ⏳ | Input driver (*Coming soon*) |

## 🧠 Latest Update (v0.0.3)
In this release, the **Global Descriptor Table (GDT)** was successfully implemented. This is a critical step for memory management and stability.
- **Kernel:** Defines Code and Data segments.
- **Stability:** Protected Mode is fully active.

## 🛠 How to Build
To build `axis.iso` from source:

1. **Install dependencies:** `nasm`, `gcc`, `xorriso`, `qemu`.
2. **Compile & Link:**
```bash
nasm -f elf32 src/boot.asm -o boot.o
nasm -f elf32 src/gdt_flush.asm -o gdt_flush.o
gcc -m32 -ffreestanding -c src/kernel.c -o kernel.o
gcc -m32 -ffreestanding -c src/gdt.c -o gdt.o
ld -m elf_i386 -T linker.ld -o axis.bin boot.o kernel.o gdt.o gdt_flush.o
```
Run in QEMU:
```bash
qemu-system-x86_64 -cdrom axis.iso
```

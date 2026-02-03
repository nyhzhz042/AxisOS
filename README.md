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
   # See build instructions in the repository
```
Run in QEMU:
```bash
qemu-system-x86_64 -cdrom axis.iso
```

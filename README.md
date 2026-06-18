# 🚀 ESP32 Mini OS (Embedded Terminal Command Line)

An efficient, lightweight embedded terminal-based operating system built from scratch for the **ESP32 Dev Module** using the **PlatformIO ecosystem** and the **Arduino Framework**.

This system features a custom CLI (Command Line Interface), an interactive dual-line 16x2 I2C LCD dashboard, and a lightweight, persistent Virtual File System (VFS) powered by **LittleFS**. It is optimized for high efficiency, complete memory stability, and allows full system interaction directly from your laptop keyboard via Serial communication.

---

## 🛠️ System Architecture & Features

* **Native Storage Engine (LittleFS):** Utilizes a custom, optimized partition table (`no_ota.csv`) giving the device a stable 2MB storage sector for creating, reading, and managing persistent files.
* **Custom CLI Processor:** Interprets real-time continuous byte streams from standard inputs, supporting Backspace buffers and executing custom Unix-like console applications.
* **WDT (Watchdog) Protection:** Employs precise tasks handling to safely disable and feed the hardware Watchdog during heavy Flash-formatting cycles to eliminate spontaneous boot-loops.
* **I2C LCD Real-time Dashboard:** Displays live kernel states, user terminal buffers, and prompt execution logs on a 16x2 matrix display.

---

## 🗂️ Supported Shell Commands

### `help`

* **Syntax:** `help`
* **Description:** Lists all active kernel commands and system apps.

### `status`

* **Syntax:** `status`
* **Description:** Queries the core, logging the CPU clock and checking live Free Heap RAM.

### `ls`

* **Syntax:** `ls`
* **Description:** Indexes and prints all active, persistent file names in the root directory.

### `echo`

* **Syntax:** `echo [Text] > [filename]`
* **Description:** Streams, creates, or overwrites custom string records into a designated file.

### `cat`

* **Syntax:** `cat [filename]`
* **Description:** Reads, handles, and prints the raw data bytes stored inside a specified file.

---

## 🚀 Getting Started

### Hardware Requirements

* **Microcontroller:** ESP32 Dev Module (ESP-WROOM-32).
* **Display:** LiquidCrystal 16x2 LCD with an I2C backpack interface.

### Connections

| LCD Pin | ESP32 GPIO |
| --- | --- |
| **SDA** | GPIO 21 |
| **SCL** | GPIO 22 |
| **VCC** | 5V |
| **GND** | GND |

### Project Configuration (`platformio.ini`)

Ensure your environment registry is correctly configured. Replace your `platformio.ini` with the following configuration:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
board_build.filesystem = littlefs
board_build.partitions = no_ota.csv
lib_deps =
    marcoschwartz/LiquidCrystal_I2C @ ^1.1.4

```

### Installation & Deployment

1. Connect your ESP32 board to your computer via a stable USB cable.
2. In VS Code, close any active Serial Monitors to prevent port conflicts (COM).
3. Click the **Upload Arrow** (`->`) at the bottom status bar to flash the system.
4. Once the upload is successful, open the **Serial Monitor** (Plug Icon).
5. Set your terminal baud rate to **115200** with **Both NL & CR** formatting enabled.
6. Start typing your commands directly using your laptop keyboard!

---

## 📂 Project Structure

```text
├── .pio/                 # PlatformIO build artifacts and libraries
├── include/              # Header declarations
├── src/
│   └── main.cpp          # Main OS Kernel and loop architectures
├── platformio.ini        # Advanced system configurations
└── README.txt            # Project documentation

```

---

## 🔧 Kernel Debugging Notes

> 💡 **First Boot Optimization:** On its first launch or after changing partitions, the system will automatically claim the flash sectors and initiate a strict formatting routine. The LCD will read `"Formatting Flash... (Pls Wait)"`. This is a one-time process.

> ⚠️ **VFS Perms Error:** If you notice any vfs_api mount warnings, the system's embedded logic will cleanly wipe and rebuild the root nodes using the `no_ota` map safely.

---

## 📄 License

This project is open-source and free to be cloned, modified, or integrated into custom hardware projects. Enjoy hacking! 💻🔥
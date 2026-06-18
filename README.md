
# 🚀 ESP32 Minimal Terminal Operating System (Core Shell v3.5)

An ultra-lightweight, high-efficiency embedded terminal operating system built from scratch for the **ESP32 Dev Module**. Optimized exclusively for pure Serial interface interaction, this system eliminates all external LCD dependencies to focus maximum clock performance on CLI stream processing and persistent data management via **LittleFS**.

Features a custom command line prompt, an interactive micro text editor (nano clone), dynamic horizontal ASCII Art banner generation, and a localized Virtual File System (VFS).

---

## 🛠️ System Architecture & Features

* **Native Storage Engine (LittleFS):** Utilizes a custom non-OTA partition table layout (`no_ota.csv`) providing a reliable persistent sector on flash memory for creating, appending, and removing user files.
* **Line-Buffer Stream Processor:** Captures raw keyboard byte streams over UART, natively handles Backspace buffer echoes (`\b \b`) for live corrections, and parses tokens for app routing.
* **Embedded Nano Editor:** A dedicated modal application within the shell that intercepts system hooks to let you write multi-line text directly to flash memory until an `EXIT` flag is triggered.
* **Horizontal ASCII Renderer:** A layout logic that slices matrix character buffers into parallel rows to render beautiful side-by-side graphical titles horizontally across the terminal.

---

## 🗂️ Core 10 Shell Commands Menu

| Command | Syntax / Usage | Description |
| :--- | :--- | :--- |
| **help** | `help` | Lists all available built-in commands and descriptions. |
| **pwd** | `pwd` | Prints the active virtual working directory root (`/root`). |
| **ls** | `ls` | Scans and indexes all persistent filenames found in flash storage. |
| **touch** | `touch [filename]` | Creates a fresh, empty file layout node inside LittleFS. |
| **nano** | `nano [filename]` | Launches the interactive text editor to write line-by-line data. |
| **banner** | `banner [word]` | Transforms any string into a wide horizontal ASCII Art display. |
| **cat** | `cat [filename]` | Reads, handles, and streams raw text data directly to standard output. |
| **rm** | `rm [filename]` | Deletes a target file and completely deallocates its flash sectors. |
| **free** | `free` | Queries physical Heap RAM stability and outputs active file system bytes. |
| **clear** | `clear` | Pushes a clear sequence layout to wipe clean the stdout Terminal buffer. |
| **reboot** | `reboot` | Performs a clean software micro-restart of the ESP32 core controller. |

---

## 💾 Advanced I/O Redirection

The CLI processor supports advanced Unix-like stream redirection tokens:

### 1. Overwrite Token ( `>` )
* **Syntax:** `echo [your message] > [filename]`
* **Action:** Erases previous data and saves a fresh record into the designated file.

### 2. Append Token ( `>>` )
* **Syntax:** `echo [your message] >> [filename]`
* **Action:** Persists the string into the final block of the file without destroying old content.

---

## 🚀 Getting Started & Deployment

### 1. Hardware Requirements
* **Microcontroller:** ESP32 Dev Module (ESP-WROOM-32).
* **Core Wiring:** Just attach your ESP32 directly via a stable USB Data Cable (No LCD needed).

### 2. Project Configuration (`platformio.ini`)
Ensure your PlatformIO configuration matches this minimal footprint:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200
board_build.filesystem = littlefs
board_build.partitions = no_ota.csv

```

### 3. Installation & Booting

1. Fire up VS Code and hit the Upload Arrow (`->`) on the status bar to flash the system.
2. Open the Serial Monitor (Plug Icon) immediately after a successful upload.
3. Ensure your monitor baud rate is set to `115200` with **Both NL & CR** formatting enabled.
4. Hit **Enter** once to receive the secure `root@esp32:~#` terminal prompt!

---

## 📂 Project Directory Structure

```text
├── .pio/                 # PlatformIO cache and target build targets
├── include/              # Modular architecture header folders
├── src/
│   └── main.cpp          # Main OS Kernel Core and Shell Loop Engine
├── platformio.ini        # Stripped system deployment configurations
└── README.md             # System user manual documentation

```

---

## 🔧 Kernel & Memory Debugging Notes

* **WDT Bypass:** The system safely deallocates the hardware Watchdog Timer (WDT) on core loop cycles to ensure long file read/write operations or heavy text entries don't trigger brownouts.
* **VFS Mounting:** On its very first deployment, LittleFS will seamlessly self-format and mount the root table directory automatically.

---

## 📄 License

This project is open-source, free to be copied, customized, or extended with further custom low-level device configurations. Happy hacking! 💻🔥


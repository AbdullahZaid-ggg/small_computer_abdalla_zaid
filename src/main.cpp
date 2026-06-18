#include <Arduino.h>
#include <LittleFS.h>
#include "esp_task_wdt.h"

String inputBuffer = "";

// دالة لطباعة موجه الأوامر (Prompt) الخاص بالـ Linux
void printPrompt() {
    Serial.print("\nroot@esp32:~# ");
}

void executeCommand(String cmd) {
    cmd.trim();
    if (cmd.length() == 0) {
        printPrompt();
        return;
    }

    Serial.println(); // سطر جديد لبدء طباعة مخرجات الأمر

    // 1. أمر استعراض المساعدة والأوامر العشرة المتاحة
    if (cmd == "help") {
        Serial.println("\n========================================");
        Serial.println("   ESP32 Core 10 Linux Commands Menu   ");
        Serial.println("========================================");
        Serial.println("help                 - Show this commands list");
        Serial.println("pwd                  - Print working directory");
        Serial.println("ls                   - List files in root");
        Serial.println("touch [file]         - Create an empty file");
        Serial.println("echo [text] > [file] - Write text into a file");
        Serial.println("cat [file]           - Display file content");
        Serial.println("rm [file]            - Delete a file");
        Serial.println("free                 - Check available RAM & Storage");
        Serial.println("clear                - Clear the terminal screen");
        Serial.println("reboot               - Restart the ESP32 OS");
        Serial.println("========================================");
    }
    // 2. أمر معرفة المجلد الحالي
    else if (cmd == "pwd") {
        Serial.println("/root");
    }
    // 3. أمر استعراض الملفات في الذاكرة
    else if (cmd == "ls") {
        String files = "";
        File root = LittleFS.open("/", "r");
        File file = root.openNextFile();
        while(file) {
            files += String(file.name()) + "  ";
            file = root.openNextFile();
        }
        if(files == "") {
            Serial.println("(Directory is empty)");
        } else {
            Serial.println(files);
        }
    }
    // 4. أمر إنشاء ملف فارغ
    else if (cmd.startsWith("touch ")) {
        String filename = "/" + cmd.substring(6);
        filename.trim();
        File f = LittleFS.open(filename, "w");
        if(f) { 
            f.close(); 
            Serial.printf("File '%s' created successfully.\n", filename.c_str()); 
        } else {
            Serial.println("touch: Open failed");
        }
    }
    // 5. أمر قراءة محتوى ملف
    else if (cmd.startsWith("cat ")) {
        String filename = "/" + cmd.substring(4);
        filename.trim();
        if (LittleFS.exists(filename)) {
            File file = LittleFS.open(filename, "r");
            while(file.available()) Serial.print((char)file.read());
            file.close();
            Serial.println();
        } else {
            Serial.println("cat: " + filename + ": No such file or directory");
        }
    }
    // 6. أمر حذف ملف من الذاكرة
    else if (cmd.startsWith("rm ")) {
        String filename = "/" + cmd.substring(3);
        filename.trim();
        if (LittleFS.exists(filename)) {
            LittleFS.remove(filename);
            Serial.println("Removed file: " + filename);
        } else {
            Serial.println("rm: cannot remove: No such file or directory");
        }
    }
    // 7. أمر فحص ذاكرة النظام والـ RAM
    else if (cmd == "free") {
        uint32_t freeRAM = ESP.getFreeHeap();
        size_t totalFlash = LittleFS.totalBytes();
        size_t usedFlash = LittleFS.usedBytes();
        Serial.printf("Free Heap RAM : %d Bytes\n", freeRAM);
        Serial.printf("Storage (FS)  : Total: %d B | Used: %d B | Free: %d B\n", totalFlash, usedFlash, totalFlash - usedFlash);
    }
    // 8. أمر تنظيف شاشة الـ Terminal
    else if (cmd == "clear") {
        for(int i = 0; i < 50; i++) Serial.println(); 
    }
    // 9. أمر إعادة تشغيل النظام
    else if (cmd == "reboot") {
        Serial.println("Rebooting ESP32 Kernel...");
        delay(1000);
        ESP.restart();
    }
    // 10. أمر الكتابة وإعادة التوجيه للملفات (echo)
    else if (cmd.startsWith("echo ")) {
        int index = cmd.indexOf('>');
        if (index != -1) {
            String text = cmd.substring(5, index); 
            String filename = "/" + cmd.substring(index + 1);
            text.trim(); filename.trim();
            File file = LittleFS.open(filename, "w"); 
            if (file) { 
                file.print(text); 
                file.close(); 
                Serial.println("Data saved in " + filename); 
            }
        } else {
            Serial.println(cmd.substring(5)); // طباعة النص مباشرة إذا لم يتم توجيهه لملف
        }
    } 
    else {
        Serial.println("bash: " + cmd + ": command not found. Type 'help'.");
    }

    printPrompt();
}

void setup() {
    Serial.begin(115200);
    
    // إلغاء الـ Watchdog لمنع الـ Reboot أثناء أول عملية تهيئة للفلاش
    esp_task_wdt_delete(NULL); 
    LittleFS.begin(true);

    Serial.println("\n\n====================================================");
    Serial.println("        ESP32 Pure Terminal OS (10 Core Cmds)       ");
    Serial.println("====================================================");
    Serial.println("System fully initialized. Minimal setup active.");
    Serial.println("Type 'help' to view the active commands registry.");
    
    printPrompt();
}

void loop() {
    if (Serial.available()) {
        char c = Serial.read();
        
        // عند الضغط على Enter تنفذ الأوامر مباشرة
        if (c == '\r' || c == '\n') {
            executeCommand(inputBuffer);
            inputBuffer = ""; 
        } 
        // دعم زر الـ Backspace لمسح الحروف حياً من تيرمينال اللابتوب
        else if (c == 8 || c == 127) { 
            if (inputBuffer.length() > 0) {
                inputBuffer.remove(inputBuffer.length() - 1);
                Serial.print("\b \b"); 
            }
        } 
        // استقبال وطباعة الحروف حية أثناء الكتابة
        else {
            inputBuffer += c;
            Serial.print(c); 
        }
    }
    delay(5);
}
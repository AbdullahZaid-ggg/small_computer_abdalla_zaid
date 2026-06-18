#include <Arduino.h>
#include <LittleFS.h>
#include "esp_task_wdt.h"

String inputBuffer = "";

void printPrompt() {
    Serial.print("\nroot@esp32:~# ");
}

// دالة توليد الأسطر الأفقية للحروف (كل حرف يتكون من 4 أسطر بارتفاع 4 صفوف)
String getLetterRow(char c, int row) {
    c = toupper(c);
    
    // مصفوفة الحروف المخصصة للطباعة الأفقية (ارتفاع 4 أسطر وعرض ثابت 6 رموز لكل حرف)
    if (c == 'A') {
        if (row == 0) return "  A   ";
        if (row == 1) return " / \\  ";
        if (row == 2) return "|---| ";
        if (row == 3) return "|   | ";
    }
    else if (c == 'B') {
        if (row == 0) return "|--\\  ";
        if (row == 1) return "|--/  ";
        if (row == 2) return "|--\\  ";
        if (row == 3) return "|--/  ";
    }
    else if (c == 'C') {
        if (row == 0) return "/---  ";
        if (row == 1) return "|     ";
        if (row == 2) return "|     ";
        if (row == 3) return "\\---  ";
    }
    else if (c == 'D') {
        if (row == 0) return "|--\\  ";
        if (row == 1) return "|   | ";
        if (row == 2) return "|   | ";
        if (row == 3) return "|--/  ";
    }
    else if (c == 'E') {
        if (row == 0) return "|---  ";
        if (row == 1) return "|---  ";
        if (row == 2) return "|     ";
        if (row == 3) return "|---  ";
    }
    else if (c == 'F') {
        if (row == 0) return "|---  ";
        if (row == 1) return "|---  ";
        if (row == 2) return "|     ";
        if (row == 3) return "|     ";
    }
    else if (c == 'G') {
        if (row == 0) return "/---  ";
        if (row == 1) return "|  -\\ ";
        if (row == 2) return "|   | ";
        if (row == 3) return "\\---/ ";
    }
    else if (c == 'H') {
        if (row == 0) return "|   | ";
        if (row == 1) return "|---| ";
        if (row == 2) return "|   | ";
        if (row == 3) return "|   | ";
    }
    else if (c == 'I') {
        if (row == 0) return " ---  ";
        if (row == 1) return "  |   ";
        if (row == 2) return "  |   ";
        if (row == 3) return " ---  ";
    }
    else if (c == 'J') {
        if (row == 0) return "  --- ";
        if (row == 1) return "    | ";
        if (row == 2) return " |  | ";
        if (row == 3) return " \\--/ ";
    }
    else if (c == 'K') {
        if (row == 0) return "|  /  ";
        if (row == 1) return "|--   ";
        if (row == 2) return "|  \\  ";
        if (row == 3) return "|   \\ ";
    }
    else if (c == 'L') {
        if (row == 0) return "|     ";
        if (row == 1) return "|     ";
        if (row == 2) return "|     ";
        if (row == 3) return "|___  ";
    }
    else if (c == 'M') {
        if (row == 0) return "|\\ /| ";
        if (row == 1) return "| X | ";
        if (row == 2) return "|   | ";
        if (row == 3) return "|   | ";
    }
    else if (c == 'N') {
        if (row == 0) return "|\\  | ";
        if (row == 1) return "| \\ | ";
        if (row == 2) return "|  \\| ";
        if (row == 3) return "|   | ";
    }
    else if (c == 'O') {
        if (row == 0) return "/---\\ ";
        if (row == 1) return "|   | ";
        if (row == 2) return "|   | ";
        if (row == 3) return "\\---/ ";
    }
    else if (c == 'P') {
        if (row == 0) return "|--\\  ";
        if (row == 1) return "|--/  ";
        if (row == 2) return "|     ";
        if (row == 3) return "|     ";
    }
    else if (c == 'Q') {
        if (row == 0) return "/---\\ ";
        if (row == 1) return "|   | ";
        if (row == 2) return "\\---\\ ";
        if (row == 3) return "     \\";
    }
    else if (c == 'R') {
        if (row == 0) return "|--\\  ";
        if (row == 1) return "|--/  ";
        if (row == 2) return "|  \\  ";
        if (row == 3) return "|   \\ ";
    }
    else if (c == 'S') {
        if (row == 0) return "/---  ";
        if (row == 1) return "\\---\\ ";
        if (row == 2) return "    | ";
        if (row == 3) return "---/  ";
    }
    else if (c == 'T') {
        if (row == 0) return "---|--";
        if (row == 1) return "   |  ";
        if (row == 2) return "   |  ";
        if (row == 3) return "   |  ";
    }
    else if (c == 'U') {
        if (row == 0) return "|   | ";
        if (row == 1) return "|   | ";
        if (row == 2) return "|   | ";
        if (row == 3) return "\\___/ ";
    }
    else if (c == 'V') {
        if (row == 0) return "|   | ";
        if (row == 1) return "|   | ";
        if (row == 2) return " \\ /  ";
        if (row == 3) return "  V   ";
    }
    else if (c == 'W') {
        if (row == 0) return "|   | ";
        if (row == 1) return "| X | ";
        if (row == 2) return "|/ \\| ";
        if (row == 3) return "|   | ";
    }
    else if (c == 'X') {
        if (row == 0) return "\\   / ";
        if (row == 1) return " \\ /  ";
        if (row == 2) return " / \\  ";
        if (row == 3) return "/   \\ ";
    }
    else if (c == 'Y') {
        if (row == 0) return "\\   / ";
        if (row == 1) return " \\ /  ";
        if (row == 2) return "  |   ";
        if (row == 3) return "  |   ";
    }
    else if (c == 'Z') {
        if (row == 0) return "----/ ";
        if (row == 1) return "   /  ";
        if (row == 2) return "  /   ";
        if (row == 3) return "/____ ";
    }
    else if (c == ' ') {
        return "      "; // مسافة أفقية واضحة بين الكلمات
    }
    
    return "      ";
}

// دالة معالجة وطباعة الـ Banner الأفقي بالكامل
void printHorizontalBanner(String text) {
    Serial.println();
    // نقوم بالمرور على الأسطر الأربعة من 0 إلى 3 لطباعتها صفاً تلو الآخر لضمان بقائها بجانب بعضها
    for (int row = 0; row < 4; row++) {
        for (size_t i = 0; i < text.length(); i++) {
            Serial.print(getLetterRow(text[i], row));
        }
        Serial.println(); // سطر جديد بعد انتهاء الصف الحالي من كل الكلمة
    }
    Serial.println();
}

void startNano(String filename) {
    Serial.printf("\n--- GNU nano 2.9.3 (File: %s) ---\n", filename.c_str());
    Serial.println("Type your text line by line. Type 'EXIT' on a single line to save and quit.\n");
    
    String fileContent = "";
    while (true) {
        if (Serial.available()) {
            String line = Serial.readStringUntil('\n');
            line.trim();
            if (line == "EXIT") break;
            fileContent += line + "\n";
            Serial.println("  > " + line);
        }
        delay(10);
    }
    
    File file = LittleFS.open(filename, "w");
    if (file) {
        file.print(fileContent);
        file.close();
        Serial.println("\n[ nano: File saved successfully. Exiting... ]");
    } else {
        Serial.println("\n[ nano: Error writing file! ]");
    }
}

void executeCommand(String cmd) {
    cmd.trim();
    if (cmd.length() == 0) {
        printPrompt();
        return;
    }

    Serial.println();

    if (cmd.startsWith("banner ")) {
        String text = cmd.substring(7);
        printHorizontalBanner(text);
    }
    else if (cmd.startsWith("nano ")) {
        String filename = "/" + cmd.substring(5); filename.trim();
        startNano(filename);
    }
    else if (cmd == "help") {
        Serial.println("\n==================================================");
        Serial.println("   ESP32 Advanced Terminal OS v3.5 (Horizontal CLI)");
        Serial.println("==================================================");
        Serial.println("help                  - Show this help system menu");
        Serial.println("pwd                   - Print current environment root");
        Serial.println("ls                    - List all active files");
        Serial.println("touch [file]          - Create an empty file layout");
        Serial.println("nano [file]           - Open interactive line text editor");
        Serial.println("banner [word]         - Render text horizontally in one line!");
        Serial.println("echo [txt] > [file]   - Overwrite text into file");
        Serial.println("echo [txt] >> [file]  - Append text to the end of file");
        Serial.println("cat [file]            - Stream file contents into console");
        Serial.println("rm [file]             - Delete file structurally");
        Serial.println("free                  - Query physical Heap RAM and LittleFS");
        Serial.println("clear                 - Clean terminal stdout shell");
        Serial.println("reboot                - Hard reset the core microprocessor");
        Serial.println("==================================================");
    }
    else if (cmd == "pwd") { Serial.println("/root"); }
    else if (cmd == "ls") {
        String files = "";
        File root = LittleFS.open("/", "r"); File file = root.openNextFile();
        while(file) { files += String(file.name()) + "  "; file = root.openNextFile(); }
        Serial.println((files == "") ? "(Directory is empty)" : files);
    }
    else if (cmd.startsWith("touch ")) {
        String filename = "/" + cmd.substring(6); filename.trim();
        File f = LittleFS.open(filename, "w"); if(f) f.close();
        Serial.printf("File '%s' touched.\n", filename.c_str());
    }
    else if (cmd.startsWith("cat ")) {
        String filename = "/" + cmd.substring(4); filename.trim();
        if (LittleFS.exists(filename)) {
            File file = LittleFS.open(filename, "r");
            while(file.available()) Serial.print((char)file.read());
            file.close(); Serial.println();
        } else { Serial.println("cat: " + filename + ": No such file"); }
    }
    else if (cmd.startsWith("rm ")) {
        String filename = "/" + cmd.substring(3); filename.trim();
        if (LittleFS.exists(filename)) { LittleFS.remove(filename); Serial.println("Removed " + filename); }
    }
    else if (cmd == "free") {
        Serial.printf("Free Heap RAM : %d Bytes\n", ESP.getFreeHeap());
        Serial.printf("Storage Free  : %d Bytes\n", LittleFS.totalBytes() - LittleFS.usedBytes());
    }
    else if (cmd == "clear") { for(int i = 0; i < 60; i++) Serial.println(); }
    else if (cmd == "reboot") { Serial.println("Rebooting..."); delay(1000); ESP.restart(); }
    else if (cmd.startsWith("echo ")) {
        int appendIndex = cmd.indexOf(">>"); int overwriteIndex = cmd.indexOf('>');
        if (appendIndex != -1) {
            String text = cmd.substring(5, appendIndex); String filename = "/" + cmd.substring(appendIndex + 2);
            text.trim(); filename.trim();
            File file = LittleFS.open(filename, "a"); if (file) { file.println(text); file.close(); Serial.println("Appended."); }
        } 
        else if (overwriteIndex != -1) {
            String text = cmd.substring(5, overwriteIndex); String filename = "/" + cmd.substring(overwriteIndex + 1);
            text.trim(); filename.trim();
            File file = LittleFS.open(filename, "w"); if (file) { file.println(text); file.close(); Serial.println("Overwritten."); }
        } else { Serial.println(cmd.substring(5)); }
    } 
    else { Serial.println("bash: command not found."); }

    printPrompt();
}

void setup() {
    Serial.begin(115200);
    esp_task_wdt_delete(NULL); 
    LittleFS.begin(true);
    Serial.println("\n\n====================================================");
    Serial.println("    ESP32 Advanced Terminal OS v3.5 (Horizontal Line) ");
    Serial.println("====================================================");
    printPrompt();
}

void loop() {
    if (Serial.available()) {
        char c = Serial.read();
        if (c == '\r' || c == '\n') { executeCommand(inputBuffer); inputBuffer = ""; } 
        else if (c == 8 || c == 127) { 
            if (inputBuffer.length() > 0) { inputBuffer.remove(inputBuffer.length() - 1); Serial.print("\b \b"); }
        } 
        else { inputBuffer += c; Serial.print(c); }
    }
    delay(5);
}
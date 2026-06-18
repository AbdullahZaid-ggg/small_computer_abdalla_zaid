#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <LittleFS.h>
#include "esp_task_wdt.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); 

String inputBuffer = "";
String currentLine2 = "Ready...";

void updateLCD(String line1, String line2) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(line1.substring(0, 16));
    lcd.setCursor(0, 1);
    lcd.print(line2.substring(0, 16));
}

void executeCommand(String cmd) {
    cmd.trim();
    if (cmd.length() == 0) return;

    if (cmd == "help") {
        updateLCD("Cmds: help, ls", "status,cat,echo");
    } 
    else if (cmd == "status") {
        updateLCD("CPU: 240MHz", "RAM: " + String(ESP.getFreeHeap()) + "B");
    } 
    else if (cmd == "ls") {
        String files = "";
        File root = LittleFS.open("/", "r");
        if (!root) {
            updateLCD("LS Error", "No Root Dir");
            return;
        }
        File file = root.openNextFile();
        while(file) {
            files += String(file.name()) + " ";
            file = root.openNextFile();
        }
        if(files == "") files = "No files found";
        updateLCD("Files:", files);
    } 
    else if (cmd.startsWith("cat ")) {
        String filename = "/" + cmd.substring(4);
        filename.trim();
        if (LittleFS.exists(filename)) {
            File file = LittleFS.open(filename, "r");
            String content = "";
            while(file.available()) content += (char)file.read();
            file.close();
            updateLCD("Content:", content);
        } else {
            updateLCD("Error:", "File not found");
        }
    } 
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
                updateLCD("Saved OK!", filename);
            } else {
                updateLCD("Error:", "Write Failed");
            }
        } else {
            updateLCD("Use: echo text", "> filename");
        }
    } 
    else {
        updateLCD("Unknown Command", "Type 'help'");
    }
    currentLine2 = cmd; 
}

void setup() {
    Serial.begin(115200);
    Wire.begin(21, 22);
    
    lcd.init();
    lcd.backlight();
    updateLCD("Booting OS...", "Mounting LittleFS");
    
    Serial.println("Forcing LittleFS Mount with Auto-Format...");
    
    // إيقاف الـ Watchdog مؤقتاً لضمان عدم حدوث ريستارت أثناء التهيئة الأولى
    esp_task_wdt_delete(NULL); 

    // تمرير true هنا مع بارتيشن no_ota يضمن التهيئة الناجحة فوراً
    if(!LittleFS.begin(true)){ 
        updateLCD("OS Error", "Storage Failed");
        Serial.println("Critical Error: LittleFS Mount/Format Failed completely.");
        return;
    }

    updateLCD("System Ready", "Type in Laptop!");
    Serial.println("\n--- ESP32 Mini OS: Storage Mounted Successfully ---");
}

void loop() {
    if (Serial.available()) {
        char c = Serial.read();
        if (c == '\r' || c == '\n') {
            executeCommand(inputBuffer);
            inputBuffer = ""; 
        } 
        else if (c == 8 || c == 127) { 
            if (inputBuffer.length() > 0) {
                inputBuffer.remove(inputBuffer.length() - 1);
                updateLCD("> " + inputBuffer, currentLine2);
            }
        } 
        else {
            inputBuffer += c;
            updateLCD("> " + inputBuffer, currentLine2);
        }
    }
    delay(10);
}
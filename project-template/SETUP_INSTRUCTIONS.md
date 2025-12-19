# ESP32 + FreeRTOS Tutorial - Complete Setup Guide

## 📦 What's Included

This is a complete learning package for mastering ESP32 development with FreeRTOS. Everything you need is included:

```
TUTORIAL_PACKAGE/
├── SETUP_INSTRUCTIONS.md          ← You are here
├── ESP32_FREERTOS_LEARNING_PLAN.md ← Complete curriculum
├── PROGRESS_TRACKER.md            ← Track your progress
├── project-template/              ← Boilerplate code
│   ├── platformio.ini
│   ├── src/main.cpp
│   ├── .exercises/
│   └── .github/copilot-instructions.md
└── AI_INSTRUCTOR_GUIDE.md         ← For GitHub Copilot
```

---

## 🎯 Who This Is For

- **Background Required:** Arduino experience, basic C programming
- **Time Commitment:** 3-4 weeks, self-paced (~1-2 hours/day)
- **Hardware:** ESP32 development board (any variant)
- **Learning Style:** Hands-on, challenge-based coding

---

## 🛠️ Complete Environment Setup

### **Step 1: Install VS Code**

1. Download and install [Visual Studio Code](https://code.visualstudio.com/)
2. Launch VS Code

### **Step 2: Install PlatformIO Extension**

1. Open VS Code Extensions panel (⇧⌘X or Ctrl+Shift+X)
2. Search for "PlatformIO IDE"
3. Click **Install** on the official PlatformIO extension
4. Wait for installation to complete (~5 minutes)
5. Restart VS Code when prompted

### **Step 3: Install GitHub Copilot (Recommended)**

1. In VS Code Extensions, search for "GitHub Copilot"
2. Install **GitHub Copilot** and **GitHub Copilot Chat**
3. Sign in with your GitHub account
4. Activate Copilot (requires subscription or student access)

> **Why Copilot?** This tutorial is designed to work with AI assistance. Copilot will act as your instructor, providing guidance based on the learning plan.

### **Step 4: Set Up Project**

1. Copy the entire `project-template/` folder to your workspace
2. Rename it to your project name (e.g., `my-esp32-learning`)
3. Open the folder in VS Code:
   ```
   File → Open Folder → Select your project folder
   ```
4. PlatformIO will auto-detect the project (look for PlatformIO icon in sidebar)

### **Step 5: Configure for Your ESP32 Board**

1. Open `platformio.ini`
2. Verify or change the board type:
   ```ini
   board = esp32dev          # Generic ESP32
   board = esp32-s3-devkitc-1  # ESP32-S3
   board = esp32-c3-devkitm-1  # ESP32-C3
   ```
3. Save the file

### **Step 6: First Build (Important!)**

The first build downloads the ESP-IDF toolchain (~1GB). This takes 5-10 minutes.

1. Open PlatformIO sidebar (alien icon)
2. Click **Build** under Project Tasks
3. Wait for download and build to complete
4. Subsequent builds will be fast (seconds)

### **Step 7: Connect Your ESP32**

1. Connect ESP32 to your computer via USB
2. Check if detected:
   - **macOS/Linux:** `ls /dev/cu.* | grep -i usb`
   - **Windows:** Check Device Manager → Ports
3. If not detected, install USB-to-Serial driver:
   - **CP210x:** [Silicon Labs driver](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers)
   - **CH340:** [WCH driver](https://www.wch-ic.com/downloads/CH341SER_MAC_ZIP.html)

### **Step 8: Upload Test Code**

1. Click **Upload** in PlatformIO (→ button)
2. Wait for upload to complete
3. LED on GPIO 2 should blink!

### **Step 9: Open Serial Monitor**

View ESP32 output logs:
```bash
# Option 1: PlatformIO monitor
pio device monitor

# Option 2: VS Code task
Terminal → Run Task → Monitor
```

Press `Ctrl+C` to exit monitor.

---

## 🤖 Activate AI Instructor (GitHub Copilot)

### **Import Learning Context**

1. Open GitHub Copilot Chat in VS Code (⌃⌘I or Ctrl+Alt+I)
2. Start the tutorial by saying:

```
I'm following the ESP32 + FreeRTOS learning plan in the .learning/ folder. 
I'm a beginner starting with Day 1. Please act as my instructor based on 
the methodology in ESP32_FREERTOS_LEARNING_PLAN.md
```

3. Copilot will guide you through exercises following the teaching philosophy

### **How to Interact with AI Instructor**

**Starting an Exercise:**
- "Start Day 1 Exercise 1"
- "Ready for the next challenge"

**During Coding:**
- "What function should I use for GPIO?"
- "How do I create a FreeRTOS task?"
- "Why isn't this compiling?"

**After Completion:**
- "Ready for review"
- "Check my code"
- "I completed the exercise"

**Getting Help:**
- "Give me a hint" (will get function names, not code)
- "Point me to documentation"
- "Explain this concept"

---

## 📚 Learning Workflow

### **Daily Routine:**

1. **Read the exercise challenge** in `ESP32_FREERTOS_LEARNING_PLAN.md`
2. **Get template** from AI instructor (loads into `src/main.cpp`)
3. **Research** ESP-IDF docs for functions mentioned
4. **Code** your solution in `src/main.cpp`
5. **Build & Upload:** `pio run -t upload`
6. **Test** with serial monitor
7. **Review** with AI instructor
8. **Iterate** based on feedback
9. **Update** `PROGRESS_TRACKER.md` when complete

### **Your Code Files:**

- **Active work:** `src/main.cpp` (always edit this)
- **Completed exercises:** Auto-saved to `.exercises/completed/`
- **No folder switching!** Stay in one workspace

### **Progress Tracking:**

Update `.learning/PROGRESS_TRACKER.md` after each exercise:
- Mark exercises complete
- Document learnings
- Note challenges faced

---

## 🔧 Troubleshooting

### **Build Fails**
```bash
# Clean and rebuild
pio run --target clean
pio run
```

### **Upload Fails**
- Check USB connection
- Press BOOT button on ESP32 during upload
- Verify correct port in `platformio.ini`
- Try different USB cable

### **Serial Monitor Shows Garbage**
- Check baud rate matches (115200)
- Press EN/RESET button on ESP32

### **"extern C" Linker Errors**
- Ensure `app_main()` has `extern "C"` wrapper
- See `.github/copilot-instructions.md` for pattern

### **PlatformIO Not Detecting Project**
- Look for `platformio.ini` in root folder
- Reload VS Code window
- Click PlatformIO home icon and import project

---

## 📖 Essential Documentation Links

**ESP-IDF (Framework):**
- [Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [API Reference](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/index.html)

**FreeRTOS:**
- [FreeRTOS Kernel Docs](https://www.freertos.org/a00106.html)
- [Task API](https://www.freertos.org/a00106.html)
- [Queue API](https://www.freertos.org/a00018.html)

**PlatformIO:**
- [PlatformIO Docs](https://docs.platformio.org)
- [ESP32 Platform](https://docs.platformio.org/en/latest/platforms/espressif32.html)

**Hardware:**
- [ESP32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf)
- [ESP32 Technical Reference](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)

---

## 🎓 Learning Philosophy

This tutorial uses **minimal hand-holding**:

- ❌ You won't get complete code in hints
- ✅ You'll get function names and concepts
- ✅ You'll read documentation yourself
- ✅ You'll write all implementation code
- ✅ You'll learn by doing, not copying

**This builds real understanding!** You'll know WHY things work, not just HOW.

---

## ✅ Ready to Start?

1. ✅ Environment set up (VS Code + PlatformIO)
2. ✅ Project opens in VS Code
3. ✅ First build succeeds
4. ✅ ESP32 uploads and blinks LED
5. ✅ Serial monitor shows output
6. ✅ GitHub Copilot activated (optional but recommended)
7. ✅ Read `ESP32_FREERTOS_LEARNING_PLAN.md`

**You're all set!** 

Open Copilot Chat and say:
```
I've completed setup. Start me on Day 1 - Exercise 1: Code Analysis
```

---

## 💬 Support

**Stuck?** Ask your AI instructor (Copilot) for:
- Function name hints
- Documentation links
- Conceptual explanations
- Code review feedback

**Remember:** The goal is to learn deeply, not finish quickly. Take your time, experiment, and understand each concept before moving on.

**Happy Learning!** 🚀

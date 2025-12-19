# ESP32 Learning - Project Structure

This directory contains all your learning exercises organized by week and day.

## 📁 Directory Organization

```
esp32-learning/
├── .learning/              # Learning plans and progress tracking
│   ├── ESP32_FREERTOS_LEARNING_PLAN.md
│   ├── PROGRESS_TRACKER.md
│   └── PROJECT_STRUCTURE.md (this file)
│
├── week1-freertos-fundamentals/
│   ├── day1-ex1-code-analysis/     # Analyzing existing blink code
│   ├── day1-ex2-arduino-comparison/ # Arduino vs ESP-IDF comparison
│   ├── day1-ex3-logging-levels/     # ESP_LOG levels practice
│   ├── day2-ex1-two-tasks/          # Multiple tasks running
│   ├── day2-ex2-task-parameters/    # Passing data to tasks
│   ├── day2-ex3-three-leds/         # 3 LEDs with 3 tasks
│   ├── day3-ex1-priorities/         # Task priority experiments
│   └── day6-7-project-led-controller/ # Week 1 practice project
│
├── week2-hardware-peripherals/
│   ├── day8-ex1-gpio-interrupts/
│   ├── day10-ex1-uart-echo/
│   └── ...
│
├── week3-advanced-freertos/
│   └── ...
│
└── week4-connectivity/
    └── ...
```

## 🚀 Workflow for Each Exercise

### 1. Starting an Exercise
```bash
cd /Users/mohitsingh/myFiles/myesp32projects/esp32-learning/week1-freertos-fundamentals/day1-ex3-logging-levels
code .  # Opens in VS Code
```

### 2. Working on Code
- Each project is a complete PlatformIO project
- Has its own `platformio.ini`, `src/main.cpp`
- Independent build and upload

### 3. Building and Testing
```bash
pio run              # Build
pio run -t upload    # Upload to ESP32
pio device monitor   # View serial output
```

### 4. After Completion
- Mark exercise complete in PROGRESS_TRACKER.md
- Add notes about what you learned
- Move to next exercise

## 📝 Each Project Contains

```
dayX-exX-name/
├── platformio.ini      # PlatformIO configuration
├── src/
│   └── main.cpp       # Your implementation
├── README.md          # Exercise description and requirements
└── .solution/         # Reference solution (only revealed after attempt)
    └── main.cpp
```

## 🎯 Benefits

✅ **Isolated environments** - Each exercise is independent  
✅ **Easy reference** - Go back to previous exercises anytime  
✅ **Version control** - Each project can be git-tracked separately  
✅ **Portfolio building** - Showcase your learning progress  
✅ **No conflicts** - Work on multiple exercises simultaneously

## 🔄 Project Template

Each new exercise project will be created from a template with:
- Pre-configured `platformio.ini`
- Starter `main.cpp` with basic structure
- `README.md` with exercise requirements
- Comments and hints in code

---

**Current Exercise:** Week 1, Day 1, Exercise 3 - ESP Logging Levels

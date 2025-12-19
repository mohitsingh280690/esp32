# Learning Progress Tracker

**Start Date:** December 16, 2025  
**Target Completion:** January 13, 2026 (4 weeks)  
**Student:** [Your Name]  
**Board:** ESP32 WROOM  
**Workspace:** `e:\esp32-freertos-tutorial-main\project-template`

---

## 📁 How This Works

**Single Workspace Approach:**
- You work in ONE project throughout all exercises
- Your code is always in `src/main.cpp`
- Previous solutions saved in `.exercises/completed/`
- No switching folders = No lost context!

**Exercise Flow:**
1. I backup your current work
2. I give you new template with TODOs
3. You code in `src/main.cpp`
4. You test with `pio run -t upload`
5. Type "ready for review" when done

---

## Current Status

**Current Week:** Week 1  
**Current Day:** Day 2  
**Current Challenge:** Day 2, Exercise 1 (Two Talking Tasks) - COMPLETED!
**Overall Progress:** 1.5/28 days (5%)

---

## Weekly Progress

### 🔵 Week 1: FreeRTOS Fundamentals (1.5/7 days completed)
- ✅ Day 1: ESP-IDF vs Arduino, Build System (COMPLETED)
  - ✅ Setup Verification: LED Blink
  - ✅ Exercise 3: ESP Logging Levels (4 log levels, counter, modulo operator)
  - **Key Learnings:** extern "C" linkage, vTaskDelay() requirement, watchdog timers, log level semantics
- 🔄 Day 2: FreeRTOS Tasks Basics (IN PROGRESS)
  - ✅ Exercise 1: Two Talking Tasks (concurrent execution, function pointers)
  - ⬜ Exercise 2: Task with Parameters (void* casting, passing data)
  - ⬜ Exercise 3: Three LEDs at Different Rates
- ⬜ Day 3: Task Scheduling & Priorities
- ⬜ Day 4: Inter-Task Communication (Queues)
- ⬜ Day 5: Semaphores & Mutexes
- ⬜ Day 6-7: Practice Project: Multi-Task LED Controller

### ⬜ Week 2: Hardware Peripherals (0/7 days)
- ⬜ Day 8: GPIO Deep Dive
- ⬜ Day 9: Timers
- ⬜ Day 10: UART
- ⬜ Day 11: I2C
- ⬜ Day 12: SPI
- ⬜ Day 13: ADC & DAC
- ⬜ Day 14: Practice Project: Sensor Dashboard

### ⬜ Week 3: Advanced FreeRTOS (0/7 days)
- ⬜ Day 15: Event Groups
- ⬜ Day 16: Task Notifications
- ⬜ Day 17: Memory Management
- ⬜ Day 18: Watchdogs
- ⬜ Day 19: Power Management
- ⬜ Day 20: Interrupt Handling
- ⬜ Day 21: Practice Project: Power Logger

### ⬜ Week 4: Connectivity (0/7 days)
- ⬜ Day 22: WiFi
- ⬜ Day 23: HTTP
- ⬜ Day 24: MQTT
- ⬜ Day 25: Bluetooth Classic
- ⬜ Day 26: BLE
- ⬜ Day 27-28: Final Project

---

## Daily Learning Log

### Week 1

#### Day 1: ESP-IDF vs Arduino (✅ Completed)
**Date:** December 19, 2025  
**Time Spent:** ~2 hours  
**Status:** Completed

**What I Learned:**
- `extern "C"` prevents C++ name mangling for ESP-IDF's C entry point
- `vTaskDelay()` is REQUIRED in task loops to prevent watchdog timeouts
- Tasks must yield to allow IDLE task to run (housekeeping, watchdog feeding)
- FreeRTOS uses preemptive priority-based scheduling
- ESP-IDF logging system: LOGE, LOGW, LOGI, LOGD, LOGV
- Log level filtering: runtime with `esp_log_level_set()`, compile-time default
- Counter overflow considerations in embedded systems

**Exercises Completed:**
- [x] Setup Verification: LED blink on GPIO 2
- [x] Exercise 3: ESP Logging Levels (all 4 levels, counter, every 5th blink detection)

**Challenges Faced:**
- Initially thought `static` was needed for counter in task function (clarified: not needed in infinite loop)
- ESP_LOGD() not showing by default (fixed with `esp_log_level_set("*", ESP_LOG_DEBUG)`)
- Understanding why vTaskDelay() is critical (not just for timing, but for scheduler cooperation)

**Key Concepts Clarified:**
- Preemptive vs cooperative scheduling
- FreeRTOS on ESP32 is a library, not separate OS
- Boot sequence: ROM bootloader → Secondary bootloader → app_main()
- uint32_t overflow: 136 years at 1 blink/second
- Misusing log levels creates alert fatigue in production

**Notes:**
- Successfully connected concepts between RT-PREEMPT Linux and FreeRTOS
- Understood bootloader architecture and OTA partition strategy
- Good foundation in embedded systems critical thinking

---

#### Day 2: FreeRTOS Tasks Basics (🔄 In Progress)
**Date:** December 19, 2025  
**Time Spent:** ~30 minutes so far  
**Status:** In Progress

**What I Learned:**
- Tasks = Threads (same concept, different terminology)
- Function pointers: `&task` passes address, `task()` calls function
- Multiple tasks run concurrently via scheduler time slicing
- Equal priority tasks share CPU time (round-robin)
- `xTaskCreate()` parameters: function pointer, name, stack size, params, priority, handle
- When task calls vTaskDelay(), scheduler switches to other ready tasks

**Exercises Completed:**
- [x] Exercise 1: Two Talking Tasks (1s and 2s intervals, concurrent execution)

**Key Understanding:**
- Task 1 delaying does NOT block Task 2 (scheduler switches contexts)
- Same timestamps appear when multiple tasks become ready simultaneously
- Using `task1()` instead of `&task1` would cause immediate call and crash

**Challenges Faced:**
- None so far - concepts building well on Day 1 foundation

**Questions for Next Session:**
- How to pass parameters to tasks? (void* casting)
- What happens with different priorities?

**Notes:**
- Code works perfectly, minor style improvements noted (static const, formatting)
- Ready for Exercise 2: Task Parameters

---

#### Day 2: FreeRTOS Tasks (⬜ Not Started)
**Date:** _______________  
**Time Spent:** _______________  
**Status:** Not Started

**What I Learned:**

**Exercises Completed:**
- [ ] Exercise 1: Create 2 tasks
- [ ] Exercise 2: Pass parameters to tasks
- [ ] Exercise 3: 3 LEDs at different rates

**Challenges Faced:**

**Questions:**

**Notes:**

---

#### Day 3: Task Scheduling & Priorities (⬜ Not Started)
**Date:** _______________  
**Time Spent:** _______________

**What I Learned:**

**Exercises Completed:**
- [ ] Exercise 1: 3 tasks with different priorities
- [ ] Exercise 2: Dynamic priority change
- [ ] Exercise 3: CPU vs I/O task priorities
- [ ] Exercise 4: Task suspension with button

**Challenges Faced:**

**Questions:**

**Notes:**

---

#### Day 4: Queues (⬜ Not Started)
**Date:** _______________  
**Time Spent:** _______________

**What I Learned:**

**Exercises Completed:**
- [ ] Exercise 1: Producer-Consumer
- [ ] Exercise 2: Multi-producer queue
- [ ] Exercise 3: Circular buffer
- [ ] Exercise 4: Command processor

**Challenges Faced:**

**Questions:**

**Notes:**

---

#### Day 5: Semaphores & Mutexes (⬜ Not Started)
**Date:** _______________  
**Time Spent:** _______________

**What I Learned:**

**Exercises Completed:**
- [ ] Exercise 1: Button ISR with semaphore
- [ ] Exercise 2: Mutex for shared counter
- [ ] Exercise 3: Counting semaphore
- [ ] Exercise 4: Priority inversion demo

**Challenges Faced:**

**Questions:**

**Notes:**

---

#### Days 6-7: Practice Project - Multi-Task LED Controller (⬜ Not Started)
**Date:** _______________  
**Time Spent:** _______________

**Project Status:**
- [ ] Task 1: LED pattern sequencer
- [ ] Task 2: Button handler
- [ ] Task 3: Serial command parser
- [ ] Task 4: Status reporter
- [ ] All patterns implemented
- [ ] No race conditions
- [ ] Button response <50ms

**What I Learned:**

**Challenges Faced:**

**Code Repository:** _______________

**Demo Video:** _______________

**Notes:**

---

### Week 2
(Template continues for Days 8-14...)

### Week 3
(Template continues for Days 15-21...)

### Week 4
(Template continues for Days 22-28...)

---

## Skills Acquired

### FreeRTOS Concepts
- [ ] Task creation and management
- [ ] Task priorities and scheduling
- [ ] Queues
- [ ] Semaphores
- [ ] Mutexes
- [ ] Event groups
- [ ] Task notifications
- [ ] Timers

### ESP32 Peripherals
- [ ] GPIO (input/output/interrupts)
- [ ] UART
- [ ] I2C
- [ ] SPI
- [ ] ADC
- [ ] DAC
- [ ] Timers
- [ ] PWM

### Connectivity
- [ ] WiFi Station mode
- [ ] WiFi AP mode
- [ ] HTTP Client
- [ ] HTTP Server
- [ ] MQTT
- [ ] Bluetooth Classic
- [ ] BLE

### Advanced Topics
- [ ] Power management
- [ ] Deep sleep modes
- [ ] Memory management
- [ ] Watchdog timers
- [ ] Interrupt handling
- [ ] Error handling
- [ ] OTA updates

---

## Projects Completed

1. **Week 1:** Multi-Task LED Controller  
   Status: ⬜ Not Started  
   Repository: _______________

2. **Week 2:** Sensor Dashboard  
   Status: ⬜ Not Started  
   Repository: _______________

3. **Week 3:** Power-Optimized Logger  
   Status: ⬜ Not Started  
   Repository: _______________

4. **Week 4:** Final Capstone  
   Status: ⬜ Not Started  
   Type: _______________  
   Repository: _______________

---

## Resources Used

### Documentation
- [ ] ESP-IDF Programming Guide
- [ ] FreeRTOS Reference Manual
- [ ] ESP32 Technical Reference

### Tutorials
- [ ] Espressif examples
- [ ] YouTube tutorials
- [ ] Online courses

### Community
- [ ] ESP32 Forum
- [ ] Reddit r/esp32
- [ ] Stack Overflow

---

## Questions & Answers

**Q1:** _______________  
**A1:** _______________

**Q2:** _______________  
**A2:** _______________

(Add more as you learn)

---

## Next Learning Session

**Planned Date:** _______________  
**Topic:** Day 1 - ESP-IDF vs Arduino  
**Preparation Needed:**
- [ ] ESP32 board ready
- [ ] USB cable connected
- [ ] PlatformIO working
- [ ] Read Day 1 content in learning plan

**Goals for Next Session:**
1. Complete all 3 exercises
2. Understand `extern "C"` requirement
3. Get comfortable with ESP_LOG macros

---

## Milestones

- [ ] **Week 1 Complete** - Understand FreeRTOS basics
- [ ] **Week 2 Complete** - Master hardware peripherals
- [ ] **Week 3 Complete** - Advanced RTOS concepts
- [ ] **Week 4 Complete** - Build real IoT device
- [ ] **Course Complete** - Ready for professional ESP32 development

---

**Last Updated:** November 16, 2025  
**Notes:** Ready to begin learning journey!

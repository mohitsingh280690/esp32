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
**Current Day:** Day 5  
**Current Challenge:** Day 5, Exercise 1 (Semaphores & Resource Management) - READY TO START
**Overall Progress:** 4/28 days (14%)

---

## Weekly Progress

### 🔵 Week 1: FreeRTOS Fundamentals (4/7 days completed)
- ✅ Day 1: ESP-IDF vs Arduino, Build System (COMPLETED)
  - ✅ Setup Verification: LED Blink
  - ✅ Exercise 3: ESP Logging Levels (4 log levels, counter, modulo operator)
  - **Key Learnings:** extern "C" linkage, vTaskDelay() requirement, watchdog timers, log level semantics
- ✅ Day 2: FreeRTOS Tasks Basics (COMPLETED)
  - ✅ Exercise 1: Two Talking Tasks (concurrent execution, function pointers)
  - ✅ Exercise 2: Task with Parameters (void* casting, passing data)
  - ✅ Exercise 3: Struct Parameters (grouping related data, arrow operator, race conditions)
- ✅ Day 3: Task Scheduling & Priorities (COMPLETED)
  - ✅ Exercise 1: Priority Demonstration (three tasks, different priorities)
  - ✅ Exercise 2: Dynamic Priority Change (runtime priority modification, task states)
  - **Key Learnings:** Priority preemption, TaskHandle_t opaque pointers, uxTaskPriorityGet(), vTaskPrioritySet(), NULL for self-reference, task states (READY vs BLOCKED), strcmp() returns 0 for match
- ✅ Day 4: Inter-Task Communication (Queues) (COMPLETED)
  - ✅ Exercise 1: Producer-Consumer Pattern (integers via queue)
  - ✅ Exercise 2: Sending Structs via Queue (sensor data simulation)
  - **Key Learnings:** typedef struct with _t convention, designated initializers vs field assignment in C++, struct memory padding/alignment, sizeof() for queue item size, %lu format specifier for uint32_t, queue data copying vs pointer sharing
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
**Date:** December 19-21, 2025  
**Time Spent:** ~3 hours  
**Status:** In Progress (2/3 exercises completed)

**What I Learned:**
- Tasks = Threads (same concept, different terminology)
- Function pointers: `&task` passes address, `task()` calls function
- Multiple tasks run concurrently via scheduler time slicing
- Equal priority tasks share CPU time (round-robin)
- `xTaskCreate()` parameters: function pointer, name, stack size, params, priority, handle
- When task calls vTaskDelay(), scheduler switches to other ready tasks
- **void* casting:** Two approaches - passing by value `(void*)500` vs passing by address `&variable`
- **Memory lifetime:** Local variables destroyed when function exits (stack vs static vs heap)
- **Undefined behavior:** Code that "works by luck" vs code that works by design
- **Timing guarantees:** Tasks created at high priority run before app_main exits
- **Race conditions:** Multiple tasks accessing same hardware (LED) causes unpredictable behavior

**Exercises Completed:**
- [x] Exercise 1: Two Talking Tasks (1s and 2s intervals, concurrent execution)
- [x] Exercise 2: Task Parameters (void* casting, passing scalar values directly)

**Key Understanding:**
- Task 1 delaying does NOT block Task 2 (scheduler switches contexts)
- Same timestamps appear when multiple tasks become ready simultaneously
- Using `task1()` instead of `&task1` would cause immediate call and crash
- **Passing by value:** `(void*)500` stores the value IN the pointer variable (no memory indirection)
- **Passing by address:** `&delay` passes memory location (variable must outlive task's read)
- **Cast difference:** `(int)pvParameter` vs `*(int*)pvParameter` - value vs dereference
- **Pointer size = int size on ESP32:** Both 32-bit, enabling the value-passing trick
- **Synchronization:** `vTaskDelay()` in app_main ensures tasks run and copy data before variables destroyed
- ESP-IDF's forgiving memory management often hides stack lifetime bugs (dangerous!)

**Challenges Faced:**
- Initially used pointer dereferencing `*(int*)pvParameter` with address passing
- Confusion about memory lifetime - when are local variables destroyed?
- Understanding why undefined behavior doesn't always crash
- Experimenting with intentionally breaking code (priority changes, no sync)
- Only one LED available - saw race condition firsthand (both tasks fighting for control)

**Deep Dive Topics Explored:**
- Why doesn't the code crash? (Timing, ESP-IDF memory management)
- When DOES task read happen relative to app_main exit?
- Attempted to force crash by lowering task priority (didn't crash - memory persists)
- Learned that "working by luck" vs "working by design" distinction
- 32-bit pointer size allowing direct value storage in pointer variable

**Questions Answered:**
- ✅ How to pass parameters to tasks? (void* casting, two methods)
- ✅ Why do variables persist after app_main exits? (Timing + forgiving memory management)
- ✅ What's the difference between passing value vs address?

**Notes:**
- Excellent exploration of C memory concepts and embedded timing issues
- Strong critical thinking demonstrated (challenged assumptions, tested edge cases)
- Ready for Exercise 3: Passing multiple parameters using structs

---

#### Day 3: Task Scheduling & Priorities (✅ Completed)
**Date:** December 22, 2025  
**Time Spent:** ~2 hours  
**Status:** Completed

**What I Learned:**
- Priority-based preemptive scheduling in FreeRTOS
- TaskHandle_t as opaque pointer type for task control
- uxTaskPriorityGet() to query task priority
- vTaskPrioritySet() to change priority at runtime
- NULL in FreeRTOS functions means "current task" - no handle needed for self-reference
- **Critical Discovery:** Priority only matters when tasks are READY to run
- Tasks in BLOCKED state (vTaskDelay) don't compete regardless of priority
- Shortened delays (10ms) needed to see priority preemption in action

**Exercises Completed:**
- [x] Exercise 1: Priority Demonstration (three tasks with priorities 1, 3, 5)
- [x] Exercise 2: Dynamic Priority Change (runtime priority boost with verification)

**Challenges Faced:**
- Initially used strcmp() incorrectly (forgot it returns 0 for match)
- First implementation with 1-second delays didn't show priority difference
- Learned that tasks must be READY (not BLOCKED) to compete for CPU

**Key Concepts Mastered:**
- Opaque pointers and why they're used (information hiding, API stability)
- Difference between controlling self (NULL) vs controlling other tasks (need handle)
- Task states: RUNNING, READY, BLOCKED, SUSPENDED
- Priority preemption behavior and when it applies
- Handle vs no handle - when each is needed

**C Concepts Learned:**
- strcmp() return values (0 = match, classic C gotcha)
- Opaque pointer pattern in C APIs
- NULL as special value meaning "current context"

**Questions Answered:**
- ✅ Why use handles at all if NULL works for self? (To control OTHER tasks)
- ✅ How to verify priority actually changed? (uxTaskPriorityGet())
- ✅ Why doesn't priority change behavior with long delays? (Tasks not competing - BLOCKED state)

**Notes:**
- Excellent hands-on discovery of RTOS fundamentals
- Testing revealed edge cases and deepened understanding
- Ready for inter-task communication patterns

---

#### Day 4: Queues - Inter-Task Communication (✅ Completed)
**Date:** December 26, 2025  
**Time Spent:** ~2 hours  
**Status:** Completed

**What I Learned:**
- **Producer-Consumer pattern** - Fundamental embedded design pattern for decoupling tasks
- Queue data copying mechanism - Queues COPY data, not store pointers
- **typedef struct** syntax and embedded C naming conventions (_t suffix)
- Struct memory padding and alignment for CPU efficiency
- sizeof() importance - never hardcode struct sizes due to padding
- C++ vs C initialization differences (designated initializers require C++20, field assignment works always)
- **Format specifiers:** %lu for uint32_t, not %u (platform-dependent)
- QueueHandle_t is already void* - no & needed when passing as parameter

**Exercises Completed:**
- [x] Exercise 1: Producer-Consumer Pattern (integers via queue)
- [x] Exercise 2: Sending Structs via Queue (sensor data with timestamp, ID, value)

**Challenges Faced:**
- Initial syntax error with C-style aggregate initialization in C++ context
- Double multiplication bug in logging (multiplied timestamp twice)
- Format specifier issue (%u vs %lu for uint32_t)
- Understanding when to use & with handles (QueueHandle_t vs TaskHandle_t)
- Copy-paste error in consumer log ("Sending" instead of "Received")

**Key Concepts Mastered:**
- Producer-Consumer pattern for rate-decoupling (fast producer, slow consumer or vice versa)
- Why queues copy data (safety, independence, no shared memory issues)
- Struct definition with typedef (cleaner syntax, matches FreeRTOS conventions)
- Designated initializers vs field assignment in C++
- Struct memory layout: [timestamp: 4B][sensor_id: 1B][padding: 3B][value: 4B] = 12B not 9B
- xQueueCreate(length, sizeof(struct)) - proper queue initialization
- xQueueSend(&data) and xQueueReceive(&buffer) - both need addresses

**C Concepts Learned:**
- **typedef struct pattern** - Creating clean type aliases
- **Struct padding/alignment** - CPU efficiency vs memory waste tradeoff
- **sizeof() operator** - Compile-time size calculation including padding
- **Designated initializers** - .field = value syntax (C++20)
- **Field assignment** - struct.field = value (always works)
- **Format specifiers** - Platform-specific integer types need proper formatting

**Design Pattern Recognition:**
- Producer-Consumer with queue buffer enables:
  * Sensor reading at fixed rate → variable processing time
  * UART asynchronous data → synchronous parsing
  * Button instant events → delayed action handling
  * Burst data capture → smooth processing flow

**Questions Answered:**
- ✅ Why copy data instead of pointers? (Task independence, memory safety, no race conditions)
- ✅ How to size a queue? (Consider burst capacity and processing time lag)
- ✅ What's portMAX_DELAY vs 0? (Block forever vs immediate return)
- ✅ Why use sizeof() not hardcoded size? (Padding makes actual size unpredictable)
- ✅ Can I use onboard ADC for sensor data? (Yes, but Day 13 - keep simulated for now to focus on queue mechanics)

**Notes:**
- Strong understanding of queue mechanics and struct handling
- Good debugging of C++ vs C syntax differences
- Pattern thinking emerging - recognizing where Producer-Consumer applies
- Ready for synchronization primitives (semaphores, mutexes)

---

---

#### Day 2: FreeRTOS Tasks (⬜ Not Started - DEPRECATED ENTRY)
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

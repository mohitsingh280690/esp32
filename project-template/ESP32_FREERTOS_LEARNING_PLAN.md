# ESP32 + FreeRTOS Complete Learning Plan

**Target Audience:** Intermediate developers with embedded experience but lacking deeper C knowledge  
**Duration:** 3-4 weeks (flexible, self-paced)  
**Goals:** 
- Master ESP32 hardware capabilities and FreeRTOS real-time programming
- **Build deep C programming knowledge** (pointers, memory, data structures)
- **Develop critical thinking** for embedded systems design

---

## 🚀 How to Use This Tutorial

### **For Students:**
1. Copy this entire repository/folder to your machine
2. Open the workspace in VS Code with PlatformIO extension
3. Reference this document and share it with GitHub Copilot Chat:
   - Use `@workspace` to give Copilot context about your project
   - Say: "I'm following the ESP32 learning plan in `.learning/` folder"
   - Copilot will act as your instructor based on this guide
4. Progress through exercises in `src/main.cpp`

### **For Copilot/AI Instructors:**
This document defines your teaching methodology. Follow these principles:

**Teaching Philosophy: Guided Discovery with C Education**
- ❌ **Never write implementation code in TODO comments**
- ❌ **Never show complete function implementations as hints**
- ✅ **Explain WHY before HOW** - Build critical thinking first
- ✅ **Teach C concepts** when they appear (pointers, structs, volatile, etc.)
- ✅ **Only mention function names** (e.g., "Use `xTaskCreate()`")
- ✅ **Point to documentation** AND explain the C concepts involved
- ✅ **Ask probing questions** about design choices and tradeoffs
- ✅ **Give conceptual hints with C education**, not code snippets

**Example of GOOD vs BAD hints:**

**❌ BAD (Too much help):**
```cpp
// TODO: Create task
// xTaskCreate(&task_function, "task1", 2048, NULL, 5, NULL);
```

**✅ GOOD (Guidance with C education):**
```cpp
// TODO: Create task using xTaskCreate()
// Hint: You need task function pointer, name string, stack size, parameters, priority, and handle
// C Concept: Why use &task_function? The & operator gets the function's address in memory.
// Critical Thinking: How much stack does your task need? Consider local variables + function calls.
```

### **Learning Flow:**
1. **Concept Introduction** - Explain theory with minimal examples
2. **Challenge Assignment** - Describe what to build (requirements only)
3. **Student Implements** - Student writes code using documentation
4. **Code Review** - AI reviews and provides feedback
5. **Iteration** - Student fixes issues with minimal hints
6. **Concept Mastery** - Confirm understanding with questions

### **Role Division**

**AI Instructor Role:**
- ✅ Explain concepts with theory and minimal examples
- ✅ Provide clear requirements and success criteria
- ✅ Review code and identify issues
- ✅ Give function names and suggest documentation to read
- ✅ Ask probing questions to check understanding
- ❌ Write implementation code in hints or comments
- ❌ Show complete solutions before student attempts

**Student Role:**
- ✅ Read ESP-IDF and FreeRTOS documentation
- ✅ Write all implementation code independently
- ✅ Test and debug solutions
- ✅ Ask specific questions when stuck
- ✅ Document learnings in progress tracker

---

## 📁 Project Workflow

### **Single Workspace Approach**

You will work in **one PlatformIO project** (`esp32-boilerplate/`) throughout the entire learning journey.

**Directory Structure:**
```
esp32-boilerplate/
├── .exercises/
│   ├── README.md              # Workflow guide
│   ├── completed/             # Your finished exercise code
│   │   ├── day1-ex2-arduino-comparison.cpp
│   │   ├── day1-ex3-logging-levels.cpp
│   │   └── day2-ex1-two-tasks.cpp
│   └── templates/             # Exercise starting templates
│       └── day2-ex2-task-parameters.cpp
│
├── .learning/                 # This directory
│   ├── ESP32_FREERTOS_LEARNING_PLAN.md
│   └── PROGRESS_TRACKER.md
│
├── src/
│   └── main.cpp              # ← YOU ALWAYS EDIT THIS FILE
│
├── platformio.ini
└── README.md
```

### **Exercise Workflow**

**Before Each Exercise:**
1. AI backs up current `src/main.cpp` → `.exercises/completed/day#-ex#-name.cpp`
2. AI provides new minimal template with TODO markers → `src/main.cpp`
3. Student stays in same VS Code window (no context loss!)

**Template Format (Minimal Guidance Only):**
```cpp
/**
 * Day X - Exercise Y: Topic Name
 * 
 * CHALLENGE: Brief description
 * 
 * REQUIREMENTS:
 * ✅ Specific requirement 1
 * ✅ Specific requirement 2
 * 
 * FUNCTIONS TO USE:
 * - function_name_1() - Brief purpose only
 * - function_name_2() - Brief purpose only
 */

// Necessary includes only
#include "header.h"

// TODO: Your task description (no code examples!)
```

**During Exercise:**
1. Open `src/main.cpp` (has TODO comments)
2. Read ESP-IDF/FreeRTOS documentation for mentioned functions
3. Write your implementation
4. Build: `pio run`
5. Upload: `pio run -t upload`
6. Test and iterate

**After Exercise:**
1. Type "ready for review"
2. I review your code and give feedback
3. You fix issues if needed
4. Move to next exercise

**Benefits:**
- ✅ **No context loss** - Same VS Code window throughout
- ✅ **No reconfiguration** - One PlatformIO project
- ✅ **Full history** - All solutions saved in `.exercises/completed/`
- ✅ **Easy reference** - View previous exercises anytime
- ✅ **Simple workflow** - Just edit `main.cpp` every time

---

## 📊 Progress Tracking

### Week 1: Foundations ⬜
- [ ] Day 1: ESP-IDF vs Arduino, Build System
- [ ] Day 2: FreeRTOS Tasks Basics
- [ ] Day 3: Task Scheduling & Priorities
- [ ] Day 4: Inter-Task Communication (Queues)
- [ ] Day 5: Semaphores & Mutexes
- [ ] Day 6-7: Practice Project: Multi-Task LED Controller

### Week 2: Hardware Peripherals ⬜
- [ ] Day 8: GPIO Deep Dive (Input/Output/ISR)
- [ ] Day 9: Timers (Hardware & Software)
- [ ] Day 10: UART Communication
- [ ] Day 11: I2C Protocol
- [ ] Day 12: SPI Protocol
- [ ] Day 13: ADC & DAC
- [ ] Day 14: Practice Project: Sensor Dashboard

### Week 3: Advanced FreeRTOS ⬜
- [ ] Day 15: Event Groups
- [ ] Day 16: Task Notifications
- [ ] Day 17: Memory Management & Heap
- [ ] Day 18: Watchdogs & Error Handling
- [ ] Day 19: Power Management & Sleep Modes
- [ ] Day 20: Interrupt Handling Deep Dive
- [ ] Day 21: Practice Project: Power-Optimized Sensor Logger

### Week 4: Connectivity & Real-World ⬜
- [ ] Day 22: WiFi Station & AP Mode
- [ ] Day 23: HTTP Client/Server
- [ ] Day 24: MQTT Protocol
- [ ] Day 25: Bluetooth Classic
- [ ] Day 26: BLE (Bluetooth Low Energy)
- [ ] Day 27-28: Final Project: IoT Device (choice below)

---

## 🧠 C Programming & Design Patterns Integrated Throughout

This tutorial teaches ESP32/FreeRTOS **AND** deepens your C programming knowledge **AND** professional embedded design patterns:

### Pointers & Memory (Days 2, 3, 17)
- Function pointers for task creation
- void* and type casting for generic parameters
- Pointer arithmetic and array relationships
- Stack vs heap allocation strategies
- Memory lifetime and dangling pointers

### Data Structures (Days 2, 6, 14)
- Struct for grouping task parameters
- typedef for cleaner code
- Passing structs by value vs pointer
- Memory layout, padding, and alignment
- Circular buffers for embedded systems

### Language Features (Days 5, 8, 20)
- volatile for hardware registers and ISR variables
- static for file scope and persistent state
- const correctness for read-only data
- Preprocessor macros vs functions
- enum for type-safe constants

### Systems Thinking (Days 5, 17, 18, 20)
- Race conditions and atomicity
- Critical sections and mutual exclusion
- Interrupt safety considerations
- Memory barriers and compiler optimization
- Resource lifetime management

### Embedded Design Patterns (Throughout)
Professional patterns you'll learn organically:

**Producer-Consumer (Day 4)**
- Decouple generation from processing
- Queue-based buffering
- Rate matching between tasks

**ISR Deferral / Interrupt Handler (Day 8, 20)**
- Minimal ISR, heavy work in task
- Semaphore signaling
- Real-time responsiveness

**Guard / Mutex Protection (Day 5)**
- Protect shared resources
- Critical section pattern
- Prevent race conditions

**Resource Pool (Day 5)**
- Counting semaphore for limited resources
- Prevent over-allocation
- Fair resource distribution

**Observer / Event-Driven (Day 15)**
- Event groups for coordination
- Wait for multiple conditions
- Power-efficient design

**State Machine (Day 15)**
- Explicit state tracking
- Event-driven transitions
- Protocol implementation

**Singleton (Throughout)**
- Hardware drivers as single instances
- Static variable patterns
- Initialization control

**Double Buffering (Day 12, 23)**
- Simultaneous read/write
- Display and DMA applications
- Prevent data tearing

**Approach:** Both C concepts and design patterns are taught **when you need them**, not as separate theory. Each exercise builds ESP32 skills, C understanding, AND professional patterns.

---

## 📚 Detailed Curriculum

## WEEK 1: FreeRTOS Fundamentals

### Day 1: ESP-IDF vs Arduino Framework
**Concepts:**
- ESP-IDF architecture vs Arduino abstraction
- `app_main()` vs `setup()/loop()`
- Build system: PlatformIO + CMake
- ESP-IDF logging system
- `extern "C"` wrapper requirement
- GPIO driver vs Arduino pinMode/digitalWrite

**C Concepts Introduced:**
- **extern "C"** - C++ name mangling vs C linkage
- **const char*** - String constants and pointers
- **static keyword** - Variable scope and lifetime
- **Preprocessor macros** - Variadic macros (ESP_LOGI)
- **Header files** - Include guards and declarations

**Exercise 1: Code Analysis (Guided)**
- Read and understand existing blink code in `src/main.cpp`
- Identify ESP-IDF patterns vs Arduino equivalents
- Understand each header file's purpose

**C Concepts to Notice:**
```cpp
static const char *TAG = "BLINK";  // Why static? Why const? Why char*?
extern "C" void app_main(void) { }  // Why extern "C"?
```

**Critical Thinking:**
- What does `static` do to TAG's scope?
- Why is TAG a pointer to const char, not just const char?
- Why must app_main() use extern "C"?

**Exercise 2: Side-by-Side Comparison (Guided)**
- Add Arduino equivalent code as comments
- Understand why ESP-IDF is more verbose
- Learn GPIO driver initialization pattern

**C Concepts - Comparison:**
```cpp
// Arduino: pinMode(2, OUTPUT);
// ESP-IDF: gpio_reset_pin(GPIO_NUM_2); gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
```

**Critical Thinking:**
- Why does ESP-IDF have separate reset and direction functions?
- What's GPIO_NUM_2? (Hint: it's an enum, not just the number 2)
- Why do enums provide better type safety than #define?

**Exercise 3: ESP Logging Levels (YOUR CODE)**
**Challenge:** Modify the LED blink task to use all 4 log levels:
- Use `ESP_LOGI()` when LED turns ON
- Use `ESP_LOGW()` when LED turns OFF  
- Use `ESP_LOGE()` every 5 blinks to report "5 blinks completed"
- Use `ESP_LOGD()` to show current blink counter

**Requirements:**
- [ ] Add a counter variable to track blinks
- [ ] Log at 4 different levels with appropriate messages
- [ ] Counter increments correctly
- [ ] Every 5th blink triggers error log
- [ ] Code compiles and runs

**Hints:**
- Use `static int counter = 0;` in the task function
- `if (counter % 5 == 0)` detects every 5th blink
- Format: `ESP_LOGI(TAG, "Blink #%d", counter);`
- Increment counter after each ON/OFF cycle

**C Concepts - Static Variables:**
```
Why static int counter = 0 inside a function?

Without static:
- counter created on stack each time function is called
- counter initialized to 0 every time
- counter destroyed when function exits

With static:
- counter allocated once (like a global)
- counter initialized only on first call
- counter retains value between calls
- counter still private to this function (not global scope)

Perfect for: Persistent state in repeatedly-called functions (like tasks!)
```

**Critical Thinking:**
- Why use static instead of a global variable?
- What happens if two tasks use the same static counter name?
- Would volatile be needed here? Why or why not?

**Key Takeaways:**
- `extern "C"` prevents C++ name mangling for C linkage
- Header includes: `freertos/FreeRTOS.h`, `driver/gpio.h`
- `static` for file scope (TAG) and persistent state (counter)
- `const` for read-only data (prevents accidental modification)
- ESP logging: LOGE (error), LOGW (warning), LOGI (info), LOGD (debug)
- Logging is thread-safe, Arduino Serial.print() is not

---

### Day 2: FreeRTOS Tasks - The Core Concept
**Concepts:**
- What is a task? (lightweight thread)
- Task states: Running, Ready, Blocked, Suspended
- `xTaskCreate()` parameters explained
- Task function signature: `void task(void *pvParameter)`
- Infinite loop requirement
- FreeRTOS naming conventions (v = void, x = BaseType_t)

**C Concepts Introduced:**
- **Function pointers** - `&` operator to get function address
- **void pointers** - Generic pointers and type casting
- **Static keyword** - Persistent state in task functions
- **Stack allocation** - Stack size parameter significance

**Exercise 1: Two Talking Tasks (YOUR CODE)**
**Challenge:** Create 2 tasks that print different messages at different intervals
- Task 1: Print "Hello from Task 1" every 1 second
- Task 2: Print "Hello from Task 2" every 2 seconds
- Both tasks should run simultaneously

**Requirements:**
- [ ] Create two separate task functions
- [ ] Both use proper `while(1)` loops
- [ ] Both use `vTaskDelay()` with different timings
- [ ] Both use ESP_LOGI with different tags
- [ ] Create both tasks in `app_main()`

**Hints:**
- Create functions: `void task1(void *pvParameter)` and `void task2(void *pvParameter)`
- Use different TAG names for each task
- Call `xTaskCreate()` twice in `app_main()`

**C Concepts to Think About:**
- Why does `xTaskCreate()` take `&task1` instead of `task1()`?
- What's the difference between the function name and function call?
- Why is pvParameter void* instead of int or another specific type?

**Exercise 2: Task with Parameters (YOUR CODE)**
**Challenge:** Pass a delay value to a generic blink task
- Create one task function that accepts delay as parameter
- Create 2 instances with different delays (500ms and 1500ms)
- Use different GPIOs for each (GPIO_NUM_2 and GPIO_NUM_4)

**Requirements:**
- [ ] Single task function accepts `void *pvParameter`
- [ ] Cast parameter to int for delay value
- [ ] Two task instances created with different parameters
- [ ] Both LEDs blink independently

**Hints:**
- You need to cast the parameter from void* to int
- Pass the delay value when creating the task
- Remember: You're passing an integer VALUE, not an address

**C Concepts - Deep Dive:**
- **Void pointers:** Why can't you use `pvParameter` directly? Because void* has no type information!
- **Type casting:** `(int)pvParameter` tells compiler "treat these bits as an integer"
- **Passing values:** `(void*)500` casts integer 500 to void* - you're passing the VALUE 500, not its address
- **Critical Thinking:** What's the difference between `(void*)500` and `(void*)&myInt`? When would you use each?

**Challenge Question:** Can you pass a GPIO pin number as a parameter too? How would you pass TWO values?

**Exercise 3: Three LEDs at Different Rates (YOUR CODE)**
**Challenge:** Create 3 tasks controlling 3 LEDs
- LED 1 (GPIO_NUM_2): 200ms blink
- LED 2 (GPIO_NUM_4): 500ms blink  
- LED 3 (GPIO_NUM_5): 1000ms blink

**Requirements:**
- [ ] 3 separate GPIOs configured
- [ ] 3 tasks created
- [ ] All run simultaneously
- [ ] Clean, organized code

**Hints:**
- One option: Create a reusable task function and pass parameters
- Another option: Create three separate task functions
- Consider which approach scales better

**Critical Thinking:**
- What if you need to pass BOTH pin number AND delay? (Hint: struct)
- Where should you allocate this struct - stack or heap? Why?
- What happens to local variables in `app_main()` after it exits?

**C Concepts - Struct Introduction:**
```cpp
// Example of grouping related data (don't copy, understand!)
typedef struct {
    int pin;
    int delay_ms;
} blink_config_t;
```
- Why use typedef? Cleaner syntax when declaring variables
- Why pass struct pointer instead of copying the whole struct?
- How do you access struct members? `config->pin` vs `config.pin`

**Key Takeaways:**
- Stack size selection (2048, 4096 bytes) - based on local variables + calls
- `vTaskDelay()` yields CPU to other tasks - prevents watchdog
- `portTICK_PERIOD_MS` vs `pdMS_TO_TICKS()` - time unit conversion
- Tasks run truly concurrently on ESP32 (dual-core!)
- **Struct pointers** for passing multiple parameters
- **Memory lifetime** considerations in multi-tasking

---

### Day 3: Task Scheduling & Priorities
**Concepts:**
- Priority levels (0 = lowest, higher number = higher priority)
- Preemptive scheduling
- Time slicing for equal priority tasks
- `vTaskPrioritySet()`, `vTaskDelete()`, `vTaskSuspend()`

**C Concepts Introduced:**
- **TaskHandle_t** - Opaque pointer types for handles
- **typedef** - Creating type aliases
- **NULL vs nullptr** - C-style null pointers
- **Enumeration** - Priority level constants

**Exercise 1: Priority Demonstration (YOUR CODE)**
**Challenge:** Create 3 tasks with different priorities (1, 3, 5)
- Each task prints its priority and increments a counter
- Observe which task runs most frequently
- Use ESP_LOGI to report counts every second

**Requirements:**
- [ ] Three tasks with priorities 1, 3, and 5
- [ ] Each maintains its own counter
- [ ] Periodic logging shows execution frequency
- [ ] Demonstrate priority preemption

**C Concepts - Handles and Opaque Pointers:**
```
TaskHandle_t myTaskHandle = NULL;

What is TaskHandle_t?
- It's a typedef for a pointer type
- "Opaque" means you don't see the struct definition
- You just pass it to FreeRTOS functions
- NULL is the "no handle" value

Why opaque?
- Hides implementation details
- Prevents accidental modification
- Cleaner API
- Implementation can change without breaking your code
```

**Critical Thinking:**
- Why do higher priority tasks starve lower ones?
- What prevents the highest priority task from running forever?
- How does vTaskDelay() give other tasks a chance?
- When would you want priority 0 (never!)

**Exercise 2: Dynamic Priority Change (YOUR CODE)**
**Challenge:** Change task priority at runtime
- Start 2 tasks at same priority
- After 5 seconds, boost one task's priority
- Observe the behavior change
- Log when priority changes

**Hints:**
- Use `vTaskPrioritySet()` to change priority
- You need the TaskHandle_t for the task to modify
- Save the handle when creating: `xTaskCreate(..., &handle);`

**C Concepts - Handles for Control:**
```
Why pass a handle to vTaskPrioritySet()?

TaskHandle_t task1_handle = NULL;
xTaskCreate(&task1, "Task1", 2048, NULL, 5, &task1_handle);

Later:
vTaskPrioritySet(task1_handle, 10);  // Boost priority

The handle is a REFERENCE to the task object.
Without it, how would FreeRTOS know WHICH task to modify?
```

**Key Takeaways:**
- Higher priority tasks preempt lower ones
- Idle task (priority 0) runs when nothing else can
- Don't starve low-priority tasks
- **TaskHandle_t** provides control over running tasks
- Handles are C's way of object references

---

### Day 4: Queues - Inter-Task Communication
**Concepts:**
- Queue creation: `xQueueCreate(length, item_size)`
- Sending: `xQueueSend()`, `xQueueSendToBack()`, `xQueueSendToFront()`
- Receiving: `xQueueReceive()` (blocking)
- Queue full/empty handling

**C Concepts Introduced:**
- **sizeof operator** - Getting type sizes at compile time
- **Address-of &** - Passing data to queue
- **Memory copy** - How queues copy data
- **Blocking operations** - Pointer to receive buffer

**Exercise 1: Producer-Consumer Pattern (YOUR CODE)**
**Challenge:** Create producer and consumer tasks communicating via queue
- Producer: Sends incrementing integers (0, 1, 2, ...) every 500ms
- Consumer: Receives and logs the integers
- Queue size: 5 items

**DESIGN PATTERN: Producer-Consumer**
This is one of the most fundamental patterns in embedded systems!

**Problem it solves:**
- Decouple data generation from data processing
- Handle different rates (fast producer, slow consumer or vice versa)
- Buffer data to prevent loss during processing

**Why in embedded:**
- Sensor reads at fixed rate, processing time varies
- UART receives data asynchronously, parsing takes time
- Button events are instant, actions take longer

**Requirements:**
- [ ] Create queue with `xQueueCreate()`
- [ ] Producer task sends integers to queue
- [ ] Consumer task receives and logs integers
- [ ] Handle queue full/empty properly

**Hints:**
- Queue needs: length (5) and item size (sizeof(int))
- Use `&data` when sending (address of variable)
- Use `&received` when receiving (address to store result)
- Check return values for success

**C Concepts - Queues and Memory:**
```
Why xQueueSend(queue, &data, timeout)?

QueueHandle_t queue = xQueueCreate(5, sizeof(int));

int data = 42;
xQueueSend(queue, &data, portMAX_DELAY);
         //       ^--- Why & ?

The queue COPIES your data:
1. You give the address of your data (&data)
2. Queue reads sizeof(int) bytes from that address
3. Queue stores a COPY internally
4. Your original variable is unchanged

This means:
- Safe to use local variables
- Data is decoupled from sender
- Each item in queue is independent

Compare to passing pointers:
xQueueSend(queue, &ptrToData, ...);  // Sends the POINTER value
                                      // Receiver gets same pointer
                                      // Both share the data (danger!)
```

**Critical Thinking - Pattern Analysis:**
- Why does queue copy data instead of storing pointers?
- What happens if producer is consistently faster than consumer?
- How do you size the queue? (Think: maximum burst, processing time)
- What if data changes after xQueueSend but before receiver reads it?

**Pattern Recognition:**
- Where else would Producer-Consumer apply?
  * UART RX → Command Parser
  * ADC Sampling → Signal Processing
  * Button Events → Action Handler
  * Sensor Readings → Data Logger
- Why is the queue the "magic" that makes this work?
- What would happen without the queue? (Polling? Shared variable?)

**Exercise 2: Sending Structs (YOUR CODE)**
**Challenge:** Send a struct with multiple fields via queue
- Define struct with: timestamp, sensor_id, value
- Producer sends sensor readings
- Consumer receives and displays all fields

**Requirements:**
- [ ] Define struct type with typedef
- [ ] Queue created with sizeof(your_struct_t)
- [ ] Producer fills struct and sends
- [ ] Consumer receives and logs all fields

**C Concepts - Structs in Queues:**
```cpp
typedef struct {
    uint32_t timestamp;
    uint8_t sensor_id;
    float value;
} sensor_data_t;

QueueHandle_t queue = xQueueCreate(10, sizeof(sensor_data_t));

sensor_data_t reading = {
    .timestamp = 12345,
    .sensor_id = 1,
    .value = 23.5
};

xQueueSend(queue, &reading, portMAX_DELAY);

Why this works:
- Queue copies ALL sizeof(sensor_data_t) bytes
- Struct padding is included
- Designated initializers (.field = value) are clear
- No dynamic allocation needed
```

**Critical Thinking:**
- What's the memory cost of queuing structs vs integers?
- When would you queue pointers instead? (Advanced: requires malloc/free)
- How does struct padding affect queue size?

**Key Takeaways:**
- Queues are FIFO by default
- **Queues copy data** - Pass address with &
- **sizeof()** gets type size at compile time
- Blocking timeout: `portMAX_DELAY` vs `pdMS_TO_TICKS()`
- Check return value (`pdTRUE` / `pdFALSE`)
- **Structs** can be queued directly - efficient for multiple values

---

### Day 5: Semaphores & Mutexes
**Concepts:**
- Binary semaphore (0 or 1)
- Counting semaphore (resource counting)
- Mutex (mutual exclusion for shared resources)
- `xSemaphoreCreateBinary()`, `xSemaphoreCreateMutex()`
- `xSemaphoreTake()`, `xSemaphoreGive()`

**C Concepts Introduced:**
- **volatile keyword** - Why shared variables need it
- **Race conditions** - When does code become non-atomic?
- **IRAM_ATTR** - What does this do and why?
- **Critical sections** - portENTER_CRITICAL() usage
- **Memory ordering** - Compiler optimization pitfalls

**Exercise 1: Button ISR → Semaphore → Task (YOUR CODE)**
**Challenge:** Implement button debouncing using semaphore
- Button press triggers ISR
- ISR gives semaphore
- Task takes semaphore and processes

**DESIGN PATTERN: ISR Deferral / Interrupt Handler**
One of the most critical patterns in embedded systems!

**Problem it solves:**
- ISRs must be FAST (microseconds, not milliseconds)
- Heavy processing in ISR causes system instability
- Need to defer work to task context

**Pattern structure:**
1. ISR does minimal work (set flag, give semaphore)
2. Semaphore signals waiting task
3. Task does the heavy processing

**Why this matters:**
- ISRs block other interrupts (bad for real-time)
- Can't use many FreeRTOS functions in ISR
- Stack space limited in ISR context
- Logging, delays, complex logic must be in task

**Requirements:**
- [ ] Create binary semaphore
- [ ] Write ISR handler with IRAM_ATTR
- [ ] Task waits on semaphore
- [ ] Proper GPIO interrupt configuration

**Hints:**
- Use `xSemaphoreCreateBinary()`
- ISR uses `xSemaphoreGiveFromISR()`
- Task uses `xSemaphoreTake()`

**C Concepts - ISR Safety:**
- **IRAM_ATTR:** Forces function into internal RAM (why? flash cache disabled in ISR!)
- **FromISR suffix:** Special versions safe to call from interrupts
- **No logging in ISR:** ESP_LOGI allocates memory - not ISR-safe!

**Critical Thinking:**
- Why can't you call vTaskDelay() in an ISR?
- What happens if you forget IRAM_ATTR?
- Why pass semaphore through ISR instead of directly setting a flag?

**Exercise 2: Mutex Protecting Shared Counter (YOUR CODE)**
**Challenge:** Two tasks increment a shared counter
- Without mutex: Observe race condition
- With mutex: Observe correct behavior
- Log the counter value to compare

**DESIGN PATTERN: Guard / Mutex Protection**

**Problem it solves:**
- Multiple tasks accessing shared resource
- Race conditions on read-modify-write operations
- Need mutual exclusion (only one task at a time)

**Pattern structure:**
```
xSemaphoreTake(mutex, portMAX_DELAY);
// Critical section - only one task here
shared_resource_access();
xSemaphoreGive(mutex);
```

**Why in embedded:**
- Shared UART/SPI peripherals
- Global data structures
- Hardware register sequences
- Resource allocation tracking

**Requirements:**
- [ ] Global counter variable
- [ ] Two tasks incrementing the counter
- [ ] Mutex protecting the counter
- [ ] Demonstrate the difference with/without mutex

**C Concepts - Race Conditions:**
```cpp
// Why is this NOT atomic?
counter++;  // Actually: read counter, add 1, write counter

// What if task switches between read and write?
// Task 1: Read counter = 5
// <context switch>
// Task 2: Read counter = 5, increment, write 6
// <context switch>  
// Task 1: Increment old value (5), write 6  ← Lost an increment!
```

**Critical Thinking:**
- Does making counter `volatile` fix the race condition? Why not?
- What does volatile actually do?
- When DO you need volatile? (Hint: hardware registers, ISR-modified flags)

**Exercise 3: Understanding Volatile (DEMONSTRATION)**
**Challenge:** Create a scenario showing when volatile matters

**C Concept - Volatile Deep Dive:**
```cpp
// Without volatile - compiler may optimize away reads
int flag = 0;
while (flag == 0) {
    // Compiler sees: "flag never changes in this loop"
    // Optimizes to: while(true) - infinite loop!
}

// With volatile - compiler must read from memory every time
volatile int flag = 0;  // "This can change outside this code's control"
```

**When to use volatile:**
- Hardware registers (memory-mapped I/O)
- Variables modified in ISRs
- Variables modified by other cores/DMA

**When NOT to use volatile:**
- Doesn't make operations atomic!
- Doesn't replace mutexes for task synchronization
- Not needed for RTOS-protected variables

**Key Takeaways:**
- ISR-safe versions: `FromISR()` suffix
- Mutex prevents race conditions
- Semaphores for synchronization, mutexes for protection

---

### Day 6-7: Practice Project - Multi-Task LED Controller
**Project Requirements:**
- 4 LEDs with independent control
- Task 1: LED pattern sequencer (reads from queue)
- Task 2: Button handler (sends patterns to queue)
- Task 3: Serial command parser (change speed, pattern)
- Task 4: Status reporter (prints state every 5s)
- Use: Queues, semaphores, proper priorities

**Patterns to Implement:**
1. Knight Rider (sweeping)
2. Blink all together
3. Alternating pairs
4. Random

**Success Criteria:**
- No race conditions
- Responsive button (<50ms)
- Clean serial output
- Proper resource cleanup

---

## WEEK 2: Hardware Peripherals Mastery

### Day 8: GPIO Deep Dive
**Concepts:**
- Pull-up/pull-down resistors
- Interrupt types: Rising, Falling, Both edges, Low/High level
- `gpio_config()` structure
- ISR registration and handling
- GPIO matrix and pin remapping

**C Concepts Introduced:**
- **Struct initialization** - Designated initializers (.field = value)
- **Bitwise shifts for masks** - `(1ULL << pin)` for pin selection
- **ULL suffix** - Unsigned long long for 64-bit GPIO mask
- **IRAM_ATTR** - Function attribute for ISR placement
- **Function pointers** - ISR handler registration

**Exercise 1: Button with Interrupt and ISR Deferral (YOUR CODE)**
**Challenge:** Implement button handling using ISR → Queue → Task pattern
- Button press triggers interrupt
- ISR minimal - just queues event
- Task handles button action (logging, LED toggle, etc.)

**DESIGN PATTERN: ISR Deferral (Reinforcement)**
You learned this in Day 5, now see it with GPIO interrupts!

**Why this matters:**
- ISRs run in interrupt context (limited stack, no FreeRTOS calls)
- GPIO interrupts are frequent (button bouncing = many triggers!)
- Heavy processing must happen in task context
- Queue from ISR to Task is the professional approach

**Requirements:**
- [ ] Configure GPIO as input with interrupt
- [ ] Register ISR handler with IRAM_ATTR
- [ ] ISR sends event to queue
- [ ] Task receives from queue and processes
- [ ] Handle debouncing

**Hints:**
- Use `gpio_config()` with designated initializers
- `gpio_install_isr_service()` before registering handlers
- ISR: `xQueueSendFromISR(queue, &event, NULL)`
- Task: `xQueueReceive(queue, &event, portMAX_DELAY)`

**C Concepts - Designated Initializers:**
```cpp
// Old C style (positional)
gpio_config_t conf = {0x01, GPIO_MODE_INPUT, 1, 0, GPIO_INTR_NEGEDGE};
// Hard to read! What's what?

// Designated initializers (C99+)
gpio_config_t io_conf = {
    .pin_bit_mask = (1ULL << GPIO_NUM_0),  // Clear what this is
    .mode = GPIO_MODE_INPUT,                // Clear
    .pull_up_en = GPIO_PULLUP_ENABLE,      // Clear
    .pull_down_en = GPIO_PULLDOWN_DISABLE, // Clear
    .intr_type = GPIO_INTR_NEGEDGE         // Clear
};
// Much better! Self-documenting code.

// Why ULL suffix?
(1ULL << GPIO_NUM_0)
//  ^^^ Unsigned Long Long (64-bit)
// ESP32 has 40+ GPIO pins, needs 64-bit mask
// Without ULL: shift might overflow on pin numbers > 31
```

**Critical Thinking:**
- Why use queue instead of global variable?
- What if multiple buttons trigger same ISR?
- How would you pass which button was pressed?
- Why can't you use ESP_LOGI directly in ISR?

**Exercise 2: Multi-Button with Event Data (YOUR CODE)**
**Challenge:** Handle 3 buttons, each triggering different actions
- Button 1: Increment counter
- Button 2: Decrement counter  
- Button 3: Reset counter
- All use same ISR but send button ID to queue

**Pattern: Single Handler, Multiple Sources**

**Requirements:**
- [ ] Configure 3 GPIOs with interrupts
- [ ] Single ISR handles all buttons
- [ ] Queue contains button ID
- [ ] Task performs action based on ID

**Hints:**
- Pass button ID as ISR arg: `gpio_isr_handler_add(pin, isr, (void*)button_id)`
- Retrieve in ISR: `uint32_t button = (uint32_t)arg;`
- Send button ID to queue

**C Concept - ISR Arguments:**
```cpp
// Register ISR with custom argument
void IRAM_ATTR button_isr_handler(void *arg) {
    uint32_t button_id = (uint32_t)arg;  // Retrieve passed argument
    xQueueSendFromISR(queue, &button_id, NULL);
}

// Register for each button with different argument
gpio_isr_handler_add(GPIO_NUM_0, button_isr_handler, (void*)1);
gpio_isr_handler_add(GPIO_NUM_2, button_isr_handler, (void*)2);
gpio_isr_handler_add(GPIO_NUM_4, button_isr_handler, (void*)3);
```

**Real-World Usage:**
- Keypad scanning
- Multi-sensor systems
- Industrial control panels
- Game controllers

**Key Takeaways:**
- **ISR Deferral pattern** is standard for GPIO interrupts
- Designated initializers make struct init clear
- ULL suffix for 64-bit GPIO masks
- IRAM_ATTR required for ISR functions
- Queue-based event handling keeps ISRs fast

---

### Day 9: Timers (Hardware & Software)
**Concepts:**
- Hardware timers: 4 groups, 64-bit counters
- Timer ISR callbacks
- Software timers: `xTimerCreate()`
- One-shot vs auto-reload
- Timer precision vs power consumption

**Hands-On:**
```cpp
// Exercise 1: Precise 100ms hardware timer
// Exercise 2: Software timer for periodic sensor reading
// Exercise 3: PWM using timer (LED brightness)
// Exercise 4: Stopwatch with microsecond precision
```

---

### Day 10: UART Communication
**Concepts:**
- Multiple UART ports (0, 1, 2)
- Baud rates, parity, stop bits
- TX/RX buffers
- `uart_read_bytes()` vs `uart_get_buffered_data_len()`
- Pattern detection

**Hands-On:**
```cpp
// Exercise 1: Echo server (receive and send back)
// Exercise 2: AT command parser
// Exercise 3: GPS NMEA sentence parser (simulated)
// Exercise 4: Binary protocol with checksum
```

---

### Day 11: I2C Protocol
**Concepts:**
- Master/Slave configuration
- Clock speed: 100kHz (standard), 400kHz (fast)
- 7-bit vs 10-bit addressing
- ACK/NACK handling
- Common sensors: BME280, OLED displays

**Hands-On:**
```cpp
// Exercise 1: I2C scanner (find device addresses)
// Exercise 2: Read temperature from BMP280/BME280
// Exercise 3: Write to OLED display (SSD1306)
// Exercise 4: Multi-sensor I2C bus
```

---

### Day 12: SPI Protocol
**Concepts:**
- Master/Slave, full-duplex
- Clock polarity (CPOL) and phase (CPHA)
- CS (Chip Select) management
- DMA transfers
- Common devices: SD cards, TFT displays, NRF24L01

**C Concepts Introduced:**
- **DMA and memory** - Direct Memory Access buffers
- **Buffer alignment** - Why DMA needs aligned memory
- **Array pointers** - Passing buffers to hardware
- **const correctness** - TX buffer is const, RX is not

**Exercise 1: SPI Display with Double Buffering (YOUR CODE)**
**Challenge:** Send image data to TFT display without tearing
- Front buffer: Currently displayed
- Back buffer: Being drawn to
- Swap buffers when frame complete
- Display task and draw task run concurrently

**DESIGN PATTERN: Double Buffering**

**Problem it solves:**
- Display shows partial/corrupted frames (tearing)
- Can't update display while reading from it
- Drawing is slow, need smooth animation
- DMA transfer and CPU drawing conflict

**Pattern structure:**
```cpp
uint8_t buffer1[SCREEN_SIZE];
uint8_t buffer2[SCREEN_SIZE];
uint8_t *front_buffer = buffer1;  // Currently shown
uint8_t *back_buffer = buffer2;   // Being drawn to

// Draw to back buffer
draw_graphics(back_buffer);

// Swap buffers atomically
uint8_t *temp = front_buffer;
front_buffer = back_buffer;
back_buffer = temp;

// Send front buffer to display via DMA
spi_send_display(front_buffer, SCREEN_SIZE);
```

**Why in embedded:**
- Smooth animations without tearing
- DMA can read while CPU writes
- Audio streaming (record while playing)
- Image processing pipelines

**Requirements:**
- [ ] Allocate two buffers
- [ ] Draw task writes to back buffer
- [ ] Display task sends front buffer via SPI
- [ ] Swap buffers between frames
- [ ] Use mutex or semaphore for sync

**Hints:**
- Use pointers to swap buffers (just swap pointers, not data!)
- Protect buffer swap with mutex
- DMA buffer must be in DMA-capable memory
- Use `heap_caps_malloc(size, MALLOC_CAP_DMA)`

**C Concepts - Pointer Swapping:**
```cpp
// Inefficient: Copy entire buffer
memcpy(buffer1, buffer2, SCREEN_SIZE);  // Slow! Copies all data

// Efficient: Swap pointers
uint8_t *temp = front_buffer;  // Save front pointer
front_buffer = back_buffer;     // Front now points to back
back_buffer = temp;             // Back now points to old front
// Lightning fast! Just swapped addresses, not data
```

**Critical Thinking:**
- Why swap pointers instead of copying data?
- What happens if you forget synchronization?
- Could triple buffering help? When?
- How does this relate to V-sync in gaming?

**Real-World Usage:**
- LCD/OLED displays
- Audio DAC streaming
- Video frame processing
- Game rendering

**Exercise 2: High-Speed Data Acquisition with DMA (YOUR CODE)**
**Challenge:** Capture sensor data via SPI at high speed
- Use DMA to avoid CPU overhead
- Buffer incoming data
- Process in separate task
- Don't lose samples during processing

**Pattern: DMA + Producer-Consumer**
Combines two patterns!

**Requirements:**
- [ ] Configure SPI with DMA
- [ ] Circular DMA buffer or ping-pong buffers
- [ ] ISR signals when buffer full
- [ ] Processing task consumes buffered data

**Key Takeaways:**
- **Double Buffering** prevents display tearing
- Pointer swapping is faster than data copying
- DMA buffers need special memory allocation
- Combines multiple patterns for complex tasks

---

### Day 13: ADC & DAC
**Concepts:**
- 12-bit ADC (0-4095)
- Attenuation: 0dB (1V), 11dB (3.3V)
- Calibration for accuracy
- 8-bit DAC output
- Continuous vs single-shot mode

**Hands-On:**
```cpp
// Exercise 1: Read potentiometer value
// Exercise 2: Battery voltage monitor (with voltage divider)
// Exercise 3: DAC sine wave generator
// Exercise 4: Audio input level meter (VU meter)
```

---

### Day 14: Practice Project - Sensor Dashboard
**Project Requirements:**
- Read 3 sensors: Temperature (I2C), Light (ADC), Button state (GPIO)
- Display on OLED or Serial
- Update rates: Temp 1Hz, Light 5Hz, Button immediate
- Log data to SD card every 10s
- Buzzer alert if temperature > threshold

**Architecture:**
- Sensor reading tasks (3)
- Display update task
- SD card writer task
- Alert manager task
- Queues for data flow

---

## WEEK 3: Advanced FreeRTOS Concepts

### Day 15: Event Groups
**Concepts:**
- 24 event bits per group
- `xEventGroupSetBits()`, `xEventGroupWaitBits()`
- Wait for ANY bit vs ALL bits
- Synchronization points
- Difference from semaphores/queues

**C Concepts Introduced:**
- **Bit manipulation** - Setting, clearing, testing bits
- **Bitwise OR** - Combining multiple bit flags
- **Bitwise AND** - Testing multiple conditions
- **Bitmasks** - Defining flag constants

**Exercise 1: Wait for Multiple Conditions (YOUR CODE)**
**Challenge:** Initialize system only when WiFi AND time sync are ready
- Task 1: Simulates WiFi connection (sets WiFi Ready bit after 3s)
- Task 2: Simulates time sync (sets Time Ready bit after 5s)
- Task 3: Waits for BOTH bits before starting main application

**DESIGN PATTERN: Observer / Event-Driven Architecture**

**Problem it solves:**
- Multiple tasks need to coordinate
- Avoid polling (wastes CPU and power)
- Wait for multiple conditions efficiently
- Synchronization without tight coupling

**Pattern structure:**
```
Task 1: xEventGroupSetBits(events, WIFI_READY_BIT);
Task 2: xEventGroupSetBits(events, TIME_READY_BIT);
Task 3: xEventGroupWaitBits(events, WIFI_READY_BIT | TIME_READY_BIT, ...);
```

**Why in embedded:**
- Power efficient (tasks blocked, not polling)
- Clean separation of concerns
- Multiple tasks can wait on same events
- One event can notify multiple waiters

**Requirements:**
- [ ] Create event group
- [ ] Define bit masks for each event
- [ ] Tasks set their respective bits
- [ ] Main task waits for ALL bits
- [ ] Log when each event occurs

**Hints:**
- Use `xEventGroupCreate()`
- Define bits: `#define WIFI_READY_BIT (1 << 0)`
- Wait for all: use `pdTRUE` for `xWaitForAllBits`
- Use `xEventGroupWaitBits()` with both bits in mask

**C Concepts - Bit Manipulation:**
```cpp
// Define individual bits
#define WIFI_READY_BIT  (1 << 0)  // Bit 0: 0b00000001
#define TIME_READY_BIT  (1 << 1)  // Bit 1: 0b00000010
#define SENSOR_READY_BIT (1 << 2) // Bit 2: 0b00000100

// Combine bits with OR
EventBits_t bits_to_wait = WIFI_READY_BIT | TIME_READY_BIT;
                        // Result: 0b00000011

// Set a bit
xEventGroupSetBits(events, WIFI_READY_BIT);

// Wait for ANY bit
xEventGroupWaitBits(events, WIFI_READY_BIT | TIME_READY_BIT, 
                    pdFALSE, pdFALSE, portMAX_DELAY);
                    
// Wait for ALL bits
xEventGroupWaitBits(events, WIFI_READY_BIT | TIME_READY_BIT,
                    pdFALSE, pdTRUE, portMAX_DELAY);
                           //  ^--- pdTRUE = wait for ALL
```

**Critical Thinking - Pattern Recognition:**
- Why event groups instead of multiple semaphores?
- How is this different from polling a flag variable?
- What happens if you forget to set a bit? (Task waits forever!)
- Where else would Observer pattern help?
  * System initialization sequences
  * Multi-sensor ready states
  * Protocol handshake steps
  * Power management transitions

**Exercise 2: State Machine with Event Groups (YOUR CODE)**
**Challenge:** Implement a system state machine
- States: INIT → CONNECTING → READY → RUNNING → ERROR
- Events trigger state transitions
- Different tasks can trigger events
- Display current state

**DESIGN PATTERN: State Machine**

**Problem it solves:**
- Complex system behavior with multiple states
- State-dependent behavior
- Clean transition logic
- Prevents invalid state combinations

**Pattern structure:**
```cpp
typedef enum {
    STATE_INIT,
    STATE_CONNECTING,
    STATE_READY,
    STATE_RUNNING,
    STATE_ERROR
} system_state_t;

// Current state
static volatile system_state_t current_state = STATE_INIT;

// State transition function
void transition_to_state(system_state_t new_state) {
    ESP_LOGI(TAG, "State: %d -> %d", current_state, new_state);
    current_state = new_state;
    // Set event bit for new state
    xEventGroupSetBits(state_events, (1 << new_state));
}

// State handler
switch(current_state) {
    case STATE_INIT:
        // Initialization logic
        transition_to_state(STATE_CONNECTING);
        break;
    case STATE_CONNECTING:
        // Connection logic
        if (connected) transition_to_state(STATE_READY);
        break;
    // ... more states
}
```

**Why in embedded:**
- Protocol implementations (TCP, USB, etc.)
- UI state management
- Power mode transitions
- Startup/shutdown sequences

**Requirements:**
- [ ] Define enum for states
- [ ] Implement state transition function
- [ ] Multiple events trigger transitions
- [ ] Tasks wait for specific states
- [ ] Handle error conditions

**Hints:**
- Use enum for state definition
- One event bit per state
- State machine runs in dedicated task
- Other tasks wait for required states

**Critical Thinking - State Machines:**
- Why use enum instead of #define?
- Should state variable be volatile?
- How do you prevent invalid transitions?
- What if multiple tasks try to change state?

**Real-World Examples:**
- WiFi connection state machine
- Bluetooth pairing states
- Battery charging states
- Motor control states
- Communication protocol states

**Exercise 3: Multi-Button Combinations (YOUR CODE)**
**Challenge:** Detect keyboard-style combinations
- Individual buttons set bits
- Detect specific combinations (like Ctrl+Alt+Del)
- Action only when all buttons pressed simultaneously
- Release detection

**Pattern: Event Combination Detection**

**Requirements:**
- [ ] 3 button inputs with interrupts
- [ ] Each button sets event bit
- [ ] Detect specific combinations
- [ ] Clear bits on release
- [ ] Log which combination detected

**Critical Thinking:**
- How long do you wait for combination completion?
- What if buttons aren't pressed simultaneously?
- How do you debounce multiple buttons?

**Key Takeaways:**
- Event groups for multiple conditions
- **Observer pattern** - Wait for events, don't poll
- **State Machine pattern** - Clean state management
- Bit manipulation for efficient flag management
- Power-efficient coordination between tasks

---

### Day 16: Task Notifications
**Concepts:**
- Lightweight alternative to semaphores/queues
- Each task has 32-bit notification value
- Faster than queues (no memory allocation)
- `xTaskNotify()`, `ulTaskNotifyTake()`
- Use cases and limitations

**Hands-On:**
```cpp
// Exercise 1: ISR → Task notification (faster than semaphore)
// Exercise 2: Task notification as event flag
// Exercise 3: Notification value as counter
```

---

### Day 17: Memory Management
**Concepts:**
- Heap types: heap_caps, internal vs external RAM
- `malloc()` vs `heap_caps_malloc()`
- Memory fragmentation
- Stack overflow detection
- `heap_caps_get_free_size()`

**Hands-On:**
```cpp
// Exercise 1: Monitor heap usage over time
// Exercise 2: Intentional stack overflow (to understand errors)
// Exercise 3: Allocate DMA-capable memory
// Exercise 4: Memory leak detection
```

---

### Day 18: Watchdogs & Error Handling
**Concepts:**
- Task watchdog timer (TWDT)
- Interrupt watchdog timer (IWDT)
- `esp_task_wdt_add()`, `esp_task_wdt_reset()`
- Panic handler and core dumps
- `ESP_ERROR_CHECK()` macro

**Hands-On:**
```cpp
// Exercise 1: Trigger watchdog reset (intentional)
// Exercise 2: Graceful error recovery
// Exercise 3: Custom panic handler
```

---

### Day 19: Power Management & Sleep Modes
**Concepts:**
- Active mode, Modem sleep, Light sleep, Deep sleep
- Wake sources: Timer, GPIO, Touchpad, ULP
- RTC memory persistence
- Power consumption measurements
- `esp_sleep_enable_timer_wakeup()`

**Hands-On:**
```cpp
// Exercise 1: Deep sleep wake on timer
// Exercise 2: Wake on button press (ext0/ext1)
// Exercise 3: Battery-powered sensor (sleep between readings)
// Exercise 4: RTC memory usage across deep sleep
```

---

### Day 20: Interrupt Handling Deep Dive
**Concepts:**
- IRAM_ATTR requirement
- ISR stack limitations (no logging, no delays)
- Deferred interrupt processing
- Critical sections: `portENTER_CRITICAL()`, `portEXIT_CRITICAL()`
- Interrupt priority levels

**C Concepts Introduced:**
- **Critical sections** - Disable interrupts temporarily
- **Atomic operations** - Single-instruction read-modify-write
- **Memory barriers** - Compiler optimization constraints
- **Portability macros** - portENTER_CRITICAL vs direct asm

**Exercise 1: High-Frequency Pulse Counter (YOUR CODE)**
**Challenge:** Count pulses in ISR, report rate in task
- ISR increments counter on every pulse
- Task reads counter every second and calculates frequency
- Must be thread-safe (ISR and task access same variable)

**DESIGN PATTERN: Critical Section Protection**

**Problem it solves:**
- ISR modifies variable while task reads it
- Read is NOT atomic (counter > 8 bits needs multiple CPU instructions)
- Race condition possible
- Need to briefly disable interrupts

**Pattern structure:**
```cpp
volatile uint32_t pulse_count = 0;

// ISR
void IRAM_ATTR pulse_isr(void *arg) {
    pulse_count++;  // Simple increment is OK in ISR
}

// Task
void monitor_task(void *pvParameter) {
    uint32_t last_count = 0;
    while(1) {
        // Critical section - interrupts disabled
        portENTER_CRITICAL(&mux);
        uint32_t current = pulse_count;
        pulse_count = 0;  // Reset
        portEXIT_CRITICAL(&mux);
        
        uint32_t frequency = current;  // Pulses in last second
        ESP_LOGI(TAG, "Frequency: %lu Hz", frequency);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
```

**Requirements:**
- [ ] GPIO interrupt on rising edge
- [ ] ISR increments volatile counter
- [ ] Task reads counter in critical section
- [ ] Display pulse frequency

**Hints:**
- Declare counter as `volatile uint32_t`
- Use static `portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;`
- Wrap multi-step operations with portENTER/EXIT_CRITICAL

**C Concepts - Why Critical Sections:**
```cpp
// Reading 32-bit variable is NOT atomic on many CPUs
uint32_t value;

// Might compile to:
// LOAD low 16 bits
// <INTERRUPT HERE - value changes!>
// LOAD high 16 bits
// Result: Corrupted value!

// Solution: Disable interrupts during read
portENTER_CRITICAL(&mux);
uint32_t safe_value = value;  // Atomic now
portEXIT_CRITICAL(&mux);

// Why volatile?
volatile uint32_t counter;
// Tells compiler: "This can change outside your control"
// Prevents optimization of reads
```

**Critical Thinking:**
- Why is counter++ safe in ISR but reading requires critical section?
- When is volatile enough vs needing critical section?
- What's the performance cost of critical sections?
- Could you use atomic operations instead?

**Exercise 2: ISR → Queue → Processing Pattern (Reinforcement)**
**Challenge:** High-speed data capture with minimal ISR time
- ISR captures timestamp and value, queues event
- Processing task dequeues and does complex calculation
- Measure ISR execution time

**Pattern: Two-Stage Processing**
ISR Deferral pattern at its finest!

**Why this works:**
- ISR: <5 microseconds (just queue)
- Task: Can take milliseconds
- System remains responsive
- No interrupt blocking

**Requirements:**
- [ ] ISR records data to queue
- [ ] Task processes queued data
- [ ] Measure ISR latency (entry to exit)
- [ ] Log if queue becomes full

**Real-World Usage:**
- High-speed ADC sampling
- Encoder position tracking
- Communication protocols
- Precision timing applications

**Exercise 3: Measure ISR Latency (YOUR CODE)**
**Challenge:** Quantify interrupt response time
- GPIO goes high
- Measure time until ISR executes
- Calculate: Interrupt latency
- Log statistics (min, max, average)

**C Concepts - Timing:**
```cpp
void IRAM_ATTR timing_isr(void *arg) {
    uint64_t entry_time = esp_timer_get_time();  // Microseconds
    
    // Your ISR work here
    
    uint64_t exit_time = esp_timer_get_time();
    uint32_t duration = (uint32_t)(exit_time - entry_time);
    
    // Queue duration for task analysis
    xQueueSendFromISR(timing_queue, &duration, NULL);
}
```

**Key Takeaways:**
- **Critical sections** for atomic multi-step operations
- **ISR Deferral** keeps interrupts responsive
- volatile for ISR-modified variables
- IRAM_ATTR mandatory for ISR functions
- Measure and optimize ISR execution time
- Professional embedded systems minimize ISR work

---

### Day 21: Practice Project - Power-Optimized Sensor Logger
**Project Requirements:**
- Read sensor every 15 minutes
- Deep sleep between readings
- Store readings in RTC memory (last 10 readings)
- Wake on button to display all readings via serial
- Run on battery for days/weeks
- LED blink pattern shows battery level on wake

**Optimization Goals:**
- <1mA average current consumption
- Wake time <2 seconds
- No data loss on crashes

---

## WEEK 4: Connectivity & Real-World Applications

### Day 22: WiFi Station & AP Mode
**Concepts:**
- WiFi event handling (`WIFI_EVENT_STA_CONNECTED`)
- WPA2 authentication
- AP mode (ESP32 as access point)
- IP assignment (DHCP vs static)
- `esp_wifi_init()`, `esp_wifi_start()`

**Hands-On:**
```cpp
// Exercise 1: Connect to WiFi with credentials
// Exercise 2: WiFi event-driven state machine
// Exercise 3: Create WiFi AP with password
// Exercise 4: WiFi scan and strongest signal selection
```

---

### Day 23: HTTP Client/Server
**Concepts:**
- `esp_http_client` for requests
- `esp_http_server` for web server
- URI handlers
- GET/POST methods
- JSON parsing (cJSON library)

**Hands-On:**
```cpp
// Exercise 1: HTTP GET request to API
// Exercise 2: Web server serving HTML page
// Exercise 3: REST API (GET sensor data, POST settings)
// Exercise 4: OTA updates via HTTP
```

---

### Day 24: MQTT Protocol
**Concepts:**
- Publisher/Subscriber model
- Topics and QoS levels (0, 1, 2)
- Retained messages
- Last Will and Testament (LWT)
- `esp_mqtt_client`

**Hands-On:**
```cpp
// Exercise 1: Publish sensor data to broker
// Exercise 2: Subscribe to command topic
// Exercise 3: MQTT + JSON payload
// Exercise 4: Home Assistant integration
```

---

### Day 25: Bluetooth Classic
**Concepts:**
- SPP (Serial Port Profile)
- Pairing and bonding
- Bluetooth stack initialization
- Discovery and connection

**Hands-On:**
```cpp
// Exercise 1: Bluetooth serial terminal
// Exercise 2: Wireless sensor data over BT
// Exercise 3: Bluetooth audio (A2DP basics)
```

---

### Day 26: BLE (Bluetooth Low Energy)
**Concepts:**
- GATT services and characteristics
- Advertising and scanning
- Central vs Peripheral roles
- Notifications and indications
- Power efficiency

**Hands-On:**
```cpp
// Exercise 1: BLE beacon advertiser
// Exercise 2: Custom GATT service (sensor readings)
// Exercise 3: BLE scanner (find nearby devices)
// Exercise 4: Phone app communication (nRF Connect)
```

---

### Day 27-28: Final Capstone Project (Choose One)

#### Option A: Smart Home Sensor Hub
- 5+ sensors (temp, humidity, motion, light, door)
- MQTT to Home Assistant
- Web interface for configuration
- Deep sleep when inactive
- Battery + solar powered
- OTA updates

#### Option B: Wireless Data Logger
- Multi-channel ADC sampling (1kHz)
- Store to SD card (CSV format)
- BLE for configuration
- Real-time streaming to PC
- Trigger modes (threshold, edge)
- Web dashboard

#### Option C: RC Car/Robot Controller
- WiFi control from phone
- Motor control (PWM)
- Ultrasonic obstacle avoidance
- Camera streaming (ESP32-CAM)
- FreeRTOS tasks: Control, Sensors, Camera, WiFi
- WebSocket for low-latency commands

#### Option D: Custom Project
Design your own combining:
- At least 3 peripherals
- WiFi or BLE
- Multiple FreeRTOS tasks
- Proper error handling
- Power management

---

## 📖 Learning Resources

### Official Documentation
- [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/)
- [FreeRTOS.org](https://www.freertos.org/Documentation/RTOS_book.html)
- [ESP32 Technical Reference](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)

### Recommended Books
- "Mastering ESP32" by Luca Dentella
- "The FreeRTOS Reference Manual" (free PDF)
- "ESP32 Cookbook" by Marco Schwartz

### Video Tutorials
- Espressif YouTube channel
- Andreas Spiess (The guy with the Swiss accent)
- DroneBot Workshop

### Code Examples
- ESP-IDF examples folder: `$IDF_PATH/examples/`
- This boilerplate: Start from `src/main.cpp`

---

## 🎯 Success Metrics

### Week 1
✅ Can create and manage multiple tasks  
✅ Understand task priorities and scheduling  
✅ Use queues, semaphores, mutexes correctly  
✅ Debug task synchronization issues

### Week 2
✅ Configure any GPIO peripheral  
✅ Interface with I2C and SPI devices  
✅ Read ADC and generate DAC output  
✅ Handle UART communication

### Week 3
✅ Optimize power consumption  
✅ Handle errors gracefully  
✅ Understand memory management  
✅ Write ISR-safe code

### Week 4
✅ Connect ESP32 to internet  
✅ Build web server or API client  
✅ Implement MQTT or BLE  
✅ Complete full IoT project

---

## 🔧 Development Setup Checklist

- [x] PlatformIO installed
- [x] ESP32 board available
- [ ] Breadboard and jumper wires
- [ ] LEDs, resistors, buttons
- [ ] I2C sensor (BME280 recommended)
- [ ] Logic analyzer (optional but helpful)
- [ ] Multimeter for debugging

---

## 📝 Daily Learning Log

Use this section to track your progress:

### Week 1 Log
**Day 1:** _______________  
Notes:

**Day 2:** _______________  
Notes:

(Continue for each day...)

---

## 🚀 Next Steps After Completion

1. **ESP32 Advanced Topics:**
   - ULP coprocessor programming
   - Touch sensor APIs
   - ESP-NOW protocol
   - Ethernet connectivity

2. **Professional Development:**
   - RTOS design patterns
   - Unit testing (Unity framework)
   - CI/CD for embedded
   - Production deployment

3. **Hardware Expansion:**
   - ESP32-S3 (AI acceleration)
   - ESP32-C3 (RISC-V)
   - ESP32-CAM
   - Custom PCB design

---

**Ready to start? Begin with Week 1, Day 1! 🎓**

**Questions? Create issues in this project or ask as we go along.**

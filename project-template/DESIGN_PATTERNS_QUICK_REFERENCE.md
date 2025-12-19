# Embedded Design Patterns - Quick Reference

## 🎯 Patterns Taught in This Tutorial

This guide provides a quick reference for all design patterns explicitly taught throughout the ESP32 + FreeRTOS tutorial.

---

## 1. Producer-Consumer Pattern

**Taught:** Day 4 (Queues)

**Problem:** Decouple data generation from data processing when they operate at different rates.

**Solution:** Queue acts as thread-safe buffer between producer and consumer tasks.

**Structure:**
```cpp
QueueHandle_t data_queue;

void producer_task(void *param) {
    while(1) {
        int data = read_sensor();
        xQueueSend(data_queue, &data, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void consumer_task(void *param) {
    int received;
    while(1) {
        if(xQueueReceive(data_queue, &received, portMAX_DELAY)) {
            process_data(received);
        }
    }
}
```

**When to Use:**
- Sensor reading → Data processing
- UART RX → Command parsing
- Button events → Action handling
- Any asynchronous data flow

**Key Points:**
- Queue provides buffering
- Producer doesn't wait for consumer
- Consumer doesn't miss data
- Queue size determines burst capacity

---

## 2. ISR Deferral / Interrupt Handler Pattern

**Taught:** Days 5, 8, 20

**Problem:** ISRs must be extremely fast, but processing requires time.

**Solution:** Minimal work in ISR, signal task to do heavy processing.

**Structure:**
```cpp
SemaphoreHandle_t isr_semaphore;

void IRAM_ATTR button_isr(void *arg) {
    xSemaphoreGiveFromISR(isr_semaphore, NULL);
}

void processing_task(void *param) {
    while(1) {
        if(xSemaphoreTake(isr_semaphore, portMAX_DELAY)) {
            // Heavy processing here
            do_complex_work();
        }
    }
}
```

**When to Use:**
- GPIO interrupts
- Timer callbacks
- Communication interrupts
- Any ISR that needs processing

**Key Points:**
- ISR does minimal work (<5μs)
- No logging, delays, or complex logic in ISR
- IRAM_ATTR required
- Use FromISR versions of FreeRTOS functions

---

## 3. Guard / Mutex Protection Pattern

**Taught:** Day 5

**Problem:** Multiple tasks accessing shared resource causes race conditions.

**Solution:** Mutex ensures mutual exclusion - only one task at a time.

**Structure:**
```cpp
SemaphoreHandle_t resource_mutex;
int shared_counter = 0;

void task1(void *param) {
    while(1) {
        xSemaphoreTake(resource_mutex, portMAX_DELAY);
        shared_counter++;  // Protected
        xSemaphoreGive(resource_mutex);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
```

**When to Use:**
- Shared UART/SPI/I2C access
- Global data structures
- Hardware register sequences
- Non-reentrant functions

**Key Points:**
- Always pair Take/Give
- Keep critical section short
- Watch for deadlocks
- Priority inheritance prevents priority inversion

---

## 4. Resource Pool Pattern

**Taught:** Day 5

**Problem:** Limited number of resources (UART ports, buffers, connections).

**Solution:** Counting semaphore manages available resource count.

**Structure:**
```cpp
SemaphoreHandle_t uart_pool;  // Count = 3 for 3 UART ports

void communication_task(void *param) {
    while(1) {
        if(xSemaphoreTake(uart_pool, pdMS_TO_TICKS(1000))) {
            // Got a UART port, use it
            uart_transmit(data);
            xSemaphoreGive(uart_pool);  // Release back to pool
        } else {
            ESP_LOGW(TAG, "No UART available");
        }
    }
}
```

**When to Use:**
- Limited hardware peripherals
- Fixed-size buffer pools
- Connection limits
- License/token management

**Key Points:**
- Initial count = number of resources
- Take = acquire resource
- Give = release resource
- Prevents over-allocation

---

## 5. Observer / Event-Driven Pattern

**Taught:** Day 15

**Problem:** Multiple tasks need to coordinate on system events without polling.

**Solution:** Event groups allow waiting for multiple conditions efficiently.

**Structure:**
```cpp
EventGroupHandle_t system_events;
#define WIFI_READY_BIT  (1 << 0)
#define TIME_READY_BIT  (1 << 1)

void wifi_task(void *param) {
    setup_wifi();
    xEventGroupSetBits(system_events, WIFI_READY_BIT);
}

void main_task(void *param) {
    xEventGroupWaitBits(system_events, 
                        WIFI_READY_BIT | TIME_READY_BIT,
                        pdFALSE, pdTRUE, portMAX_DELAY);
    // Both conditions met, proceed
    start_application();
}
```

**When to Use:**
- System initialization sequences
- Multi-condition synchronization
- State transitions
- Power management events

**Key Points:**
- 24 bits per event group
- Wait for ANY or ALL bits
- Power efficient (no polling)
- Multiple tasks can wait on same events

---

## 6. State Machine Pattern

**Taught:** Day 15

**Problem:** Complex system behavior with multiple states and transitions.

**Solution:** Explicit state tracking with enum and transition logic.

**Structure:**
```cpp
typedef enum {
    STATE_INIT,
    STATE_CONNECTING,
    STATE_READY,
    STATE_RUNNING,
    STATE_ERROR
} system_state_t;

static volatile system_state_t current_state = STATE_INIT;

void state_machine_task(void *param) {
    while(1) {
        switch(current_state) {
            case STATE_INIT:
                do_init();
                current_state = STATE_CONNECTING;
                break;
            case STATE_CONNECTING:
                if(connect_attempt()) {
                    current_state = STATE_READY;
                }
                break;
            // ... more states
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
```

**When to Use:**
- Protocol implementations (TCP, USB, BLE)
- UI state management
- Power mode transitions
- Complex initialization sequences

**Key Points:**
- Use enum for type safety
- Explicit transition conditions
- Easy to visualize and debug
- Can combine with event groups

---

## 7. Double Buffering Pattern

**Taught:** Day 12

**Problem:** Display/DMA reads while CPU writes causes tearing or corruption.

**Solution:** Two buffers - one being read, one being written. Swap when complete.

**Structure:**
```cpp
uint8_t buffer1[BUFFER_SIZE];
uint8_t buffer2[BUFFER_SIZE];
uint8_t *front_buffer = buffer1;
uint8_t *back_buffer = buffer2;

void drawing_task(void *param) {
    while(1) {
        draw_frame(back_buffer);  // Draw to back
        
        // Swap pointers (atomic)
        uint8_t *temp = front_buffer;
        front_buffer = back_buffer;
        back_buffer = temp;
        
        send_to_display(front_buffer);  // Send front to display
    }
}
```

**When to Use:**
- LCD/OLED displays
- Audio DAC streaming
- Video processing
- High-speed data acquisition

**Key Points:**
- Swap pointers, not data (fast!)
- Prevents tearing
- Synchronization needed between swap and use
- Can extend to triple buffering

---

## 8. Critical Section Pattern

**Taught:** Day 20

**Problem:** Multi-step operation on shared data needs atomicity.

**Solution:** Disable interrupts briefly for atomic access.

**Structure:**
```cpp
static portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
volatile uint32_t shared_counter = 0;

void task1(void *param) {
    while(1) {
        portENTER_CRITICAL(&mux);
        uint32_t value = shared_counter;
        shared_counter = value + 1;
        portEXIT_CRITICAL(&mux);
    }
}
```

**When to Use:**
- ISR + Task share variable
- Multi-step read-modify-write
- Hardware register sequences
- When mutex is too heavyweight

**Key Points:**
- Disables interrupts (use sparingly!)
- Keep section VERY short
- Different from mutex (affects all interrupts)
- Use for microsecond-scale protection

---

## 9. Singleton Pattern

**Taught:** Throughout (implicitly)

**Problem:** Hardware peripherals are single-instance, need controlled access.

**Solution:** Static variables and initialization guards.

**Structure:**
```cpp
static bool spi_initialized = false;
static SemaphoreHandle_t spi_mutex = NULL;

void init_spi_singleton(void) {
    if(!spi_initialized) {
        spi_mutex = xSemaphoreCreateMutex();
        // SPI hardware init
        spi_initialized = true;
    }
}

void use_spi(void) {
    xSemaphoreTake(spi_mutex, portMAX_DELAY);
    // Use SPI
    xSemaphoreGive(spi_mutex);
}
```

**When to Use:**
- Hardware drivers (SPI, I2C, UART)
- System-wide configuration
- Logging systems
- Resource managers

**Key Points:**
- One instance for hardware
- Static variables for state
- Initialization guard
- Often combined with mutex

---

## Pattern Combinations

Real systems combine patterns:

**Sensor System:**
- Producer-Consumer (sensor → processor)
- ISR Deferral (GPIO → Queue → Task)
- Mutex (shared SPI bus)
- Observer (wait for init complete)

**Display Application:**
- Double Buffering (smooth rendering)
- Producer-Consumer (draw → display)
- State Machine (UI states)
- Critical Section (frame counter)

**IoT Device:**
- State Machine (connection states)
- Observer (WiFi + time ready)
- Producer-Consumer (data → cloud)
- Resource Pool (connection slots)

---

## Pattern Selection Guide

| Need | Pattern |
|------|---------|
| Async data flow | Producer-Consumer |
| Fast ISR | ISR Deferral |
| Shared resource | Guard/Mutex |
| Limited resources | Resource Pool |
| Multiple conditions | Observer/Event |
| Complex states | State Machine |
| Display/DMA | Double Buffering |
| Atomic access | Critical Section |
| Hardware driver | Singleton |

---

## Learning Path

1. **Day 4:** Start with Producer-Consumer (fundamental)
2. **Day 5:** Add ISR Deferral and Guard (safety)
3. **Day 8:** Practice ISR Deferral with GPIO
4. **Day 12:** Learn Double Buffering (performance)
5. **Day 15:** Master Observer and State Machine (coordination)
6. **Day 20:** Understand Critical Sections (advanced)

Each pattern builds on previous knowledge. By end of tutorial, you'll recognize these patterns in any embedded codebase!

---

## 🎓 Professional Impact

Understanding these patterns makes you:
- ✅ Recognize professional embedded code
- ✅ Design robust real-time systems
- ✅ Debug complex multi-task issues
- ✅ Write maintainable embedded software
- ✅ Interview confidently for embedded roles
- ✅ Contribute to open-source embedded projects

These are the **same patterns** used in:
- Industrial automation
- Automotive systems
- Medical devices
- IoT platforms
- Consumer electronics
- Aerospace/defense

**Master these patterns = Think like a professional embedded engineer!**

#include <bluefruit.h>

volatile bool counter = true;

extern "C" {
  void TIMER2_IRQHandler_v(){
    uint32_t * tim2_CC0_event_addr = (uint32_t*)0x4000A140;
    if(*tim2_CC0_event_addr == 1){
      *tim2_CC0_event_addr = 0;
      counter = !counter;
    }
  }
}

void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  // Configure TIMER4, base address 0x4000A000
  // Set the BITMODE register 0x4000A508
  uint32_t * tim4_BITMODE_addr = (uint32_t*)0x4000A508;
  *tim4_BITMODE_addr = 0x00000000;
  uint32_t * tim4_Prescaler_addr = (uint32_t*)0x4000A510;
  *tim4_Prescaler_addr = 9;   // set timer frequency to 16 MHz / 2^9 = 31250 Hz
  uint32_t * tim4_CC0_addr = (uint32_t*)0x4000A540;
  *tim4_CC0_addr = 31250;  // set the compare value, so Compare 0 occurs once very 1 second
  uint32_t * tim4_SHORTS_addr = (uint32_t*)0x4000A200;
  //*tim4_SHORTS_addr = *tim4_SHORTS_addr | 0x00000001;
  *tim4_SHORTS_addr = 0x00000001;  // Enable shortcut between Compare 0 event and Clear task
  uint32_t * tim4_INTENSET_addr = (uint32_t*)0x4000A304;
  *tim4_INTENSET_addr = 1 << 16;  // Enable CC0 interrupt
  NVIC_EnableIRQ(TIMER4_IRQn);  // Enable interrupt in the NVIC interrupt controller
  uint32_t * tim4_START_addr = (uint32_t*)0x4000A000;
  *tim4_START_addr = 1;  // Start the timer
}
void loop() {
  digitalWrite(LED_BUILTIN, counter);
}

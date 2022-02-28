volatile int counter = 0;
extern "C" {
  void TIMER4_IRQHandler_v(){
    uint32_t * tim4_CC0_event_addr = (uint32_t*)0x4001B140;
    if(*tim4_CC0_event_addr == 1){
      *tim4_CC0_event_addr = 0;
      counter = !counter;
    }
  }
}

void setup() {
  pinMode(13,OUTPUT);
  //Serial.begin(115200);
  // Configure TIMER4, base address 0x4001B000
  // Set the BITMODE register 0x4001B508
  uint32_t * tim4_BITMODE_addr = (uint32_t*)0x4001B508;
  *tim4_BITMODE_addr = 0x00000000;
  uint32_t * tim4_Prescaler_addr = (uint32_t*)0x4001B510;
  *tim4_Prescaler_addr = 9;   // set timer frequency to 16 MHz / 2^9 = 31250 Hz
  uint32_t * tim4_CC0_addr = (uint32_t*)0x4001B540;
  *tim4_CC0_addr = 31250;  // set the compare value, so Compare 0 occurs once very 1 second
  uint32_t * tim4_SHORTS_addr = (uint32_t*)0x4001B200;
  //*tim4_SHORTS_addr = *tim4_SHORTS_addr | 0x00000001;
  *tim4_SHORTS_addr = 0x00000001;  // Enable shortcut between Compare 0 event and Clear task
  uint32_t * tim4_INTENSET_addr = (uint32_t*)0x4001B304;
  *tim4_INTENSET_addr = 1 << 16;  // Enable CC0 interrupt
  NVIC_EnableIRQ(TIMER4_IRQn);  // Enable interrupt in the NVIC interrupt controller
  uint32_t * tim4_START_addr = (uint32_t*)0x4001B000;
  *tim4_START_addr = 1;  // Start the timer
}

void loop() {
  //Serial.println(counter);
  digitalWrite(13, counter);
}
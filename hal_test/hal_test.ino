#include <bluefruit.h>
#include <nrf.h>
#include <nrf_gpio.h>
#include <nrf_gpiote.h>
#include <hal/nrf_power.h>
const uint32_t P1_pin = 11;
//C:\Users\josia\AppData\Local\Arduino15\packages\adafruit\hardware\nrf52\1.3.0\cores\nRF5\nordic\nrfx\mdk
// https://studio.edgeimpulse.com/studio/83393
void setup() {
    // put your setup code here, to run once:
  for(uint8_t i=0; i<5; i++){
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
  }
  
  digitalWrite(25, LOW); // turn off power lead to save power
  // Start Preparing for the wake-up mechanism
  // Disable port interrupt
  //NRF_GPIOTE->INTENCLR |= ((uint32_t) GPIOTE_INTENCLR_PORT_Clear << GPIOTE_INTENCLR_PORT_Pos);
  nrf_gpiote_int_disable(NRF_GPIOTE, NRF_GPIOTE_INT_PORT_MASK);

  NRF_P1->DETECTMODE = 0; // default detect mode
  // NRF_P1->LATCH &= ~((uint32_t)GPIO_LATCH_PIN11_Msk); // Clear latch status of PIN11
  nrf_gpio_pin_latch_clear(P1_pin);
  
  // Configure the wake-up pin
  // set direction to input mode
  // NRF_P1->PIN_CNF[P1_pin] &= ~((uint32_t) GPIO_PIN_CNF_DIR_Msk);
  // NRF_P1->PIN_CNF[P1_pin] |= ((uint32_t) GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos); NRF_GPIO_PIN_DIR_INPUT?
  nrf_gpio_port_dir_input_set(NRF_GPIO, P1_pin);
  
  // Connect input buffer
  //NRF_P1->PIN_CNF[P1_pin] &= ~((uint32_t) GPIO_PIN_CNF_INPUT_Msk);
  //NRF_P1->PIN_CNF[P1_pin] |= ((uint32_t) GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos);
  nrf_gpio_cfg_watcher(P1_pin);

  // Set pulldown 
  // NRF_P1->PIN_CNF[P1_pin] &= ~((uint32_t) GPIO_PIN_CNF_PULL_Msk);
  // NRF_P1->PIN_CNF[P1_pin] |= ((uint32_t) GPIO_PIN_CNF_PULL_Pulldown << GPIO_PIN_CNF_PULL_Pos);  
  nrf_gpio_cfg_input(P1_pin, NRF_GPIO_PIN_PULLDOWN );
  
  // Generate Sense signal when pin is HIGH
  //NRF_P1->PIN_CNF[P1_pin] &= ~((uint32_t) GPIO_PIN_CNF_SENSE_Msk);
  //NRF_P1->PIN_CNF[P1_pin] |= ((uint32_t) GPIO_PIN_CNF_SENSE_High << GPIO_PIN_CNF_SENSE_Pos);
  nrf_gpio_cfg_sense_input(P1_pin, NRF_GPIO_PIN_PULLDOWN, NRF_GPIO_PIN_SENSE_HIGH);
  
  // Clear any port event that might have occurred during the configuration
  //NRF_GPIOTE->EVENTS_PORT = 0;
  nrf_gpiote_event_clear(NRF_GPIOTE, NRF_GPIOTE_EVENT_PORT);

  // Enable port interrupt
  //NRF_GPIOTE->INTENSET |= ((uint32_t)GPIOTE_INTENSET_PORT_Set << GPIOTE_INTENSET_PORT_Pos);
  nrf_gpiote_int_enable(NRF_GPIOTE, NRF_GPIOTE_INT_PORT_MASK);
  // End preparing for the wake-up mechanism
  
  // Now put device into System Off mode
  // NRF_POWER->SYSTEMOFF = 1;
  nrf_power_system_off(NRF_POWER);
  // never reach here
}

void loop() {
  // put your main code here, to run repeatedly:
}

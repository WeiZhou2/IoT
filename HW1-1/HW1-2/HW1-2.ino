#include <Wire.h>
#define BUFLEN 8192
int buf[BUFLEN];
char msg[30];
int val;
unsigned long start_time, duration;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  start_time = micros();
  for(int i=0; i<BUFLEN; i++){
    val = analogRead(A3);
    float volt = val/1023 * 3.3;
    //sprintf(msg, "ADC: %d Volt: %0.2f",  buf[i], volt);
    //Serial.println(msg);
  }
  duration = micros() - start_time;
  Serial.println(duration);
  delay(500);
}

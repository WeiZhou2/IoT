#include <Wire.h>

int first[10];
int second[10];
int answer[10];
int input[10];
int answerCount;
int questionCount;
int firstTime;
int question = 10;

void setup(){
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB
  }
  answerCount = 0;
  questionCount = 0;
  firstTime = 0;
}

void loop(){
  if(firstTime == 0){
    for(int x = 0; x < question; x++){
      first[x] = random(0, 10);
      second[x] = random(0, 10);
      answer[x] = first[x] + second[x]; 
    }
    firstTime++;
  }
  
  if( questionCount < question && questionCount == answerCount  ){
    Serial.print(String(first[questionCount]));
    Serial.print(" + ");
    Serial.println(String(second[questionCount]));
    questionCount++;
  }
  
  if(Serial.available() > 0){
    if (questionCount!=0){
      int val = Serial.parseInt();
      byte enter = Serial.read();
      if(enter == 10){
         while (!Serial) {
            ; 
        }
        Serial.print("Your Answer: ");
        Serial.println(String(val));
        input[answerCount]=val;
        answerCount++;

        if (answerCount >= question){
          for(int x = 0; x < question; x++){
            Serial.print("You Enter: ");
            Serial.print(String(input[x]));
            Serial.print(" for Question ");
            Serial.print(String(x + 1));            
            if (input[x] == answer[x]){
              Serial.println(", the answer is correct");              
            } else {
              Serial.print(", the answer is incorrect, the correct answer is "); 
              Serial.print(String(answer[x]));
              Serial.println("."); 
            }
          }
        }
      }
    }
  }    
}

#include <Arduino.h>

#define LED 13
#define light_time_period 100
#define idle_time_period 1000
#define ON_state "1"
#define OFF_state "0"
#define version 1

#define time_quantum 100 //quantum of time (in milliseconds). Used in Binking pattern matrix

/* 
* Binking pattern matrix
* 
* Matrix is set of blinking pattern arrays
*
* Each of them is array of booleans 
*  - 1 (or other any nonzero value) turns LED ON for quantum of time
*  - 0 turns LED OFF for quantum of time   
*
* Matrix index is set of blinking pattern arrays labels
*/

String blinkMatrixIndex[] = {
  "Вимкнути",
  "Просте мигання",
  "Довге мигання",
  "Сиuнал SOS"
};

bool blinkMatrix[][500] = {
  {},
  {1,0},
  {1,1,1,0},
  {1,0,1,0,1,0, 1,1,1,0,1,1,1,0,1,1,1,0, 1,0,1,0,1,0}
};

// ---------------------------------
String currentState = "-";

void setup() {

    pinMode(LED,OUTPUT);
    
    Serial.begin(9600);
    Serial.print("Привіт...\n");
    Serial.print("Починаємо працювати...\n-------------------\n");
    
    Serial.println(".... МЕНЮ ....");

    Serial.print("sizeof(blinkMatrixIndex) = "); Serial.println(sizeof(blinkMatrixIndex));
    Serial.println(" ");

    for(unsigned int i = 0; i <= sizeof(blinkMatrixIndex); i++){
      Serial.print(i); Serial.print(" - "); Serial.println(blinkMatrixIndex[i]);
    }

    Serial.println(" ");
    Serial.print("Сurrent state is "); Serial.println(currentState);
    
}


void blinkLED() {
  if (currentState == ON_state) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(light_time_period);
    digitalWrite(LED_BUILTIN, LOW);
    delay(idle_time_period);
  }
  else if ( currentState == OFF_state) {
    digitalWrite(LED_BUILTIN, LOW);
  }  
}

void loop() {
    String data;
  
    if (Serial.available() > 0){
      data = Serial.readString();
      
      Serial.println(data);
      
      if (data == currentState) {
        Serial.print("Нічого не змінилось. ");
      }
      
      else if (data == ON_state) { 
        Serial.print("Вмикаємо ... "); 
        currentState = ON_state;
      }
      
      else if (data == OFF_state) { 
        Serial.print("Вимикаємо ... "); 
        currentState = OFF_state;
      }

    Serial.print("(current state is "); Serial.print(currentState); Serial.println(")");

    }
    
    blinkLED();

}

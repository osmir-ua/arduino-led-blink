#include <Arduino.h>

#define LED 13
#define light_time_period 100
#define idle_time_period 1000
#define ON_state "1"
#define OFF_state "0"
#define version 1

String currentState = "-";

void setup() {

    pinMode(LED,OUTPUT);
    
    Serial.begin(9600);
    Serial.print("Привіт...\n");
    Serial.print("Починаємо працювати...\n-------------------\n");
    
    Serial.print(".... МЕНЮ .... \n1 - вмк.\n2 - вимк.\n\n");
    
    Serial.print("current state is "); Serial.println(currentState);
    
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
        Serial.print("Нічного не змінилось. ");
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

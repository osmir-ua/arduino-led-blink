#include <Arduino.h>

#define LED 13

#define light_time_period 100
#define idle_time_period 1000
#define ON_state "1"
#define OFF_state "0"

#define version 2

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
  {0},
  {1,0},
  {1,1,1,0},
  {1,0,1,0,1,0, 1,1,1,0,1,1,1,0,1,1,1,0, 1,0,1,0,1,0}
};

// ---------------------------------
String currentState = "-";

unsigned int arrayIndex;
unsigned int arrayPosIndex;
unsigned int patternID;

unsigned long lastTime = millis();


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


void processBlink(unsigned int patternId){

  unsigned long currentTime = millis();
  
  if(!patternId || (currentTime - lastTime) < time_quantum ) return;

  if (!arrayIndex || patternId != arrayIndex) {
    arrayIndex = patternId;
    
    if (!blinkMatrixIndex[arrayIndex]) return;
    
    arrayPosIndex = 0;
  }

  if (blinkMatrixIndex[arrayIndex][arrayPosIndex]){
    
    if (blinkMatrixIndex[arrayIndex][arrayPosIndex] == 0) digitalWrite(LED_BUILTIN, LOW);
    else digitalWrite(LED_BUILTIN, HIGH);

    lastTime = currentTime;    
    arrayPosIndex++;

    if (!blinkMatrixIndex[arrayIndex][arrayPosIndex]) arrayPosIndex = 0;
  }
}

nvl()

void loop() {
    int data;
  
    if (Serial.available() > 0){
      data = Serial.read();
      
      Serial.println(data);
      
      if (data == currentState) {
        Serial.print("Нічого не змінилось. ");
      }
      else{

      }

      Serial.print("(current state is "); Serial.print(currentState); Serial.println(")");

    }


    processBlink(arrayIndex);

}

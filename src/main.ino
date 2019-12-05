#include <Arduino.h>

#define LED 13

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
  "Сигнал SOS"
};

bool blinkMatrix[][500] = {
  {0},
  {1,0},
  {1,1,1,0},
  {1,0,1,0,1,0, 1,1,1,0,1,1,1,0,1,1,1,0, 1,0,1,0,1,0}
};

// ---------------------------------
unsigned int currentState;

unsigned int arrayIndex;
unsigned int arrayPosIndex;

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

    Serial.println();
    Serial.print("Сurrent state is "); Serial.write(currentState); Serial.println();

    
}


void processBlink(unsigned int patternId){

  unsigned long currentTime = millis();
  
  // if patternId is null of time interval doesn't pass -- do nothing
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

// nvl()

void loop() {
    String data;
    unsigned int patternID;
    
    if (Serial.available() > 0){
      data = Serial.readString();
      
      if (isdigit(data.charAt(0))) {
        patternID = (unsigned int)data.toInt();
      }

      // status message
      Serial.print("Entered : "); 
        Serial.print(data);  
        Serial.print(" ("); 
        Serial.write(patternID);
        Serial.println(")");
      

      if (patternID == currentState) {
        Serial.print("Нічого не змінилось. ");
      }
      else{
        currentState = patternID;
      }

      Serial.print("(current state is "); Serial.write(currentState); Serial.println(")");

    }

    processBlink(patternID);

}

#include <Arduino.h>

#define LED 13

#define time_quantum 1000 // 10 sec. Quantum of time (in milliseconds). Used in Binking pattern matrix
#define patternMaxrix1stLevelSize 4
#define patternMaxrix2dnLevelSize 30

/*
* Matrix index is set of blinking pattern array labels
*/
String blinkMatrixIndex[patternMaxrix1stLevelSize] = {
  "Вимкнути",
  "Просте мигання",
  "Довге мигання",
  "Сигнал SOS"
};

/* 
* Binking pattern matrix
* 
* Matrix is set of strings (blinking pattern arrays). 
* Each character in string is 1 or 0  
*  - 1 (or other any nonzero value) turns LED ON for quantum of time
*  - 0 turns LED OFF for quantum of time   
*
*/
String blinkMatrix[patternMaxrix1stLevelSize] = {
  "0",
  "10",
  "1110",
  "101010111011101110101010"
};

// ---------------------------------
unsigned int currentState;

unsigned int arrayIndex;
unsigned int arrayPosIndex;

unsigned long lastTime = millis();


void echoMatrix(){
    Serial.println("========================");

    for ( unsigned int a = 0; a < patternMaxrix1stLevelSize; a++ ) {
      Serial.print("Line : "); Serial.print(a);
      Serial.print(" Label : "); Serial.print(blinkMatrixIndex[a]);
      Serial.print(" Size : "); Serial.print(blinkMatrix[a].length());
      Serial.print(" Content : "); Serial.print(blinkMatrix[a]); 
      Serial.println();

      // loop through columns of current row
      for ( unsigned int j = 0; j < blinkMatrix[a].length(); j++ ) {
        Serial.print(blinkMatrix[a].charAt(j));       Serial.print(" ");
      }
      Serial.println(); // start new line of output
    } 

    Serial.println("========================"); Serial.println();
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void setup() {

    pinMode(LED,OUTPUT);
    
    Serial.begin(9600);
    while (!Serial);
    
    Serial.print("Починаємо працювати...\n-------------------\n");

    // echoMatrix();

    Serial.println(".... МЕНЮ ....");

    for(unsigned int i = 0; i < patternMaxrix1stLevelSize; i++){
      Serial.print(i); Serial.print(" - "); Serial.println(blinkMatrixIndex[i]);
    }

    Serial.println();
    Serial.print("Сurrent state is "); Serial.write(currentState); Serial.println();
   
}


void processBlink(unsigned int patternId){

  unsigned long currentTime = millis();
  
  //debugging message
  //Serial.println();
  //Serial.print("patternId = "); Serial.println(patternId); 
  //Serial.print("currentTime = "); Serial.println(currentTime); 
  //Serial.print("(currentTime - lastTime) = "); Serial.println(currentTime - lastTime); 

  // if patternId is null of time interval doesn't pass -- do nothing
  if(!patternId || (currentTime - lastTime) < time_quantum ) return;

  if (!arrayIndex || patternId != arrayIndex) {
    arrayIndex = patternId;
    
    if (!blinkMatrixIndex[arrayIndex]) return;
    
    arrayPosIndex = 0;
  }

  //debugging message
  //Serial.print("arrayIndex = "); Serial.println(arrayIndex); 
  //Serial.print("arrayPosIndex = "); Serial.println(arrayPosIndex); 
  //Serial.print("blinkMatrixIndex[arrayIndex] = "); Serial.println(blinkMatrixIndex[arrayIndex]); 

  //debugging message
  //Serial.print("blinkMatrix[arrayIndex][arrayPosIndex] = "); Serial.println(blinkMatrix[arrayIndex].charAt(arrayPosIndex)); 

  int theBit = blinkMatrix[arrayIndex].charAt(arrayPosIndex)-'0';

  //debugging message
  //Serial.print("theBit = "); Serial.println(theBit); 

  if (theBit == 0) digitalWrite(LED_BUILTIN, LOW);
  else if (theBit == 1) digitalWrite(LED_BUILTIN, HIGH);
  else arrayPosIndex = 0;

  lastTime = currentTime;    
  arrayPosIndex++;

  //debugging message
  //Serial.print("New blinkMatrix[arrayIndex][arrayPosIndex] = "); Serial.println(blinkMatrix[arrayIndex].charAt(arrayPosIndex)); 

  theBit = blinkMatrix[arrayIndex].charAt(arrayPosIndex) - '0';
  if (!(theBit == 0 || theBit == 1)) 
    arrayPosIndex = 0;
}

void loop() {
    String data;
    unsigned int patternID = 0;
    
    if (Serial.available() > 0){
      data = Serial.readString();
      
      if (isdigit(data.charAt(0))) {
        patternID = (unsigned int)data.toInt();
      }

      // status message
      /*Serial.print("Entered : "); 
        Serial.print(data);  
        Serial.print(" ("); 
        Serial.print(patternID);
        Serial.println(")");
      */

      if (patternID == currentState) {
        Serial.print("Нічого не змінилось. ");
      }
      else{
        currentState = patternID;
      }

      Serial.print("(current state is "); Serial.print(currentState); Serial.println(")");

    }

    processBlink(currentState);
   
    delay(time_quantum / 10);

}

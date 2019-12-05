# 1 "C:\\Users\\osmir\\AppData\\Local\\Temp\\tmpc6x687xt"
#include <Arduino.h>
# 1 "C:/Users/osmir/Documents/Arduino/LED-blinking/arduino-led-blink/src/main.ino"
#include <Arduino.h>

#define LED 13






#define time_quantum 100
# 24 "C:/Users/osmir/Documents/Arduino/LED-blinking/arduino-led-blink/src/main.ino"
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


unsigned int currentState;

unsigned int arrayIndex;
unsigned int arrayPosIndex;

unsigned long lastTime = millis();
void setup();
void processBlink(unsigned int patternId);
void loop();
#line 47 "C:/Users/osmir/Documents/Arduino/LED-blinking/arduino-led-blink/src/main.ino"
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



void loop() {
    String data;
    unsigned int patternID;

    if (Serial.available() > 0){
      data = Serial.readString();

      if (isdigit(data.charAt(0))) {
        patternID = (unsigned int)data.toInt();
      }


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
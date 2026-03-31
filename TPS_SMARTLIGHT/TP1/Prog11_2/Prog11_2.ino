// TP1 - PROG11_1

#define LED_D5_PIN D10
#define T_LED_D5 2000

#define LED_BLUE_PIN D9
#define LED_GREEN_PIN D7
#define LED_RED_PIN D6

#define BP1_PIN D2
#define BP2_PIN D3
#define T_BP 30 // 30ms

#define STATE_0 0
#define STATE_1 1
#define STATE_2 2
#define STATE_3 3
#define STATE_4 4
#define STATE_5 5
#define STATE_6 6
#define STATE_7 7
#define STATE_8 8

#define STATE_10 10
#define STATE_11 11
#define STATE_12 12


#define OFF 0
#define GREEN 1
#define YELLOW 2
#define RED 3
#define BLUE 4

unsigned long time, timeEnd;
long previousTime;
int bp1, bp2;

byte currentState, globalState;
  
void setup() {
  pinMode(LED_D5_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(BP1_PIN, INPUT);
  pinMode(BP2_PIN, INPUT);
  previousTime = -T_BP;
  currentState = STATE_0;
  globalState = STATE_10;
  Serial.begin(9600);
}

void loop() {
  time = millis();

  // Acquisition boutons ssi dt >= T_BP
  if(time - previousTime >= T_BP) { 

    bp1 = digitalRead(BP1_PIN);
    bp2 = digitalRead(BP2_PIN);

    if(globalState == STATE_10 && bp2 == 0) globalState = STATE_11;
    else if(globalState == STATE_11 && bp1 == 0 && bp2 == 1) globalState = STATE_12;
    else if(globalState == STATE_12 && bp1 == 1 && bp2 == 1) globalState = STATE_10;

    switch(globalState) {
      case STATE_10 :
        // Led de vie
        blinkLed(LED_D5_PIN, T_LED_D5);
        break;
      case STATE_11 :          
        Serial.println("Arrêt");  
        digitalWrite(LED_D5_PIN, LOW);
        setRGB(RED);
        break;
      case STATE_12 :
        Serial.println("Reprise");  
        currentState = 0;
        setRGB(OFF);
        break;
    }

    if(globalState == STATE_10) {
      prog11();
    }
    
    previousTime = time; 
  } 

}

void blinkLed(byte ledPin, unsigned int tLed) {
  static unsigned int compute;
  compute = time % tLed; // Reste de la division entière
  if(compute < tLed/2) digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin, LOW);
}

void setRGB(int ledColor) {
  static unsigned int ledPin;
  digitalWrite(LED_GREEN_PIN, LOW);  
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_BLUE_PIN, LOW);
  if(ledColor == OFF) return;  
  switch (ledColor) {
    case GREEN:
      ledPin = LED_GREEN_PIN;
      break;
    case YELLOW:
      digitalWrite(LED_RED_PIN, HIGH);
      ledPin = LED_GREEN_PIN;
      break;
    case RED:
      ledPin = LED_RED_PIN;
      break;
    case BLUE:
      ledPin = LED_BLUE_PIN;
      break;
  }
  digitalWrite(ledPin, HIGH);
}

void prog11() {
  if(bp1 == 0 && currentState == STATE_0) currentState = STATE_1;
  else if(currentState == STATE_1) currentState = STATE_2;
  else if(time > timeEnd && currentState == STATE_2) currentState = STATE_3;  
  else if(currentState == STATE_3) currentState = STATE_4;
  else if(time > timeEnd && currentState == STATE_4) currentState = STATE_5;    
  else if(currentState == STATE_5) currentState = STATE_6;
  else if(time > timeEnd && currentState == STATE_6) currentState = STATE_7; 
  else if(currentState == STATE_7) currentState = STATE_8;
  else if(time > timeEnd && currentState == STATE_8) currentState = STATE_0; 
  if(currentState == STATE_0) {
    setRGB(OFF);
  }
  if(currentState == STATE_1) { 
    timeEnd = time + 4000;      
    setRGB(GREEN);
    Serial.println("Préchauffage");
  }
  if(currentState == STATE_3) {
    timeEnd = time + 3000;      
    setRGB(YELLOW);
    Serial.println("Rampe");
  }
  if(currentState == STATE_5) {
    timeEnd = time + 2000;      
    setRGB(RED);
    Serial.println("Refusion");
  }
  if(currentState == STATE_7) {
    timeEnd = time + 3000;      
    setRGB(BLUE);
    Serial.println("Refroidissement");
  }
}

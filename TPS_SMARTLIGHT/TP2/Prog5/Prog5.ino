// TP2 - Prog 5

#define SAMPLE_PERIOD 500 // en ms
#define ANALOG_PIN A9
#define BP1_PIN D2
#define BP2_PIN D3
#define LED_RED_PIN D6
#define LED_GREEN_PIN D7
#define LED_D5_PIN D10

#define STATE_0 0
#define STATE_1 1
#define STATE_2 2
#define STATE_3 3
#define STATE_4 4
#define STATE_5 5
#define STATE_6 6

const byte nbValuesToAcquire = 10;

float analogValue, meanValue, threshold;

unsigned long time, nbValues;
long previousTime;

byte bp1, previousBp1, bp2, previousBp2, state, nbAcquiredValues, nbEvent;

void setup() {
  //analogReference(AR_INTERNAL1V0);
  analogReference(AR_DEFAULT);
  analogReadResolution(10);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(BP1_PIN, INPUT);
  pinMode(BP2_PIN, INPUT);

  pinMode(LED_D5_PIN, OUTPUT);
  digitalWrite(LED_D5_PIN, LOW);

  Serial.begin(115200);
  while(!Serial) delay(10);

  bp1 = 1;
  previousBp1 = 1;

  bp2 = 1;
  previousBp2 = 1;

  nbAcquiredValues = 0;
  analogValue = 0;

  threshold = 0.5;

  previousTime = -SAMPLE_PERIOD;
}

void loop() {
  time = millis();

  if(time - previousTime >= SAMPLE_PERIOD) {

    bp1 = digitalRead(BP1_PIN);    
    bp2 = digitalRead(BP2_PIN);  

    if(bp1 == 0 && previousBp1 == 1 && state == STATE_0) state = STATE_1;
    else if(nbAcquiredValues == nbValuesToAcquire && state == STATE_1) state = STATE_2;
    else if(state == STATE_2 && meanValue > threshold) state = STATE_3;
    else if(state == STATE_2 && meanValue <= threshold) state = STATE_4;
    else if(state == STATE_3 && nbEvent == 3) state = STATE_5;
    else if(state == STATE_3 && nbEvent < 3) state = STATE_0;
    else if(state == STATE_5 && bp2 == 1 && previousBp2 == 0) state = STATE_6;
    else if(state == STATE_4) state = STATE_0;
    else if(state == STATE_6) state = STATE_0;

    switch (state) {      
      case STATE_1:      
        digitalWrite(LED_GREEN_PIN, LOW);
        analogValue += analogRead(ANALOG_PIN)*3.3/1024;
        nbAcquiredValues++;
        Serial.print("Acquisition number : ");
        Serial.print(nbAcquiredValues);
        Serial.print(" - CumSum Value : ");
        Serial.println(analogValue);
        break;
      case STATE_2:
        meanValue = analogValue/nbValuesToAcquire;
        Serial.print("Mean value : ");
        Serial.println(meanValue);
        nbAcquiredValues = 0;
        analogValue = 0;
        break;
      case STATE_3:
        nbEvent++;
        Serial.print("Threshold reached : ");
        Serial.println(nbEvent);
        break;
      case STATE_4:
        nbEvent = 0;
        break;
      case STATE_5:
        digitalWrite(LED_RED_PIN, HIGH);
        nbEvent = 0;
        break;
      case STATE_6:
        digitalWrite(LED_RED_PIN, LOW);
        digitalWrite(LED_GREEN_PIN, HIGH);
        break;
    }

    previousBp1 = bp1;    
    previousBp2 = bp2;   
    previousTime = time;
  }  
}

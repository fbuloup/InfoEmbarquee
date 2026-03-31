// TP2 - Prog 4

#define SAMPLE_PERIOD 500 // en ms
#define ANALOG_PIN A9
#define BP1_PIN D2

#define STATE_0 0
#define STATE_1 1
#define STATE_2 2

const byte nbValuesToAcquire = 10;

float analogValue;

unsigned long time, nbValues;
long previousTime;

byte bp1, previousBp1, state, nbAcquiredValues;

void setup() {
  //analogReference(AR_INTERNAL1V0);
  analogReference(AR_DEFAULT);
  analogReadResolution(10);
  pinMode(BP1_PIN, INPUT);

  Serial.begin(115200);
  while(!Serial) delay(10);

  bp1 = 1;
  previousBp1 = 1;

  nbAcquiredValues = 0;
  analogValue = 0;

  previousTime = -SAMPLE_PERIOD;
}

void loop() {
  time = millis();

  if(time - previousTime >= SAMPLE_PERIOD) {

    bp1 = digitalRead(BP1_PIN);    

    if(bp1 == 0 && previousBp1 == 1 && state == STATE_0) state = STATE_1;
    else if(nbAcquiredValues == nbValuesToAcquire && state == STATE_1) state = STATE_2;
    else if(state == STATE_2) state = STATE_0;

    switch (state) {      
      case STATE_1:
        analogValue += analogRead(ANALOG_PIN)*3.3/1024;
        nbAcquiredValues++;
        Serial.print("Acquisition number : ");
        Serial.print(nbAcquiredValues);
        Serial.print(" - CumSum Value : ");
        Serial.println(analogValue);
        break;
      case STATE_2:
        analogValue = analogValue/nbValuesToAcquire;
        Serial.print("Mean value : ");
        Serial.println(analogValue);
        nbAcquiredValues = 0;
        analogValue = 0;
        break;
    }

    previousBp1 = bp1;    
    previousTime = time;
  }  
}

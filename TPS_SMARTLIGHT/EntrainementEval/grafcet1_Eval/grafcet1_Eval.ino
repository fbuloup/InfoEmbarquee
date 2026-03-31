#define STATE_0 0
#define STATE_1 1
#define STATE_21 21
#define STATE_22 22

#define BP1_PIN D2
#define ANALOG_PIN A9
#define LED_RED_PIN D6
#define LED_GREEN_PIN D7

#define PERIOD 30

unsigned long time;
long lastTime;

float analogValue;
byte bp1, lastBp1;

byte currentState;

bool rec0, rec1a, rec1b;

void setup() {
  currentState = STATE_0;
  lastTime = -PERIOD;
  lastBp1 = 1;
  pinMode(BP1_PIN, INPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  analogReference(AR_DEFAULT);
  analogReadResolution(10);
  Serial.begin(9600);
}

void loop() {

  time = millis();
  if(time - lastTime >= PERIOD) {
    bp1 = digitalRead(BP1_PIN);

    rec0 = (bp1 == 0) && (lastBp1 == 1);
    rec1a = (analogValue < 1.65);
    rec1b = (analogValue >= 1.65);

    if(currentState == STATE_0 && rec0) currentState = STATE_1;
    else if(currentState == STATE_1 && rec1a) currentState = STATE_21;
    else if(currentState == STATE_1 && rec1b) currentState = STATE_22;
    else if(currentState == STATE_21) currentState = STATE_0;
    else if(currentState == STATE_22) currentState = STATE_0;

    switch(currentState) {
      case STATE_1 :
        analogValue = analogRead(ANALOG_PIN);
        analogValue = analogValue*3.3/1024;
        Serial.println(analogValue);
        break;
      case STATE_21 :
        digitalWrite(LED_RED_PIN, HIGH);
        digitalWrite(LED_GREEN_PIN, LOW);
        Serial.println("LED RED HIGH");
        break;
      case STATE_22 :
        digitalWrite(LED_RED_PIN, LOW);
        digitalWrite(LED_GREEN_PIN, HIGH);
        Serial.println("LED GREEN HIGH");
        break;
    }

    lastBp1 = bp1;
    lastTime = time;
  }

}

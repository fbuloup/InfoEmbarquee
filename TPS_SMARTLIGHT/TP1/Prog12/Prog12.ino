// TP1 - PROG12

#define LED_D5_PIN D10
#define T_LED_D5 2000
#define LED_RED_PIN D6
#define LED_GREEN_PIN D7

#define BP1_PIN D2
#define BP2_PIN D3
#define T_BP 30

#define STATE_10 10
#define STATE_11 11
#define STATE_12 12

#define STATE_20 20
#define STATE_21 21
#define STATE_22 22

#define DT 5000 

long time, previousTimeBp1, previousTimeBp2, timeEnteringState12, timeEnteringState22, timeEnd2;
bool bp1Pushed, bp2Pushed, enteringState12, enteringState22, end1, end2;
int bp1, bp2, lastBp1, lastBp2;

byte currentState1 = STATE_10;
byte currentState2 = STATE_20;
  
void setup() {
  pinMode(LED_D5_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(BP1_PIN, INPUT);
  pinMode(BP2_PIN, INPUT);
  lastBp1 = 1;
  lastBp2 = 1;
  previousTimeBp1 = -T_BP;
  previousTimeBp2 = -T_BP;
}

void loop() {
  time = millis();
  // Acquisition bouton 1 front montant
  bp1Pushed = false;
  if(time - previousTimeBp1 >= T_BP) {
    bp1 = digitalRead(BP1_PIN);
    if(bp1 == 0 && lastBp1 == 1) bp1Pushed = true;
    lastBp1 = bp1;
    previousTimeBp1 = time;
  }
  // Acquisition bouton 2 front montant
  bp2Pushed = false;
  if(time - previousTimeBp2 >= T_BP) {
    bp2 = digitalRead(BP2_PIN);
    if(bp2 == 0 && lastBp2 == 1) bp2Pushed = true;
    lastBp2 = bp2;
    previousTimeBp2 = time;
  }
  // Gestion changement d'état grafcet 1
  if(currentState1 == STATE_10) currentState1 = STATE_11;
  else if(currentState1 == STATE_11 && bp1Pushed) currentState1 = STATE_12;
  else if(currentState1 == STATE_12 && (bp1Pushed || end1)) currentState1 = STATE_10;
  // Exécution des actions grafcet 1
  switch(currentState1) {
    case STATE_11:
      digitalWrite(LED_RED_PIN, LOW);
      enteringState12 = true;
      end1 = false;
      break;
    case STATE_12:
      if(enteringState12) timeEnteringState12 = time;
      enteringState12 = false;
      end1 = (time - timeEnteringState12) > DT ? true : false;
      digitalWrite(LED_RED_PIN, HIGH);
      break;
  }
  // Gestion changement d'état grafcet 2
  if(currentState2 == STATE_20) currentState2 = STATE_21;
  else if(currentState2 == STATE_21 && bp2Pushed) currentState2 = STATE_22;
  else if(currentState2 == STATE_22 && end2) currentState2 = STATE_20;
  // Exécution des actions grafcet 2
  switch(currentState2) {
    case STATE_21:
      digitalWrite(LED_GREEN_PIN, LOW);
      enteringState22 = true;
      end2 = false;
      break;
    case STATE_22:
      if(enteringState22) {
        timeEnteringState22 = time;
        timeEnd2 = timeEnteringState22 + DT;
      } else if(bp2Pushed) timeEnd2 = timeEnd2 + DT;
      enteringState22 = false;
      end2 = time > timeEnd2 ? true : false;
      digitalWrite(LED_GREEN_PIN, HIGH);
      break;
  }
  // Led de vie
  blinkLed();
}

void blinkLed() {
  static unsigned int compute;
  compute = time % T_LED_D5; // Reste de la division entière
  if(compute < T_LED_D5/2) digitalWrite(LED_D5_PIN, HIGH);
  else digitalWrite(LED_D5_PIN, LOW);
}

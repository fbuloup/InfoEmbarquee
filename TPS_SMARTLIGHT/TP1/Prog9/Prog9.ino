// TP1 - PROG9

#define LED_D5_PIN D10
#define LED_D7_PIN D8
#define T_LED_D5 2000
#define BP1_PIN D2
#define T_BP 30 // 30ms

#define STATE_0 0
#define STATE_1 1
#define STATE_2 2

unsigned long time, t0;
long previousTime;
int bp1, counter;

byte currentState;
  
void setup() {
  pinMode(LED_D5_PIN, OUTPUT);
  pinMode(LED_D7_PIN, OUTPUT);
  pinMode(BP1_PIN, INPUT);
  previousTime = -T_BP;
  counter = 0;
  currentState = STATE_0;
  Serial.begin(9600);
  t0 = millis();
}

void loop() {
  time = millis() - t0;

  // Acquisition boutons ssi dt >= T_BP
  if(time - previousTime >= T_BP) { 
    bp1 = digitalRead(BP1_PIN);
    if(bp1 == 0 && currentState == STATE_0) currentState = STATE_1;
    else if(currentState == STATE_1) currentState = STATE_2;
    else if(bp1 == 1 && currentState == STATE_2) currentState = STATE_0;
    if(currentState == STATE_0) {
      digitalWrite(LED_D7_PIN, LOW);
    }
    if(currentState == STATE_1) { 
      counter++;
      digitalWrite(LED_D7_PIN, HIGH);
      Serial.println(counter);
    }
     previousTime = time; 
   } 

  // Led de vie
  blinkLed(LED_D5_PIN, T_LED_D5);
}

void blinkLed(byte ledPin, unsigned int tLed) {
  static unsigned int compute;
  compute = time % tLed; // Reste de la division entière
  if(compute < tLed/2) digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin, LOW);
}
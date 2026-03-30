// TP1 - PROG6

#define LED_D5_PIN D10
#define T_LED_D5 2000
#define LED_RED_PIN D6
#define BP1_PIN D2
#define BP2_PIN D3

unsigned long time;
int bp1, bp2;
  
void setup() {
  pinMode(LED_D5_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(BP1_PIN, INPUT);
  pinMode(BP2_PIN, INPUT);
  t0 = millis();
}

void loop() {
  time = millis();

  bp1 = digitalRead(BP1_PIN);
  bp2 = digitalRead(BP2_PIN);
  if(bp1 == 0) digitalWrite(LED_RED_PIN, HIGH);
  if(bp2 == 0) digitalWrite(LED_RED_PIN, LOW);
  
  // Led de vie
  blinkLed();
}

void blinkLed() {
  static unsigned int compute;
  compute = time % T_LED_D5; // Reste de la division entière
  if(compute < T_LED_D5/2) digitalWrite(LED_D5_PIN, HIGH);
  else digitalWrite(LED_D5_PIN, LOW);
}

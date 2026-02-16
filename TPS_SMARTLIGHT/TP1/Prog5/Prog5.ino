// TP1 - PROG5

#define LED_D5_PIN D10
#define LED_RED_PIN D6
#define BP1_PIN D2
#define T_LED 2000

unsigned long time, t0;
int bp1;
  
void setup() {
  pinMode(LED_D5_PIN, OUTPUT);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(BP1_PIN, INPUT);
  t0 = millis();
}

void loop() {
  time = millis() - t0;
  
  bp1 = digitalRead(BP1_PIN);
  digitalWrite(LED_RED_PIN, bp1?LOW:HIGH);
  
  // Led de vie
  blinkLed();
}

void blinkLed() {
  static unsigned int compute;
  compute = time % T_LED; // Reste de la division entière
  if(compute < T_LED/2) digitalWrite(LED_D5_PIN, HIGH);
  else digitalWrite(LED_D5_PIN, LOW);
}
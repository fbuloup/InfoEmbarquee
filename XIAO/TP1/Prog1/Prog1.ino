// TP1 - PROG1

#define LED_D5_PIN D10
#define T_LED_D5 2000

unsigned long time, t0;
  
void setup() {
  pinMode(LED_D5_PIN, OUTPUT);
  t0 = millis();
}

void loop() {
  time = millis() - t0;
  // Led de vie
  blinkLed();
}

void blinkLed() {
  static unsigned int compute;
  compute = time % T_LED_D5; // Reste de la division entière
  if(compute < T_LED_D5/2) digitalWrite(LED_D5_PIN, HIGH);
  else digitalWrite(LED_D5_PIN, LOW);
}
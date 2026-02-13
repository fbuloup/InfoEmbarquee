// TP1 - PROG2

#define LED_D5_PIN D10
#define LED_BLUE_PIN D9
#define T_LED_D5 2000
#define T_LED_BLUE 800

unsigned long time, t0;
  
void setup() {
  pinMode(LED_D5_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  t0 = millis();
}

void loop() {
  time = millis() - t0;
  // Led bleue
  blinkLed(LED_BLUE_PIN, T_LED_BLUE);
  // Led de vie
  blinkLed(LED_D5_PIN, T_LED_D5);
}

void blinkLed(byte ledPin, unsigned int tLed) {
  static unsigned int compute;
  compute = time % tLed; // Reste de la division entière
  if(compute < tLed/2) digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin, LOW);
}

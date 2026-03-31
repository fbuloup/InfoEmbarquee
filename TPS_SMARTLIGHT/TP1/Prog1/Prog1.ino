// TP1 - PROG1

#define LED_D5_PIN D10
#define T_LED_D5 2000

unsigned long time;
  
void setup() {
  pinMode(LED_D5_PIN, OUTPUT);
}

void loop() {
  time = millis();
  // Led de vie
  blinkLed();
}

void blinkLed() {
  static unsigned int compute;
  compute = time % T_LED_D5; // Reste de la division entière
  if(compute < T_LED_D5/2) digitalWrite(LED_D5_PIN, HIGH);
  else digitalWrite(LED_D5_PIN, LOW);
}

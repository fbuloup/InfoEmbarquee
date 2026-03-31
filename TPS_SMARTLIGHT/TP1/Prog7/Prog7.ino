// TP1 - PROG7

#define LED_D5_PIN D10
#define T_LED_D5 2000
#define BP1_PIN D2
#define T_BP1 30 // 30ms - Mettre en commentaire pour rebonds

long time, bp1Counter;
long previousTime; // Mettre en commentaire pour rebonds
int bp1, lastBp1;
  
void setup() {
  pinMode(LED_D5_PIN, OUTPUT);
  pinMode(BP1_PIN, INPUT);
  bp1Counter = 0;
  lastBp1 = 1;
  previousTime = -T_BP1; // Mettre en commentaire pour rebonds
  Serial.begin(9600);
}

void loop() {
  time = millis();

  // Acquisition ssi dt >= T_BP1
  if(time - previousTime >= T_BP1) { // Mettre en commentaire pour rebonds
    bp1 = digitalRead(BP1_PIN);
    if(bp1 == 0 && lastBp1 == 1) { // Falling edge (front descendant)
      bp1Counter++;
      Serial.println(bp1Counter);
    }
    lastBp1 = bp1;
    previousTime = time;
  } // Mettre en commentaire pour rebonds

  // Led de vie
  blinkLed();
}

void blinkLed() {
  static unsigned int compute;
  compute = time % T_LED_D5; // Reste de la division entière
  if(compute < T_LED_D5/2) digitalWrite(LED_D5_PIN, HIGH);
  else digitalWrite(LED_D5_PIN, LOW);
}

// TP1 - PROG6

#define LED_D5_PIN D10
#define T_LED_D5 2000
#define BP1_PIN D2
#define BP2_PIN D3
#define T_BP 30 // 30ms - Mettre en commentaire pour rebonds

unsigned long time, t0, bpCounter;
long previousTime; // Mettre en commentaire pour rebonds
int bp1, bp2, lastBp1, lastBp2;
  
void setup() {
  pinMode(LED_D5_PIN, OUTPUT);
  pinMode(BP1_PIN, INPUT);
  pinMode(BP2_PIN, INPUT);
  bpCounter = 0;
  lastBp1 = 1;
  lastBp2 = 1;
  previousTime = -T_BP; // Mettre en commentaire pour rebonds
  Serial.begin(9600);
  t0 = millis();
}

void loop() {
  time = millis() - t0;

  // Acquisition boutons ssi dt >= T_BP
  if(time - previousTime >= T_BP) { // Mettre en commentaire pour rebonds
    bp1 = digitalRead(BP1_PIN);
    bp2 = digitalRead(BP2_PIN);
    if(bp1 == 0 && lastBp1 == 1) { // Falling edge
      bpCounter++;
      Serial.println(bpCounter);
    }
    if(bp2 == 0 && lastBp2 == 1) { // Falling edge
      bpCounter--;
      Serial.println(bpCounter);
    }
    lastBp1 = bp1;
    lastBp2 = bp2;
    previousTime = time; // Mettre en commentaire pour rebonds
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
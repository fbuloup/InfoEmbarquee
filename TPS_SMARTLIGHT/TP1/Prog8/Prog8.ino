// TP1 - PROG8

#define LED_D5_PIN D10
#define LED_BLUE_PIN D9
#define T_LED_D5 2000
#define BP1_PIN D2
#define BP2_PIN D3
#define T_BP 30 // 30ms

unsigned long time, tLedBlue;
long previousTime;
int bp1, bp2, lastBp1, lastBp2;
  
void setup() {
  pinMode(LED_D5_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  pinMode(BP1_PIN, INPUT);
  pinMode(BP2_PIN, INPUT);
  lastBp1 = 1;
  lastBp2 = 1;
  previousTime = -T_BP;
  tLedBlue = 800;
  Serial.begin(9600);
}

void loop() {
  time = millis();

  // Acquisition boutons ssi dt >= T_BP
  if(time - previousTime >= T_BP) { 
    bp1 = digitalRead(BP1_PIN);
    bp2 = digitalRead(BP2_PIN);
    if(bp1 == 0 && lastBp1 == 1) { // Falling edge
      tLedBlue+=50;
      if(tLedBlue > 2000) tLedBlue = 2000;
      Serial.println(tLedBlue);
    }
    if(bp2 == 0 && lastBp2 == 1) { // Falling edge
      tLedBlue-=50;
      if(tLedBlue < 200) tLedBlue = 200;
      Serial.println(tLedBlue);
    }
    lastBp1 = bp1;
    lastBp2 = bp2;
    previousTime = time; 
  } 
   
  blinkLed(LED_BLUE_PIN, tLedBlue );

  // Led de vie
  blinkLed(LED_D5_PIN, T_LED_D5);
}

void blinkLed(byte ledPin, unsigned int tLed) {
  static unsigned int compute;
  compute = time % tLed; // Reste de la division entière
  if(compute < tLed/2) digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin, LOW);
}

// TP2 - Prog 1, 1b et 1c

#define SAMPLE_PERIOD 500 // en ms
#define ANALOG_PIN A9

bool firstLoop;
unsigned int sensorValueInt;
float sensorValueVolt;

unsigned long time, t0, previousTime;

void setup() {
  //analogReference(AR_INTERNAL1V0);
  analogReference(AR_DEFAULT);
  analogReadResolution(10);
  Serial.begin(9600);
  previousTime = -SAMPLE_PERIOD;
  t0 = millis();
  time = 0;
}

void loop() {
  time = millis() - t0;

  if(time - previousTime >= SAMPLE_PERIOD) {
    sensorValueInt = analogRead(ANALOG_PIN);
    Serial.print(sensorValueInt);
    Serial.print(" - ");
    sensorValueVolt = sensorValueInt*3.28 / 1017;
    Serial.println(sensorValueVolt);
    previousTime = time;
  }
  // AR_DEFAULT
  // Valeur min 0 pour 0V
  // Valeur max 1017 pour 3.28V
  // Valeur centrale : 509 pour 1.64V
  // q = 3.28/1017 # 3.22mV
  
}

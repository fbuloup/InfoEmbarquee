#define SAMPLE_PERIOD 500 // ms
#define ANALOG_PIN A9

bool firstLoop;
unsigned int sensorValueInt;
float sensorValueVolt;

unsigned long time, t0, previousTime;

void setup() {
  //analogReference(AR_DEFAULT);
  analogReference(AR_DEFAULT);
  analogReadResolution(10);
  Serial.begin(9600);
  previousTime = -SAMPLE_PERIOD;
}

void loop() {
  if(firstLoop) {
    t0 = millis();
    time = 0;
    firstLoop = false;
  } else time = millis() - t0;

  if(time - previousTime >= SAMPLE_PERIOD) {
    sensorValueInt = analogRead(ANALOG_PIN);
    Serial.print(sensorValueInt);
    Serial.print(" - ");
    sensorValueVolt = sensorValueInt*3.3 / 1019;//map(sensorValueInt, 0, 4095, 0, 3300000);
    Serial.println(sensorValueVolt);
    previousTime = time;
  }
  // AR_DEFAULT
  // Valeur min 0 pour 0V
  // Valeur max 1019 pour 3.3V
  // Valeur centrale : 510 pour 1.64V
  // q = 3.3/1019 # 3.24mV
  
}

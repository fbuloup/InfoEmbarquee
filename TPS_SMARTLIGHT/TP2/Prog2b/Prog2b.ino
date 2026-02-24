// TP2 - Prog 2b

#define SAMPLE_PERIOD 500 // en ms
#define ANALOG_PIN A0
const unsigned int N = 10; // Taille de la moyenne glissante

float sensorValueLux;

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
    sensorValueLux = getPhotoTransistorLux();
    sensorValueLux = movingAverage(sensorValueLux);
    Serial.println(sensorValueLux);
    previousTime = time;
  }
}

float movingAverage(float newValue) {
  static float values[N]; // Automatically initialized to 0.0
  static unsigned int index = 0; // Explicitly initialized (not needed !)
  static float total = 0; // Explicitly initialized (not needed !)
  if(index >= N) index = 0;
  total = total - values[index];
  values[index] = newValue;
  total = total + values[index];
  index++;
  return total/N;
}

float getPhotoTransistorLux() {
  // AR_DEFAULT
  // Valeur min 0 pour 0V
  // Valeur max 1023 pour (3.3 - q)V
  // Valeur centrale : 512 pour 1.65V
  // q = 3.3/1024 # 3.223mV
  // Vlight1 = R1*IPCE => IPCE = Vlight1/R1 
  // IPCE = Vlight1/51*10^(-3) A
  // IPCE = 1000/51*Vlight1 en uA (1)
  // Pour 10 lux IPCE/IPCEmax = 0.01
  // Pour 100 lux IPCE/IPCEmax = 0.1
  // ...
  // Pour 10000 lux IPCE/IPCEmax = 10
  // ...
  // Ev(lux) = 1000*IPCE/IPCEmax
  // Avec (1) :
  // Ev(lux) = 1000000/(51*IPCEmax)*Vlight1
  // IPCEmax en uA. On prendra 24uA
  // Ev(lux) = 1000000/(51*24)*3.3/1024*N
  // N étant le nombre donné par le CAN
  // Ev (lux) = 3300000/1253376*N
  // Ev (lux) # 2.6328891*N
  static unsigned int valueInt;
  static float value;
  valueInt = analogRead(ANALOG_PIN);
  value = 2.6328891*valueInt;
  return value;
}
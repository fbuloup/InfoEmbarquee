// TP2 - Prog 2

#define SAMPLE_PERIOD 500 // en ms
#define ANALOG_PIN A0

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
    Serial.println(sensorValueLux);
    previousTime = time;
  }
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
  // Ev (lux) # 2.6328891*N pour IPCEmax = 24uA
  // Si on prend IPCEmax = 16uA on aura :
  // Ev (lux) # 3.94933*N
  // Et si on prend IPCEmax = 32uA on aura :
  // Ev (lux) # 1.9746*N
  static unsigned int valueInt;
  static float value;
  valueInt = analogRead(ANALOG_PIN);
  value = 2.6329*valueInt;
  return value;
}

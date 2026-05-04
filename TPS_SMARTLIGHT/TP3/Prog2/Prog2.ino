#define PERIOD 100

#define BP1_PIN D2

unsigned long time;
long lastTime, letter;

byte bp1, lastBp1;

void setup() {
  Serial1.begin(2400, SERIAL_8E1);
  while(!Serial1);
  lastTime = -PERIOD;
  bp1 = 1;
  lastBp1 = 1;
  pinMode(BP1_PIN, INPUT);
  Serial.begin(9600);
}
 
void loop() {
  time = millis();
  if(time - lastTime >= PERIOD) {
    bp1 = digitalRead(BP1_PIN);
    if(bp1 == 0 && lastBp1 == 1) {
      letter = random(65, 91);
      Serial1.write(letter);
      Serial.write(letter);
    }
    lastBp1 = bp1;
    lastTime = time;
  }

}
 
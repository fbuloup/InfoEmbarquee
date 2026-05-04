#define PERIOD 100

unsigned long time;
long lastTime;

void setup() {
  Serial1.begin(9600,SERIAL_8E1);
  lastTime = -PERIOD;
  while(!Serial1);
}
 
void loop() {
  time = millis();
  if(time - lastTime >= PERIOD) {
    Serial1.write('C');
    lastTime = time;
  }

/*
La trame selon l'axe temporel : 01100001011 11 bits 
  0           11000010              1                1
start.    data LSB -> MSB.      Parité paire         stop
                                donc bit à 1
                                puisque nombre
                                de bit à 1 dans
                                data impair

donc 'C' en binaire 01000011 (0x43 = 67)
*/

}
 
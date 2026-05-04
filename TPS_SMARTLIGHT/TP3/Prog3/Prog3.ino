void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600, SERIAL_8O1);
  while (!Serial1);
  Serial.begin(9600);
  while (!Serial);
  Serial.write(83);
  Serial.write(79);
  Serial.write(0x53);
  Serial.write(13);
  Serial.write(0x0A);
  Serial.write('O');
  Serial.write(107);
  int nbOctets = Serial.write("Vive GEII!");
  Serial.write(nbOctets);
  //Serial.print(nbOctets);
  Serial.print(" Commande Serial.print avec nombre ");
  Serial.println(3.1416);
  float pi = 3.1415926535;
  Serial.print("Commande Serial.print avec variable ");
  Serial.println(pi, 4);
  Serial.print("Commande Serial.print avec caractères spéciaux \n\r\n\r");
  Serial.println("Interprétez l'affichage");
}

void loop() {
  Serial1.write(0x55);
  delay(500);
}

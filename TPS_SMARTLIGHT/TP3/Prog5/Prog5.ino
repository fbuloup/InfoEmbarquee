#define LED_RED_PIN D6

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;     // whether the string is complete

void setup() {
  pinMode(LED_RED_PIN, OUTPUT);
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  mySerialEvent();
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    if(inputString.equalsIgnoreCase("ON")) {
      Serial.println("LED ON");
      digitalWrite(LED_RED_PIN, HIGH);
    }
    if(inputString.equalsIgnoreCase("OFF")) {
      Serial.println("LED OFF");
      digitalWrite(LED_RED_PIN, LOW);
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX.
  This routine is run between each time loop() runs, so using delay inside loop can delay response.
  Multiple bytes of data may be available.
*/
void mySerialEvent() { // Le serialEvent classique ne peut pas marcher avec l'USB
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    // inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it
    // Mettre le moniteur serie en "New Line"
    if (inChar == '\n' || inChar == '\r') {
      stringComplete = true;
    } else inputString += inChar;
  }
}
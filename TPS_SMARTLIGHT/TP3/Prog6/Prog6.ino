#define LED_RED_PIN D6
#define LED_GREEN_PIN D7
#define LED_BLUE_PIN D9

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;     // whether the string is complete
long value;

void setup() {
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  mySerialEvent();
  // print the string when a newline arrives:
  if (stringComplete) {
    inputString.toUpperCase();
    Serial.println(inputString);
    if(inputString.equals("ON")) {
      digitalWrite(LED_RED_PIN, HIGH);
    }
    if(inputString.equals("OFF")) {
      digitalWrite(LED_RED_PIN, LOW);
    }
    if(inputString.startsWith("MA ")) {
      inputString = inputString.substring(3);
      if(inputString.equalsIgnoreCase("R")) digitalWrite(LED_RED_PIN, HIGH);
      else if(inputString.equalsIgnoreCase("G")) digitalWrite(LED_GREEN_PIN, HIGH);
      else if(inputString.equalsIgnoreCase("B")) digitalWrite(LED_BLUE_PIN, HIGH);
    }
    if(inputString.startsWith("AR ")) {
      inputString = inputString.substring(3);
      if(inputString.equalsIgnoreCase("R")) digitalWrite(LED_RED_PIN, LOW);
      else if(inputString.equalsIgnoreCase("G")) digitalWrite(LED_GREEN_PIN, LOW);
      else if(inputString.equalsIgnoreCase("B")) digitalWrite(LED_BLUE_PIN, LOW);
    }
    if(inputString.startsWith("R ")) {
      inputString = inputString.substring(2);
      value = inputString.toInt();
      analogWrite(LED_RED_PIN, value);
    }
    if(inputString.startsWith("G ")) {
      inputString = inputString.substring(2);
      value = inputString.toInt();
      analogWrite(LED_GREEN_PIN, value);
    }
    if(inputString.startsWith("B ")) {
      inputString = inputString.substring(2);
      value = inputString.toInt();
      analogWrite(LED_BLUE_PIN, value);
    }
    if(inputString.startsWith("RH ")) {
      inputString = inputString.substring(3);
      value = strtol(inputString.c_str(), NULL, 16);
      analogWrite(LED_RED_PIN, value);
    }
    if(inputString.startsWith("GH ")) {
      inputString = inputString.substring(3);
      value = strtol(inputString.c_str(), NULL, 16);
      analogWrite(LED_GREEN_PIN, value);
    }
    if(inputString.startsWith("BH ")) {
      inputString = inputString.substring(3);
      value = strtol(inputString.c_str(), NULL, 16);
      analogWrite(LED_BLUE_PIN, value);
    }
    if(inputString.startsWith("RGB ")) {
      inputString = inputString.substring(4);
      String RString = inputString.substring(0, inputString.indexOf(" "));
      inputString.remove(0, inputString.indexOf(" ") + 1);
      String GString = inputString.substring(0, inputString.indexOf(" "));
      inputString.remove(0, inputString.indexOf(" ") + 1);
      String BString = inputString;
      value = RString.toInt();
      analogWrite(LED_RED_PIN, value);
      value = GString.toInt();
      analogWrite(LED_GREEN_PIN, value);
      value = BString.toInt();
      analogWrite(LED_BLUE_PIN, value);
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
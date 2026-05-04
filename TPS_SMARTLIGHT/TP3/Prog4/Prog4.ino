#define LED_RED_PIN D6

void setup() {
  pinMode(LED_RED_PIN, OUTPUT); // Configure la broche de la LED en sortie
  Serial.begin(9600); // Initialise la communication série à 9600 bauds
  while(!Serial);
  afficherMenu(); // Affiche le menu au démarrage
}

void loop() {
  // Vérifie si des données sont disponibles sur le port série
  if (Serial.available() > 0) {
    char commande = Serial.read(); // Lit le caractère reçu

    // Allume la LED si le caractère est '1'
    if (commande == '1') {
      digitalWrite(LED_RED_PIN, HIGH);
      Serial.println("LED allumée.");
    }
    // Éteint la LED si le caractère est '0'
    else if (commande == '0') {
      digitalWrite(LED_RED_PIN, LOW);
      Serial.println("LED éteinte.");
    }
    // Affiche un message d'erreur si la commande est invalide
    else {
      Serial.println("Commande invalide. Tapez 1 pour allumer ou 0 pour éteindre.");
    }

    afficherMenu(); // Réaffiche le menu après chaque commande
  }
}

// Fonction pour afficher le menu
void afficherMenu() {
  Serial.println("----- Menu -----");
  Serial.println("Tapez 1 pour allumer la LED.");
  Serial.println("Tapez 0 pour éteindre la LED.");
  Serial.println("----------------");
}
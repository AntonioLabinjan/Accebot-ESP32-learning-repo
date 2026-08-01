/*
/*
  ESP32 SOS Beacon

  Opis:
  -------
  Ovaj program pretvara ESP32 + LED + gumb u mali SOS signalni uređaj.

  Pritiskom na gumb uključuje se/isključuje SOS mod.
  Kada je SOS mod aktivan, LED šalje Morseov signal:

      ... --- ...

  Implementacija:
  -------
  - Gumb ne pali direktno LED, nego mijenja stanje sustava (toggle).
  - Varijabla sosEnabled pamti je li SOS trenutno uključen.
  - Detekcija klika radi preko promjene stanja gumba:
        HIGH -> LOW

  - SOS signal ne koristi delay().
    Umjesto toga koristi se millis(), što omogućava da ESP32
    tijekom čekanja i dalje reagira na ulaze.

  - pattern[] predstavlja vremenski raspored LED signala:
        trajanje ON/OFF intervala u milisekundama.

  - step označava trenutnu poziciju unutar SOS sekvence.

  Koncepti demonstrirani:
  -------
  - digitalni input/output
  - state machine
  - event detection
  - non-blocking programiranje
  - millis() timer
  - sekvencijalno upravljanje ponašanjem uređaja

  Ovo je temeljna arhitektura za buduće ESP32 IoT nodeove:
  
        događaj (gumb/MQTT poruka)
                    |
                    v
              promjena stanja
                    |
                    v
              izvršavanje akcije

  U budućnosti se isti princip može koristiti za:
  MQTT naredbe, releje, brave, senzore itd.
*/


#define ledPin 5
#define buttonPin 16
  */

#define ledPin 5
#define buttonPin 16

bool sosEnabled = false;
bool lastButtonState = HIGH;

unsigned long previousMillis = 0;

int step = 0;
bool ledState = LOW;

// SOS pattern:
// . . . - - - . . .
int pattern[] = {
  200, 200,
  200, 200,
  200, 200,

  600, 200,
  600, 200,
  600, 200,

  200, 200,
  200, 200,
  200, 800
};

int patternLength = sizeof(pattern) / sizeof(pattern[0]);


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  digitalWrite(ledPin, LOW);
}


void loop() {

  bool currentButtonState = digitalRead(buttonPin);


  // Detekcija pritiska gumba (rising/falling edge)
  if (lastButtonState == HIGH && currentButtonState == LOW) {

    sosEnabled = !sosEnabled;

    // resetiraj SOS kada se ponovno uključi
    step = 0;
    ledState = LOW;
    digitalWrite(ledPin, LOW);

  }

  lastButtonState = currentButtonState;


  if (sosEnabled) {
    runSOS();
  }
  else {
    digitalWrite(ledPin, LOW);
  }
}


void runSOS() {

  unsigned long currentMillis = millis();


  if (currentMillis - previousMillis >= pattern[step]) {

    previousMillis = currentMillis;


    ledState = !ledState;
    digitalWrite(ledPin, ledState);


    step++;

    if (step >= patternLength) {
      step = 0;
    }
  }
}

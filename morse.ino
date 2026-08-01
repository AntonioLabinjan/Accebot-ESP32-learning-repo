#define ledPin 5
#define buttonPin 16

int mode = 0;
bool lastButton = HIGH;

void blink(int onTime, int offTime, int count) {
  for (int i = 0; i < count; i++) {
    digitalWrite(ledPin, HIGH);
    delay(onTime);
    digitalWrite(ledPin, LOW);
    delay(offTime);
  }
}

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  bool current = digitalRead(buttonPin);

  if (lastButton == HIGH && current == LOW) {
    mode++;
    if (mode > 3) mode = 0;
  }

  lastButton = current;

  switch (mode) {

    case 0:
      digitalWrite(ledPin, LOW);
      break;

    case 1:
      blink(100,100,1);
      break;

    case 2:
      blink(100,100,3);
      break;

    case 3:
      blink(500,200,1);
      break;
  }
}

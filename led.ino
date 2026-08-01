#define ledPin 5
#define buttonPin 16

void setup(){
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop(){
  int buttonState = digitalRead(buttonPin);

  if(buttonState == LOW){
    digitalWrite(ledPin, HIGH);
  } else if (buttonState == HIGH){
    digitalWrite(ledPin, LOW);
  }
}

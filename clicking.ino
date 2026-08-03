#define buzzerPin 5 // the buzzer pin

void setup()
{
  pinMode(buzzerPin, OUTPUT); // Set as output
}

void loop()
{
    digitalWrite(buzzerPin, HIGH); 
    delay(100); 
    digitalWrite(buzzerPin, LOW); 
    delay(100); 
}

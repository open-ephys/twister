const int speakerPin = 6;

void setup()
{
  pinMode(speakerPin, OUTPUT);
}

void playTone(int t, int duration) {
  for (long i = 0; i < duration * 1000L; i += t * 2) {
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(t);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(t);
  }
}

void loop() {
  playTone(500, 100);
  delay(100);
  playTone(500, 100);
  delay(2000);   
}


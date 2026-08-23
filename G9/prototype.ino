const int buzzer = 8;
const int ldrPins[4] = {A0, A1, A2, A3};

const int LIGHT_THRESHOLD = 500;
bool readyToTrigger[4] = {true, true, true, true};

int lyreNotes[] = {
  262, 294, 330, 349
};

void setup() {
  pinMode(buzzer, OUTPUT);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    int lightLevel = analogRead(ldrPins[i]);

    if (lightLevel < LIGHT_THRESHOLD && readyToTrigger[i]) {
      playLyre(i);
      readyToTrigger[i] = false;
    }

    if (lightLevel >= LIGHT_THRESHOLD) {
      readyToTrigger[i] = true;
    }
  }

  delay(20);
}

void playLyre(int stringIndex) {
  tone(buzzer, lyreNotes[stringIndex], 250);
  delay(300);
  noTone(buzzer);
}
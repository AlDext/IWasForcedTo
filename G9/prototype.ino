const int buzzer = 8;
const int ldrPins[4] = {A0, A1, A2, A3};

const int LIGHT_THRESHOLD = 500;
bool readyToTrigger = true;

int lyreNotes[] = {
  262, 294, 330, 349, 392, 440, 494, 523
}; // C D E F G A B C

void setup() {
  pinMode(buzzer, OUTPUT);
}

void loop() {
  bool allLit = true;
  bool oneDark = false;

  for (int i = 0; i < 4; i++) {
    int lightLevel = analogRead(ldrPins[i]);

    if (lightLevel < LIGHT_THRESHOLD) {
      oneDark = true;
      allLit = false;
    }
  }

  
  if (readyToTrigger && oneDark) {
    playLyre();
    readyToTrigger = false;
  }

  if (!readyToTrigger && allLit) {
    readyToTrigger = true;
  }

  delay(20);
}

void playLyre() {
  for (int i = 0; i < 8; i++) {
    tone(buzzer, lyreNotes[i], 250);
    delay(300);
  }

  noTone(buzzer);
}
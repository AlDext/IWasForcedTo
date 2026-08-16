
int laserPins[] = {2, 3, 4, 5};   

int ldrPins[] = {A0, A1, A2, A3}; 

int buzzerPin = 8;

// C4 = 262,  D4 = 294,  E4 = 330,  F4 = 349
// G4 = 392,  A4 = 440,  B4 = 494,  C5 = 523
int noteFrequencies[] = {262, 330, 392, 523};  // C4, E4, G4, C5

int THRESHOLD = 200;        
int COOLDOWN_MS = 150;      
int NOTE_DURATION_MS = 180; 

bool lastState[4] = {false, false, false, false};     
unsigned long lastPlayTime[4] = {0, 0, 0, 0};         

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(laserPins[i], OUTPUT);
    digitalWrite(laserPins[i], HIGH);   
  }

  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
  
}

void loop() {
  for (int i = 0; i < 4; i++) {
    int ldrValue = analogRead(ldrPins[i]; 
    bool isBlocked = (ldrValue < THRESHOLD);

    if (isBlocked && !lastState[i] && (millis() - lastPlayTime[i] > COOLDOWN_MS)) {
      
      tone(buzzerPin, noteFrequencies[i], NOTE_DURATION_MS);
    }

    lastState[i] = isBlocked;

    // Serial.print("String ");
    // Serial.print(i);
    // Serial.print(": ");
    // Serial.print(ldrValue);
    // Serial.print("  ");
    // if (i == 3) Serial.println(); // New line after all 4
  }
  delay(10);
}

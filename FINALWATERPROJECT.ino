#include <math.h>

#define PIEZO_PIN 34
#define LED_PIN 25
#define BUZZER_PIN 26
#define PUMP_PIN 27

#define SAMPLE_SIZE 128

float samples[SAMPLE_SIZE];

int triggerCount = 0;
const int requiredTriggers = 5;

unsigned long startTime;

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);

  digitalWrite(PUMP_PIN, HIGH); // pump ON

  startTime = millis();

  Serial.println("🚀 Leak Detection System Started");
}

void loop() {

  // ⏱ Run only 30 sec
  if (millis() - startTime > 30000) {
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(PUMP_PIN, LOW);
    Serial.println("⏹ Test Finished");
    while(1);
  }

  // ⏳ Ignore first 5 sec (stabilization)
  if (millis() - startTime < 5000) return;

  // -------- SIGNAL SAMPLING --------
  float sum = 0;
  float peak = 0;

  for (int i = 0; i < SAMPLE_SIZE; i++) {
    samples[i] = analogRead(PIEZO_PIN);

    sum += samples[i] * samples[i];

    if (samples[i] > peak)
      peak = samples[i];

    delayMicroseconds(200);
  }

  // -------- FEATURE EXTRACTION --------
  float rms = sqrt(sum / SAMPLE_SIZE);

  float mean = 0;
  for (int i = 0; i < SAMPLE_SIZE; i++)
    mean += samples[i];
  mean /= SAMPLE_SIZE;

  float variance = 0;
  for (int i = 0; i < SAMPLE_SIZE; i++) {
    float diff = samples[i] - mean;
    variance += diff * diff;
  }
  variance /= SAMPLE_SIZE;

  float freqEnergy = 0;
  for (int i = 1; i < SAMPLE_SIZE; i++) {
    float diff = samples[i] - samples[i - 1];
    freqEnergy += diff * diff;
  }
  freqEnergy /= SAMPLE_SIZE;

  // -------- NOISE FILTER --------
  if (rms < 600) {
    triggerCount = 0;
    Serial.println("Noise ignored");
    return;
  }

  // -------- EDGE AI DECISION --------
 
int score = 0;

if (rms > 2000) score++;          // scaled
if (peak > 3200) score++;         // near max
if (variance > 100000) score++;   // strong instability
if (freqEnergy > 5000) score++;   // strong vibration pattern

bool leakDetected = (score >= 2);   // relaxed

// 🔥 Strong override
if (variance > 500000) {
  leakDetected = true;
}
 

  if (leakDetected)
    triggerCount++;
  else
    triggerCount = 0;

  // -------- OUTPUT --------
  if (triggerCount >= requiredTriggers) {

    Serial.println("🚨 LEAK DETECTED 🚨");

    digitalWrite(BUZZER_PIN, HIGH);

    // LED blinking
    digitalWrite(LED_PIN, HIGH);
    delay(200);
    digitalWrite(LED_PIN, LOW);
    delay(200);

    // Pump OFF
    digitalWrite(PUMP_PIN, LOW);

  } else {

    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    digitalWrite(PUMP_PIN, HIGH);
  }

  // -------- DEBUG --------
  Serial.print("RMS: "); Serial.print(rms);
  Serial.print(" | Peak: "); Serial.print(peak);
  Serial.print(" | Var: "); Serial.print(variance);
  Serial.print(" | Freq: "); Serial.print(freqEnergy);
  Serial.print(" | Score: "); Serial.println(score);

  delay(150);
}
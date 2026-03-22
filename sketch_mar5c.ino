#include <math.h>

const int piezoPin = 34;
const int ledPin = 25;
const int buzzerPin = 26;

const int samples = 64;

const float rmsThreshold = 1050;
const float varianceThreshold = 30000;

unsigned long startTime;

unsigned long lastBlink = 0;
bool ledState = false;

void setup() {

  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  analogReadResolution(12);

  startTime = millis();
}

void loop() {

  unsigned long currentTime = millis();
  float seconds = (currentTime - startTime) / 1000.0;

  if(seconds > 30) {
    Serial.println("Test finished");
    while(true);   // stop program
  }

  int data[samples];

  long sum = 0;
  long sumSquares = 0;
  int peak = 0;

  // ---- Sampling ----
  for(int i = 0; i < samples; i++) {

    data[i] = analogRead(piezoPin);

    sum += data[i];
    sumSquares += (long)data[i] * data[i];

    if(data[i] > peak)
      peak = data[i];

    delayMicroseconds(200);
  }

  float mean = sum / (float)samples;
  float rms = sqrt(sumSquares / (float)samples);
  float variance = (sumSquares / (float)samples) - (mean * mean);

  float freqEnergy = 0;

  for(int i = 1; i < samples; i++) {
    freqEnergy += abs(data[i] - data[i-1]);
  }

  freqEnergy = freqEnergy / samples;

  // ---- Print values with time ----
  Serial.print("Time: ");
  Serial.print(seconds);
  Serial.print(" sec | RMS: ");
  Serial.print(rms);
  Serial.print(" | Peak: ");
  Serial.print(peak);
  Serial.print(" | Variance: ");
  Serial.print(variance);
  Serial.print(" | FreqEnergy: ");
  Serial.println(freqEnergy);

  bool leakDetected = false;

  // ---- Leak detection only after 10 sec ----
  if(seconds > 10) {

    if(rms > rmsThreshold && variance > varianceThreshold && freqEnergy > 30) {
      leakDetected = true;
    }

  }

  // ---- Output ----
  if(leakDetected) {

    digitalWrite(buzzerPin, HIGH);

    if(millis() - lastBlink > 200) {

      ledState = !ledState;
      digitalWrite(ledPin, ledState);

      lastBlink = millis();
    }

  } else {

    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }

  delay(300);
}
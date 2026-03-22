# 💧 Piezoelectric-Based Intelligent Water Leak Detection System

> **Low-Cost | Real-Time | Single-Sensor | Embedded IoT Project**

---

## 📌 Overview

This project presents a **cost-effective and intelligent water leak detection system** using a piezoelectric sensor and ESP32 microcontroller.

The system analyzes vibration signals from pipelines using multiple parameters such as **RMS, Peak, Variance, and Frequency Energy**, along with **time-based filtering** to reduce false alarms caused by motor vibrations.

🚨 Real-time alerts are provided through an **LED and buzzer** when a leak is detected.

---

## 🚀 Key Features

* 🔍 Single sensor-based leak detection
* 📊 Multi-parameter signal analysis
* ⚡ Real-time processing using ESP32
* 🚫 Reduced false alarms using time filtering
* 🔔 Instant alert system (LED + Buzzer)
* 💰 Low-cost and simple hardware design
* 🔮 Future-ready for TinyML integration

---

## 🏗️ System Architecture

```
Piezo Sensor
     ↓
Signal Conditioning
     ↓
ESP32 (ADC Sampling)
     ↓
Feature Extraction
     ↓
Decision Logic
     ↓
Alert System (LED + Buzzer)
```

---

## 🔧 Hardware Components

* ESP32 Microcontroller
* Piezoelectric Sensor
* LED (Alert Indicator)
* Buzzer
* Resistors & Capacitor (Signal Conditioning)
* Water Pump Setup (for testing)

---

## ⚙️ Software & Technologies

* Embedded C / Arduino IDE
* Signal Processing Techniques
* Threshold-Based Detection Logic
* Real-Time Data Sampling

---

## 🔄 Working Principle

### 1. Signal Acquisition

* Piezo sensor captures pipe vibrations
* ESP32 reads analog signals continuously

### 2. Feature Extraction

The following parameters are calculated:

* **RMS (Root Mean Square)** → Overall vibration energy
* **Peak Value** → Maximum signal amplitude
* **Variance** → Signal instability
* **Frequency Energy** → Rapid signal fluctuations

### 3. Decision Logic

```
If (RMS ↑ AND Peak ↑ AND Variance ↑ AND Frequency Energy ↑)
AND condition persists over time
→ Leak Detected
```

### 4. Alert System

* LED starts blinking
* Buzzer turns ON

---

## 🧠 Detection Methods

### 1. RMS Analysis

Measures overall vibration energy in the pipeline.

### 2. Peak Detection

Identifies sudden spikes caused by leak turbulence.

### 3. Variance Analysis

Detects irregular vibration patterns.

### 4. Frequency Energy

Captures rapid signal fluctuations typical in leaks.

### 5. Time-Based Filtering

* Leak is detected only if the condition persists
* Eliminates false triggers from motor vibrations

---

## 📊 Results

| Parameter        | Normal Range | Leak Range |
| ---------------- | ------------ | ---------- |
| RMS              | 100–350      | 600–1180   |
| Peak             | 240–584      | 883–1385   |
| Variance         | Low          | Very High  |
| Frequency Energy | Moderate     | High       |

✅ Clear spikes observed during leak conditions
✅ False alarms significantly reduced
✅ Detection achieved within seconds

---

## 🧪 Project Phases

1. Component setup and wiring
2. Signal acquisition
3. Feature extraction
4. Noise filtering
5. Leak detection logic
6. Alert system implementation

---

## 🌟 Novelty

* Uses a **single piezoelectric sensor** instead of multiple sensors
* Implements **multi-parameter analysis**
* Combines **embedded processing + signal analytics**
* Reduces cost and system complexity
* Designed for future **TinyML integration**

---

## 📱 Applications

* Smart water pipeline monitoring
* Industrial fluid systems
* Home water leak detection
* Smart cities & IoT infrastructure
* Agricultural irrigation systems

---

## ⚠️ Limitations

* Threshold values depend on environment
* Sensor placement affects accuracy
* No wireless monitoring (current version)
* Less accurate than ML-based systems
* Requires calibration for different pipe materials

---

## 🔮 Future Scope

* 📡 IoT-based remote monitoring
* 📱 Mobile app integration
* 🤖 Machine learning-based classification
* 🌐 Cloud data logging and analytics
* 🔧 Auto-calibration system

---

## 👨‍💻 Author

Priyadarshini
priyadarshini0727@gmail.com

---

# AIoT-Based Reactive Autonomous Vehicle
### Real-Time Visual Traffic Sign Recognition using TinyML on Embedded Systems

This project demonstrates the design and implementation of a small-scale autonomous vehicle based on **Artificial Intelligence of Things (AIoT)** principles. The system leverages edge computing to perform real-time visual classification of traffic signs, enabling reactive navigation directly on resource-constrained hardware.

---

## 🚀 Overview

The vehicle utilizes a sophisticated **Perception-Decision-Action** architecture distributed across two microcontrollers. By executing machine learning models directly on the edge, the system achieves low-latency response times without dependency on cloud infrastructure, making it an ideal prototype for smart mobility and automotive engineering applications.

### Key Highlights
- **Edge AI:** Real-time inference using a lightweight Convolutional Neural Network (CNN) optimized via Edge Impulse.
- **Dual-MCU Architecture:** Task separation between perception (XIAO ESP32-S3) and actuation (ESP32).
- **IoT Integration:** Live web dashboard for real-time video streaming and system telemetry.
- **Robust Navigation:** Reactive control system based on visual cues (STOP, LEFT, RIGHT).

---

## 🏗️ System Architecture

The system is built on a modular architecture designed for high-performance edge deployment:

1.  **Perception Layer (XIAO ESP32-S3 Sense):** 
    - Captures environmental data via an integrated camera.
    - Executes the TinyML inference engine.
    - Hosts an HTTP server for live monitoring.
2.  **Communication Bridge:** Reliable data transfer between MCUs using **UART serial communication**.
3.  **Actuation Layer (ESP32 + L298N):**
    - Receives navigation commands.
    - Manages low-level motor control for dual DC motors.
    - Handles power distribution and PWM signals.

---

## 🧠 TinyML Pipeline

The core of the vehicle's intelligence is a visual classifier trained to recognize international traffic signs.

### Model Training & Optimization
- **Framework:** Edge Impulse.
- **Dataset:** Custom-built dataset captured in real-world lighting conditions using the onboard XIAO camera.
- **Preprocessing:** Grayscale conversion and resolution optimization (96x96) to reduce memory footprint.
- **Architecture:** Lightweight CNN with ReLU activation, Max Pooling, and Softmax output.
- **Optimization:** Quantized to INT8 to maximize performance on the ESP32-S3’s vector instructions.

### Performance Results (Beta Phase)
| Class | Accuracy | Notes |
| :--- | :--- | :--- |
| **STOP** | **95%** | High precision in varied lighting. |
| **LEFT** | ~90% | Successfully distinguishes directionality. |
| **RIGHT** | ~91% | Optimized to avoid symmetry confusion. |
| **Background** | 95% | Robust "None" class to prevent false positives. |

> **Note on Model Strategy:** We intentionally allowed for a degree of controlled overfitting to the test environment to act as a "visual memory" for the vehicle, ensuring maximum reliability within the target circuit parameters.

---

## 🛠️ Hardware Stack

- **Primary MCU:** Seeed Studio XIAO ESP32-S3 Sense (8MB PSRAM).
- **Secondary MCU:** ESP32 (General Purpose).
- **Motor Driver:** L298N Dual H-Bridge.
- **Actuators:** 2x High-torque DC Motors.
- **Power:** 7.4V Li-Po battery with independent regulation for logic and power stages.

---

## 🌐 IoT Visualization Interface

The vehicle hosts a local web server that provides:
- **Live Stream:** Real-time MJPEG video feed from the vehicle's perspective.
- **Inference Logs:** Real-time display of predicted classes and confidence scores.
- **System Status:** Telemetry data including connection stability and navigation states.

---

## 🔮 Future Roadmap (The "FOMO" Evolution)

While our current classification-based approach is highly effective, we are transitioning towards **Object Detection (FOMO - Faster Objects, More Objects)**.
- **Spatial Awareness:** Transitioning from "whole frame" classification to specific object localization.
- **Improved Accuracy:** Reducing confusion between directional signs (Left/Right) by focusing exclusively on the sign's geometry, ignoring background noise.
- **PID Control:** Implementing proportional-integral-derivative control for smoother turning and speed management.

---

## 👥 Authors

- **Danna Alejandra Sánchez** - *System Design & AI Integration*
- **Jorge Enrique Lugo Lopez** - *Hardware Architecture & Low-Level Control*

*Project developed at Universidad de La Sabana.*

---
**Targeting Automotive Innovation:** This project is designed as a proof-of-concept for scalable, low-cost autonomous systems, aligning with the engineering excellence standards of leaders like **FEV Iberia**.

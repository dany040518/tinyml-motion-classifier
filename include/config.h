#pragma once

// ================= Pines Motores y Aux =================
#define ENA_IZQ    D0
#define IN1_IZQ    D1
#define IN2_IZQ    D2

#define ENA_DER    D3
#define IN1_DER    D4
#define IN2_DER    D5

// ================= PWM Motores =================
#define PWM_FREQ_HZ    1000   // Frecuencia PWM en Hz
#define PWM_RES_BITS   10     // Resolución: 0-1023
#define VELOCIDAD_PWM  700    // Velocidad base (0-1023). Ajustar según batería.

// ================= WiFi / AP =================
#define AP_SSID   "ESP32_Config"
#define AP_PASS   ""  
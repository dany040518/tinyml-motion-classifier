#include "navigation.h"
#include "../motors/motors.h"

// ================================================================
//  navigation.cpp — Lógica de decisión basada en predicción ML
//  Proyecto: CarControl AIoT (XIAO ESP32-S3 Sense)
//
//  Traduce la salida del clasificador Edge Impulse (4 clases)
//  en llamadas concretas al módulo de motores.
//
//  Flujo esperado (Etapa 4 — integración real):
//    Cámara → Edge Impulse inferencia → predicción (String)
//                                            ↓
//                                   ejecutarDecision()
//                                            ↓
//                                   módulo motors → L298N
// ================================================================

void ejecutarDecision(String prediccion) {

    // Normalizar a minúsculas para evitar errores por capitalización
    prediccion.toLowerCase();
    prediccion.trim();

    Serial.print("[nav] Predicción recibida: \"");
    Serial.print(prediccion);
    Serial.println("\"");

    // ---- Árbol de decisión basado en las 4 clases del modelo ----

    if (prediccion == "left") {
        // Señal de flecha izquierda detectada
        girarIzquierda();

    } else if (prediccion == "right") {
        // Señal de flecha derecha detectada
        girarDerecha();

    } else if (prediccion == "stop") {
        // Señal de STOP detectada
        detener();

    } else if (prediccion == "none") {
        // No se detecta ninguna señal → avanzar libremente
        avanzar();

    } else {
        // Clase desconocida: comportamiento seguro = detenerse
        Serial.print("[nav] ADVERTENCIA: clase desconocida '");
        Serial.print(prediccion);
        Serial.println("' → deteniendo por seguridad.");
        detener();
    }
}
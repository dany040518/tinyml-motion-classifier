#pragma once

#include <Arduino.h>

// ================================================================
//  navigation.h — Módulo de navegación por visión (TinyML)
//  Proyecto: CarControl AIoT (XIAO ESP32-S3 Sense)
//
//  Este módulo recibe la predicción del modelo Edge Impulse
//  y traduce la clase detectada en una acción de movimiento.
//
//  Clases reconocidas:
//    "left"  → girarIzquierda()
//    "right" → girarDerecha()
//    "stop"  → detener()
//    "none"  → avanzar()
// ================================================================

/**
 * @brief Ejecuta la acción de movimiento según la predicción del modelo ML.
 *
 * @param prediccion  String con la clase predicha por Edge Impulse.
 *                    Valores válidos: "left", "right", "stop", "none"
 *
 * Ejemplo de uso:
 *   ejecutarDecision("left");   // → girarIzquierda()
 *   ejecutarDecision("none");   // → avanzar()
 */
void ejecutarDecision(String prediccion);
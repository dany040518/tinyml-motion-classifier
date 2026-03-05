#include <Arduino.h>
#include "motors/motors.h"
#include "navigation/navigation.h"
#include "camera/camera.h"
#include "ml/classifier.h"

void setup() {

    Serial.begin(115200);

    camera_init();
    motors_init();
}

void loop() {

    String prediction = run_classifier_camera();

    ejecutarDecision(prediction);

}

// ================================================================
//  main.cpp — Controlador principal del sistema CarControl AIoT
//  Proyecto: CarControl AIoT (XIAO ESP32-S3 Sense)
//  Framework: Arduino | Plataforma: PlatformIO
//
//  Estado actual del proyecto:
//    ✅ Etapa 2 — Control de motores (motors.h / motors.cpp)
//    ✅ Etapa 3 — Lógica de navegación (navigation.h / navigation.cpp)
//    🔄 Etapa 4 — Integración modelo Edge Impulse (pendiente)
//
//  SIMULACIÓN TEMPORAL:
//    Se itera sobre un arreglo de predicciones ficticias para
//    verificar que cada acción del carrito se ejecuta correctamente.
//    Cuando el modelo Edge Impulse esté listo, reemplazar la
//    variable `prediction` con la salida real del clasificador.
// ================================================================

// ---- Simulación: secuencia de predicciones de prueba ----------
const String testPredictions[] = { "none", "left", "none", "right", "none", "stop" };
const int    numPredictions     = sizeof(testPredictions) / sizeof(testPredictions[0]);
int          predIndex          = 0;

// ---- Intervalo entre cada decisión simulada (ms) --------------
const unsigned long DECISION_INTERVAL_MS = 2000;
unsigned long lastDecisionTime = 0;

// ================================================================
//  setup()
// ================================================================
void setup() {
    Serial.begin(115200);
    delay(500);

    Serial.println("================================================");
    Serial.println("  CarControl AIoT — XIAO ESP32-S3 Sense");
    Serial.println("  Etapas 2 y 3: Motores + Navegación");
    Serial.println("  [MODO SIMULACIÓN — sin modelo ML aún]");
    Serial.println("================================================");

    // Inicializar el módulo de motores
    motors_init();

    // Asegurar estado inicial: detenido
    detener();

    Serial.println("[main] Sistema listo. Iniciando simulación...\n");
}

// ================================================================
//  loop()
// ================================================================
void loop() {
    unsigned long ahora = millis();

    // Ejecutar una nueva decisión cada DECISION_INTERVAL_MS ms
    if (ahora - lastDecisionTime >= DECISION_INTERVAL_MS) {
        lastDecisionTime = ahora;

        // -------------------------------------------------------
        // TODO (Etapa 4): Reemplazar esta línea por la predicción
        //                 real del modelo Edge Impulse:
        //
        //   String prediction = getMLPrediction();
        //
        // Por ahora usamos la simulación:
        // -------------------------------------------------------
        String prediction = testPredictions[predIndex];

        Serial.print("[main] Ciclo ");
        Serial.print(predIndex + 1);
        Serial.print("/");
        Serial.print(numPredictions);
        Serial.print(" → simulando predicción: \"");
        Serial.print(prediction);
        Serial.println("\"");

        // Pasar la predicción al módulo de navegación
        ejecutarDecision(prediction);

        // Avanzar al siguiente índice (cíclico)
        predIndex = (predIndex + 1) % numPredictions;

        Serial.println(); // Separador visual en Serial Monitor
    }
}
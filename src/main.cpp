#include <Arduino.h>
#include "motors/motors.h"
#include "navigation/navigation.h"
#include "camera/camera.h"
#include "ml/classifier.h"

// ================================================================
//  main.cpp — Controlador principal del sistema CarControl AIoT
//  Proyecto: CarControl AIoT (XIAO ESP32-S3 Sense)
//  Framework: Arduino | Plataforma: PlatformIO
//
//  Flujo del loop:
//    1. Leer IMU → si hay inclinación peligrosa → detener (seguridad)
//    2. Capturar imagen con la cámara → inspeccionar buffer
//    3. Simular predicción ML → ejecutar decisión de movimiento
// ================================================================

// ---- Intervalo entre ciclos completos (ms) --------------------
const unsigned long LOOP_INTERVAL_MS = 3000;
unsigned long lastLoopTime = 0;

// ---- Simulación: secuencia de predicciones de prueba ----------
const String testPredictions[] = { "none", "left", "none", "right", "none", "stop" };
const int    numPredictions     = sizeof(testPredictions) / sizeof(testPredictions[0]);
int          predIndex          = 0;

// ---- Callback de cámara: se ejecuta con el frame capturado ----
//  En la Etapa 4 este callback pasará fb->buf a Edge Impulse.
//  Por ahora solo imprime información del frame para verificar.
void onFrameCaptured(camera_fb_t* fb) {
    Serial.println("[main] === Datos del frame capturado ===");
    Serial.print("  Resolución : ");
    Serial.print(fb->width);
    Serial.print(" x ");
    Serial.println(fb->height);
    Serial.print("  Tamaño buf : ");
    Serial.print(fb->len);
    Serial.println(" bytes");
    Serial.print("  Primer px  : ");
    Serial.println(fb->buf[0]);
    Serial.print("  Último px  : ");
    Serial.println(fb->buf[fb->len - 1]);

    // -------------------------------------------------------
    // TODO (Etapa 4): Aquí se integrará Edge Impulse:
    //
    //   signal_t signal;
    //   numpy::signal_from_buffer(fb->buf, fb->len, &signal);
    //   ei_impulse_result_t result;
    //   run_classifier(&signal, &result, false);
    //   String prediction = result.classification[...].label;
    //   ejecutarDecision(prediction);
    // -------------------------------------------------------
}

// ================================================================
//  setup()
// ================================================================
void setup() {
    Serial.begin(115200);
    delay(800);

    Serial.println("================================================");
    Serial.println("  CarControl AIoT — XIAO ESP32-S3 Sense");
    Serial.println("  Etapas 2, 3, 5 y 6: Motores + Nav + Cam");
    Serial.println("  [MODO SIMULACION — sin modelo ML aun]");
    Serial.println("================================================\n");

    motors_init();

    bool camOk = camera_init();
    if (!camOk) {
        Serial.println("[main] ADVERTENCIA: camara no disponible. Continuando sin ella.");
    }

    detener();
    Serial.println("\n[main] Sistema listo. Iniciando ciclo principal...\n");
}

// ================================================================
//  loop()
// ================================================================
void loop() {
    unsigned long ahora = millis();

    if (ahora - lastLoopTime >= LOOP_INTERVAL_MS) {
        lastLoopTime = ahora;

        Serial.println("================================================");
        Serial.print("[main] Ciclo ");
        Serial.print(predIndex + 1);
        Serial.print(" / ");
        Serial.println(numPredictions);

        // ---- PASO 1: Capturar imagen con la cámara ---------
        camera_capture(onFrameCaptured);

        // ---- PASO 2: Simular predicción ML y decidir -------
        String prediction = testPredictions[predIndex];
        Serial.print("[main] Prediccion simulada: \"");
        Serial.print(prediction);
        Serial.println("\"");

        ejecutarDecision(prediction);

        predIndex = (predIndex + 1) % numPredictions;
        Serial.println();
    }
}
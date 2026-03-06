#include "motors.h"
#include "../../include/config.h"

// ================================================================
//  motors.cpp — Implementación del control de motores
//  Proyecto: CarControl AIoT (XIAO ESP32-S3 Sense)
//
//  Usa el API ledcAttach() / ledcWrite() del Arduino framework
//  para ESP32 (versión >=3.x). Compatible con PlatformIO.
//
//  Esquema L298N:
//    ENA / ENB  → Pin PWM (controla velocidad)
//    IN1 / IN2  → Dirección motor izquierdo
//    IN3 / IN4  → Dirección motor derecho
// ================================================================

// -------------------- Estado interno --------------------------
static String _estadoMotores = "DETENIDO";

// ================================================================
//  motors_init()
// ================================================================
void motors_init() {
    // Pines de dirección como salida digital
    pinMode(IN1_IZQ, OUTPUT);
    pinMode(IN2_IZQ, OUTPUT);
    pinMode(IN1_DER, OUTPUT);
    pinMode(IN2_DER, OUTPUT);

    // Canales PWM para habilitación de motores (ESP32 Arduino >=3.x)
    ledcAttach(ENA_IZQ, PWM_FREQ_HZ, PWM_RES_BITS);
    ledcAttach(ENA_DER, PWM_FREQ_HZ, PWM_RES_BITS);

    // Asegurarse de que arranque detenido
    detener();

    Serial.println("[motors] Módulo de motores inicializado.");
}

// ================================================================
//  avanzar()  — Ambos motores hacia adelante
// ================================================================
void avanzar() {
    _estadoMotores = "ADELANTE";

    // Motor izquierdo: adelante
    digitalWrite(IN1_IZQ, HIGH);
    digitalWrite(IN2_IZQ, LOW);

    // Motor derecho: adelante
    digitalWrite(IN1_DER, HIGH);
    digitalWrite(IN2_DER, LOW);

    // Aplicar velocidad PWM
    ledcWrite(ENA_IZQ, VELOCIDAD_PWM);
    ledcWrite(ENA_DER, VELOCIDAD_PWM);

    Serial.println("[motors] >> AVANZAR");
}

// ================================================================
//  girarIzquierda()  — Solo motor derecho activo
// ================================================================
void girarIzquierda() {
    _estadoMotores = "IZQUIERDA";

    // Motor izquierdo: apagado
    digitalWrite(IN1_IZQ, LOW);
    digitalWrite(IN2_IZQ, LOW);
    ledcWrite(ENA_IZQ, 0);

    // Motor derecho: adelante (impulsa hacia la izquierda)
    digitalWrite(IN1_DER, HIGH);
    digitalWrite(IN2_DER, LOW);
    ledcWrite(ENA_DER, VELOCIDAD_PWM);

    Serial.println("[motors] << GIRAR IZQUIERDA");
}

// ================================================================
//  girarDerecha()  — Solo motor izquierdo activo
// ================================================================
void girarDerecha() {
    _estadoMotores = "DERECHA";

    // Motor izquierdo: adelante (impulsa hacia la derecha)
    digitalWrite(IN1_IZQ, HIGH);
    digitalWrite(IN2_IZQ, LOW);
    ledcWrite(ENA_IZQ, VELOCIDAD_PWM);

    // Motor derecho: apagado
    digitalWrite(IN1_DER, LOW);
    digitalWrite(IN2_DER, LOW);
    ledcWrite(ENA_DER, 0);

    Serial.println("[motors] >> GIRAR DERECHA");
}

// ================================================================
//  detener()  — Corta corriente a ambos motores
// ================================================================
void detener() {
    _estadoMotores = "DETENIDO";

    digitalWrite(IN1_IZQ, LOW);
    digitalWrite(IN2_IZQ, LOW);
    digitalWrite(IN1_DER, LOW);
    digitalWrite(IN2_DER, LOW);

    ledcWrite(ENA_IZQ, 0);
    ledcWrite(ENA_DER, 0);

    Serial.println("[motors] || DETENIDO");
}
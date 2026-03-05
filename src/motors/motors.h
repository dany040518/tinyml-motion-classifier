#pragma once

#include <Arduino.h>

// ================================================================
//  motors.h — Módulo de control de motores
//  Proyecto: CarControl AIoT (XIAO ESP32-S3 Sense)
//  Driver: L298N (o compatible)
//
//  Pinout adaptado al XIAO ESP32-S3:
//    Motor IZQUIERDO → IN1=D0, IN2=D1, ENA=D2 (PWM)
//    Motor DERECHO   → IN3=D3, IN4=D4, ENB=D5 (PWM)
// ================================================================

// -------------------- Prototipos de funciones ------------------

/**
 * @brief Inicializa los pines y canales PWM de los motores.
 *        Debe llamarse una sola vez en setup().
 */
void motors_init();

/**
 * @brief Avanza el carrito hacia adelante.
 *        Ambos motores giran en sentido positivo.
 */
void avanzar();

/**
 * @brief Gira el carrito a la izquierda.
 *        Motor derecho activo, motor izquierdo detenido.
 */
void girarIzquierda();

/**
 * @brief Gira el carrito a la derecha.
 *        Motor izquierdo activo, motor derecho detenido.
 */
void girarDerecha();

/**
 * @brief Detiene completamente el carrito.
 *        Ambos motores sin corriente.
 */
void detener();
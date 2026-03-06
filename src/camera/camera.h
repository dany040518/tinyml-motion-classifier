#pragma once

#include <Arduino.h>
#include "esp_camera.h"

// ================================================================
//  camera.h — Módulo de cámara OV2640
//  Proyecto: CarControl AIoT (XIAO ESP32-S3 Sense)
//
//  El XIAO ESP32-S3 Sense tiene la cámara OV2640 conectada
//  internamente al ESP32-S3 mediante pines fijos definidos
//  por el fabricante Seeed Studio.
//
//  Resolución configurada: 96x96 px (GRAYSCALE)
//  → Optimizada para inferencia con Edge Impulse (TinyML)
//  → Menor uso de PSRAM y mayor velocidad de captura
// ================================================================

// ---------------------------------------------------------------
//  Pinout OV2640 fijo en XIAO ESP32-S3 Sense
//  (definido por Seeed Studio, no cambiar)
// ---------------------------------------------------------------
#define CAM_PIN_PWDN    -1
#define CAM_PIN_RESET   -1
#define CAM_PIN_XCLK     10
#define CAM_PIN_SIOD     40
#define CAM_PIN_SIOC     39
#define CAM_PIN_D7       48
#define CAM_PIN_D6       11
#define CAM_PIN_D5       12
#define CAM_PIN_D4       14
#define CAM_PIN_D3       16
#define CAM_PIN_D2       18
#define CAM_PIN_D1       17
#define CAM_PIN_D0       15
#define CAM_PIN_VSYNC    38
#define CAM_PIN_HREF     47
#define CAM_PIN_PCLK     13

// ---------------------------------------------------------------
//  Resolución de captura
//  FRAMESIZE_96X96 → compatible con modelos Edge Impulse 96x96
//  Cambiar a FRAMESIZE_QVGA (320x240) si se necesita más detalle
// ---------------------------------------------------------------
#define CAM_FRAME_SIZE   FRAMESIZE_96X96
#define CAM_PIXEL_FORMAT PIXFORMAT_GRAYSCALE

// ---------------------------------------------------------------
//  Prototipos de funciones
// ---------------------------------------------------------------

/**
 * @brief Inicializa la cámara OV2640 con configuración para TinyML.
 *        Debe llamarse una sola vez en setup().
 * @return true si la inicialización fue exitosa, false si falló.
 */
bool camera_init();

/**
 * @brief Captura un frame, ejecuta un callback con acceso al buffer
 *        y luego libera el frame automáticamente.
 *
 *  Uso típico:
 *    camera_capture([](camera_fb_t* fb) {
 *        // usar fb->buf, fb->len, fb->width, fb->height
 *    });
 *
 *  En la Etapa 4 (Edge Impulse), el callback pasará fb->buf
 *  directamente a la función de señal del clasificador.
 *
 * @param callback  Función que recibe el puntero al frame.
 *                  El frame es válido solo dentro del callback.
 * @return true si la captura fue exitosa.
 */
bool camera_capture(void (*callback)(camera_fb_t* fb));
#include "camera.h"

// ================================================================
//  camera.cpp — Implementación del módulo de cámara OV2640
//  Proyecto: CarControl AIoT (XIAO ESP32-S3 Sense)
//
//  Flujo de uso previsto (Etapa 4 — Edge Impulse):
//
//    camera_capture([](camera_fb_t* fb) {
//        // fb->buf  → puntero al array de píxeles (uint8_t*)
//        // fb->len  → tamaño total en bytes
//        // Pasar a ei_camera_get_data() o signal_t de EI
//    });
//
//  El frame se libera automáticamente al salir del callback,
//  evitando fugas de memoria en PSRAM.
// ================================================================

// ================================================================
//  camera_init()
// ================================================================
bool camera_init() {
    Serial.println("[camera] Inicializando OV2640...");

    camera_config_t config;

    // ---- Pines de la cámara (fijos en XIAO ESP32-S3 Sense) ----
    config.pin_pwdn     = CAM_PIN_PWDN;
    config.pin_reset    = CAM_PIN_RESET;
    config.pin_xclk     = CAM_PIN_XCLK;
    config.pin_sccb_sda = CAM_PIN_SIOD;
    config.pin_sccb_scl = CAM_PIN_SIOC;
    config.pin_d7       = CAM_PIN_D7;
    config.pin_d6       = CAM_PIN_D6;
    config.pin_d5       = CAM_PIN_D5;
    config.pin_d4       = CAM_PIN_D4;
    config.pin_d3       = CAM_PIN_D3;
    config.pin_d2       = CAM_PIN_D2;
    config.pin_d1       = CAM_PIN_D1;
    config.pin_d0       = CAM_PIN_D0;
    config.pin_vsync    = CAM_PIN_VSYNC;
    config.pin_href     = CAM_PIN_HREF;
    config.pin_pclk     = CAM_PIN_PCLK;

    // ---- Configuración de imagen ----------------------------
    config.xclk_freq_hz = 20000000;           // 20 MHz (estándar OV2640)
    config.pixel_format = CAM_PIXEL_FORMAT;   // GRAYSCALE para TinyML
    config.frame_size   = CAM_FRAME_SIZE;     // 96x96 px
    config.jpeg_quality = 12;                 // Solo aplica si se usa JPEG
    config.fb_count     = 1;                  // 1 frame buffer en memoria

    // ---- Usar PSRAM si está disponible ----------------------
    if (psramFound()) {
        config.fb_location = CAMERA_FB_IN_PSRAM;
        Serial.println("[camera] PSRAM detectada — frame buffer en PSRAM.");
    } else {
        config.fb_location = CAMERA_FB_IN_DRAM;
        Serial.println("[camera] PSRAM no encontrada — frame buffer en DRAM.");
    }

    // ---- Inicializar driver de cámara -----------------------
    esp_err_t err = esp_camera_init(&config);

    if (err != ESP_OK) {
        Serial.print("[camera] ERROR al inicializar: 0x");
        Serial.println(err, HEX);
        return false;
    }

    Serial.println("[camera] OV2640 inicializada correctamente.");
    Serial.print("[camera] Resolución: ");
    Serial.print(96);
    Serial.print("x");
    Serial.print(96);
    Serial.println(" px | Formato: GRAYSCALE");

    return true;
}

// ================================================================
//  camera_capture()
// ================================================================
bool camera_capture(void (*callback)(camera_fb_t* fb)) {

    // Capturar frame desde el sensor
    camera_fb_t* fb = esp_camera_fb_get();

    if (fb == nullptr) {
        Serial.println("[camera] ERROR: no se pudo capturar el frame (fb == NULL).");
        return false;
    }

    Serial.print("[camera] Frame capturado — ");
    Serial.print(fb->width);
    Serial.print("x");
    Serial.print(fb->height);
    Serial.print(" px | ");
    Serial.print(fb->len);
    Serial.println(" bytes");

    // Ejecutar el callback con acceso al buffer del frame
    if (callback != nullptr) {
        callback(fb);
    }

    // Liberar el frame (imprescindible para no agotar PSRAM)
    esp_camera_fb_return(fb);
    Serial.println("[camera] Frame liberado.");

    return true;
}
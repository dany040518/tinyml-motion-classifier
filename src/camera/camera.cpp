#include "Arduino.h"
#include "camera.h"
#include "esp_camera.h"

void camera_init() {

    Serial.println("Inicializando camara");

}

bool capture_image() {

    camera_fb_t *fb = esp_camera_fb_get();

    if (!fb) {
        Serial.println("Error capturando imagen");
        return false;
    }

    esp_camera_fb_return(fb);
    return true;
}
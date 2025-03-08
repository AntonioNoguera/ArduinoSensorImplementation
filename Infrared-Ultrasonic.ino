#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TRIG 9
#define ECHO 10
#define LED_ALARM 7  // LED que se activará si la temperatura es alta

#define NUM_SAMPLES 5  // Tamaño del filtro de media móvil
#define TEMP_THRESHOLD 38.0  // Umbral de temperatura en °C para activar la alarma

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Adafruit_SSD1306 display(128, 64, &Wire);

float distanceSamples[NUM_SAMPLES] = {0};  // Almacenar las últimas mediciones de distancia
int sampleIndex = 0;

void setup() {
    Serial.begin(9600);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(LED_ALARM, OUTPUT);

    mlx.begin();
    
    // Inicializar pantalla OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("Error al inicializar pantalla OLED"));
        while (1);
    }
    display.clearDisplay();
}

void loop() {
    float distance = getFilteredDistance();
    float objectTemp = mlx.readObjectTempC();
    float ambientTemp = mlx.readAmbientTempC();

    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println(" cm");

    Serial.print("Temperatura del objeto: ");
    Serial.print(objectTemp);
    Serial.println(" °C");

    Serial.print("Temperatura ambiente: ");
    Serial.print(ambientTemp);
    Serial.println(" °C");

    // Alarma si la temperatura del objeto supera el umbral
    if (objectTemp >= TEMP_THRESHOLD) {
        digitalWrite(LED_ALARM, HIGH);
        Serial.println("⚠️ ¡Alerta! Temperatura del objeto demasiado alta.");
    } else {
        digitalWrite(LED_ALARM, LOW);
    }

    // Mostrar en pantalla OLED
    updateDisplay(distance, objectTemp, ambientTemp);

    delay(500);
}

/**
 * Obtiene una lectura de distancia con un filtro de media móvil.
 */
float getFilteredDistance() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    long duration = pulseIn(ECHO, HIGH);
    float distance = duration * 0.034 / 2; // Conversión a cm

    // Actualizar muestras en el buffer
    distanceSamples[sampleIndex] = distance;
    sampleIndex = (sampleIndex + 1) % NUM_SAMPLES;

    // Calcular la media móvil
    float sum = 0;
    for (int i = 0; i < NUM_SAMPLES; i++) {
        sum += distanceSamples[i];
    }
    return sum / NUM_SAMPLES;
}

/**
 * Muestra los valores en la pantalla OLED.
 */
void updateDisplay(float distance, float objectTemp, float ambientTemp) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    display.setCursor(0, 0);
    display.print("Distancia: ");
    display.print(distance);
    display.println(" cm");

    display.setCursor(0, 15);
    display.print("Obj. Temp: ");
    display.print(objectTemp);
    display.println(" C");

    display.setCursor(0, 30);
    display.print("Amb. Temp: ");
    display.print(ambientTemp);
    display.println(" C");

    // Mensaje de alerta si la temperatura del objeto es alta
    if (objectTemp >= TEMP_THRESHOLD) {
        display.setCursor(0, 50);
        display.setTextSize(2);
        display.println("ALERTA!");
    }

    display.display();
}
